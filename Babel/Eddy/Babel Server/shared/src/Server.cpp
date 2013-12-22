#include		<iostream>
#include		"Server.h"

Server::Server(int port, int nbListen) : _port(port), _nbListen(nbListen), _started(false)
{
	this->_instruction.push_back(&Server::list);
	this->_instruction.push_back(&Server::call);
	this->_instruction.push_back(&Server::hangUp);
	this->_instruction.push_back(&Server::statusText);
	this->_instruction.push_back(&Server::status);
	this->_instruction.push_back(&Server::acceptCall);
	this->_instruction.push_back(&Server::rejectCall);
	this->_instruction.push_back(&Server::createAccount);
	this->_instruction.push_back(&Server::addContact);
	this->_instruction.push_back(&Server::removeContact);
	this->_instruction.push_back(&Server::blockContact);
	this->_instruction.push_back(&Server::chat);
	this->_instruction.push_back(&Server::error);
	this->_instruction.push_back(&Server::handshake);
	this->_instruction.push_back(&Server::ping);
	try
	{
		this->_sockTCP.init(port, nbListen);
		std::cout << "INIT" << std::endl;
	}
	catch (const Exception& e)
	{
		throw e;
	}
}

Server::~Server()
{
}

void									Server::start()
{
	unsigned int						i;
	std::pair<unsigned int, char *>		ret;
	Packet								*packet;
	User								*user;

	this->_accountManager.load();
	this->_started = true;
	while (this->_started)
	{
		this->_clientList = this->_sockTCP.isReadable();
		for (i = 0; i < this->_clientList.size(); ++i)
		{
			std::cout << "TCP" << std::endl;
			if (this->_clientList[i] == 0)
			{
				ret = this->_sockTCP.checkConnection();
				std::cout << "Client " << ret.first << " is connecting : " << ret.second << std::endl;
				if (this->_userCollection.add(ret.first, "", ret.second))
					std::cout << "Client added" << std::endl;
				this->_toSendTCP.push(std::pair<Packet *, unsigned int>(new Packet(0, Packet::HANDSHAKE), ret.first));
			}
			else
			{
				user = this->_userCollection.getUserBySockId(this->_clientList[i]);
				std::cout << "Client = " << this->_clientList[i] << std::endl;
				packet = this->getPacket(user);
				if (packet &&  packet->getMagicNumber() == Packet::MAGIC_NUMBER && packet->getInstruction() < Packet::ENUM_COUNT)
					(this->*(this->_instruction[packet->getInstruction()]))(user, packet);
			}
		}
		this->sendTCP();
	}
	this->_accountManager.save();
}

void			Server::stop()
{
	this->_started = false;
}

Packet					*Server::getPacket(User *user)
{
	Packet				*packet = 0;

	if (!user)
		return (0);
	this->_received = this->_sockTCP.recv(user->getSockId(), 1500);
	if (this->_received.size() == 0)
	{
		//user->disconnect();
		this->_userCollection.removeUserById(user->getUID());
		std::cout << "Player Disconnected on recv" << std::endl;
	}
	else
	{
		packet = user->getPacket(this->_received[user->getSockId()].first, this->_received[user->getSockId()].second);
	}
	return (packet);
}

void									Server::sendTCP()
{
	std::pair<Packet *, unsigned int>	packet;
	User								*user;

	while (this->_toSendTCP.size() > 0)
	{
		try
		{
			packet = this->_toSendTCP.front();
			this->_clientList = this->_sockTCP.isWritable(packet.second);
			if (this->_clientList.size() == 1)
			{
				std::cout << "I CAN WRITE TCP" << std::endl;
				packet.first->show();
				this->_clientList = this->_sockTCP.send(packet.second, packet.first->serialize(), packet.first->size());
				for (unsigned int i = 0; i < this->_clientList.size(); ++i)
				{
					user = this->_userCollection.getUserById(this->_clientList[i]);
					if (user)
					{
						//user->disconnect();
						this->_userCollection.removeUserById(user->getUID());
						std::cout << "Player Disconnected on send" << std::endl;
					}
				}
				delete packet.first;
				this->_toSendTCP.pop();
			}
		}
		catch (const Exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void											Server::list(User *user, Packet *packet)
{
	char										status = 1;
	Packet										*toSend = 0;
	std::string									response = "";
	Account										*account = 0;
	std::vector<std::pair<Account *, bool> >	contactList;
	short										id = 2;
	unsigned int								nb = 0;

	account = this->_accountManager.getAccountByName(user->getName());
	contactList = account->getContactList();
	for (unsigned int i = 0; i < contactList.size(); ++i)
	{
		nb += 4 + contactList[i].first->getName().size();
		nb += 4 + contactList[i].first->getStatusText().size();
		nb += 3;
	}
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat(status ? "clssc" : "cs");
	toSend->updateData(3 + 4 + (!status ? response.size() : nb));
	toSend->appendToData<char>(0, status);
	toSend->appendToData<short>(1, this->_accountManager.size());
	for (unsigned int i = 0; i < contactList.size(); ++i)
	{
		toSend->appendToData(id, contactList[i].first->getName());
		toSend->appendToData(id + 1, contactList[i].first->getStatusText());
		toSend->appendToData<char>(id + 2, contactList[i].first->getStatus());
		id += 3;
	}
	if (!status)
		toSend->appendToData(1, response);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::call(User *user, Packet *packet)
{
	std::string		login;
	Account			*toCall;
	Account			*fromCall;
	char			status = 0;
	Packet			*toSend = 0;
	std::string		response = "";

	login = packet->getString(0);
	response = login;
	fromCall = this->_accountManager.getAccountByName(user->getName());
	toCall = this->_accountManager.getAccountByName(login);
	if (!toCall)
		response = "Unknown user " + login + ".";
	else if (!toCall->connected())
		response = "User disconnected.";
	else if (toCall->pending() || toCall->inCall())
		response = "User already in call.";
	else if (fromCall->hasContact(login) && fromCall->contactBlocked(login))
		response = "Contact blocked.";
	else
		status = 1;
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat(status ? "css" : "cs");
	toSend->updateData(3 + 4 + response.size() + (status ? (4 + toCall->getIp().size()) : 0));
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	if (status)
	{
		fromCall->setCurrentCall(toCall);
		toCall->setCurrentCall(fromCall);
		fromCall->callWaiting();
		toCall->callWaiting();
		toSend->appendToData(2, toCall->getIp());
		user = this->_userCollection.getUserByName(toCall->getName());
		if (!user)
			std::cerr << "ERROR ON USER" << std::endl;
	}
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::hangUp(User *user, Packet *packet)
{
	std::string		login;
	char			status = 1;
	Account			*fromCall;
	Account			*toCall;
	Packet			*toSend = 0;
	std::string		response = "";

	login = user->getName();
	response = login;
	if (!this->_accountManager.accountExists(login))
	{
		status = 0;
		response = "Unknown user " + login + ".";
	}
	fromCall = this->_accountManager.getAccountByName(user->getName());
	toCall = fromCall->getCurrentCall();
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat(status ? "cs" : "css");
	toSend->updateData(3 + 4 + response.size() + (status ? 0 : (4 + toCall->getName().size())));
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	if (status)
	{
		fromCall->setCurrentCall(0);
		toCall->setCurrentCall(0);
		user = this->_userCollection.getUserByName(toCall->getName());
		if (!user)
			std::cerr << "ERROR ON USER" << std::endl;
	}
	else
		toSend->appendToData(2, toCall->getName());
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::statusText(User *user, Packet *packet)
{
	std::string		statusTextStr;
	char			status = 1;
	Packet			*toSend = 0;
	std::string		response = "";

	statusTextStr = packet->getString(0);
	response = statusTextStr;
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat("cs");
	toSend->updateData(3 + 4 + response.size());
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::status(User *user, Packet *packet)
{
	char			stat;
	char			status = 1;
	Packet			*toSend = 0;
	std::string		response = "";

	stat = packet->getChar(0);
	if (stat < 0 || stat >= Account::ENUM_COUNT)
	{
		status = 0;
		response = "Invalid status value.";
	}
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat("cs");
	toSend->updateData(3 + 3);
	toSend->appendToData<char>(0, status);
	if (!status)
		toSend->appendToData(1, response);
	else
		toSend->appendToData(1, stat);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::acceptCall(User *user, Packet *packet)
{
	std::string		login;
	Account			*toCall;
	Account			*fromCall;
	char			status = 0;
	Packet			*toSend = 0;
	std::string		response = "";

	fromCall = this->_accountManager.getAccountByName(user->getName());
	toCall = fromCall->getCurrentCall();
	if (!toCall)
		response = "Unknown user " + login + ".";
	else if (!toCall->connected())
		response = "User disconnected.";
	else if (toCall->pending() || toCall->inCall())
		response = "User already in call.";
	else if (fromCall->hasContact(toCall) && fromCall->contactBlocked(toCall))
		response = "Contact blocked.";
	else
		status = 1;
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat("css");
	toSend->updateData(3 + 4 + response.size() + 4 + (status ? toCall->getIp().size() : toCall->getName().size()));
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	toSend->appendToData(2, status ? toCall->getIp() : toCall->getName());
	if (status)
	{
		fromCall->callAccepted();
		toCall->callAccepted();
		user = this->_userCollection.getUserByName(toCall->getName());
		if (!user)
			std::cerr << "ERROR ON USER" << std::endl;
	}
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::rejectCall(User *user, Packet *packet)
{
	std::string		login;
	Account			*toCall;
	Account			*fromCall;
	char			status = 0;
	Packet			*toSend = 0;
	std::string		response = "";

	fromCall = this->_accountManager.getAccountByName(user->getName());
	toCall = fromCall->getCurrentCall();
	if (!toCall)
		response = "Unknown user " + login + ".";
	else if (!toCall->connected())
		response = "User disconnected.";
	else if (toCall->pending() || toCall->inCall())
		response = "User already in call.";
	else if (fromCall->hasContact(toCall) && fromCall->contactBlocked(toCall))
		response = "Contact blocked.";
	else
		status = 1;
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat("css");
	toSend->updateData(3 + 4 + response.size() + 4 + (status ? toCall->getIp().size() : toCall->getName().size()));
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	toSend->appendToData(2, status ? toCall->getIp() : toCall->getName());
	if (status)
	{
		fromCall->setCurrentCall(0);
		toCall->setCurrentCall(0);
		fromCall->callAccepted();
		toCall->callAccepted();
		user = this->_userCollection.getUserByName(toCall->getName());
		if (!user)
			std::cerr << "ERROR ON USER" << std::endl;
	}
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::login(User *user, Packet *packet)
{
	std::string		login;
	std::string		password;
	Account			*account;
	char			status = 0;
	Packet			*toSend = 0;
	std::string		response = "";

	login = packet->getString(0);
	password = packet->getString(1);
	response = login;
	account = this->_accountManager.getAccountByName(login);
	if (!account)
		response = "Unknown user " + login + ".";
	else if (account->connected())
		response = "Already connected.";
	else if (account->getPassword() != password)
		response = "Wrong password.";
	else
		status = 1;
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat("cs");
	toSend->updateData(3 + 3);
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	if (status)
		account->connect();
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::createAccount(User *user, Packet *packet)
{
	std::string		login;
	std::string		password;
	char			status = 1;
	Packet			*toSend = 0;
	std::string		response = "";

	login = packet->getString(0);
	password = packet->getString(1);
	response = login;
	if (!this->_accountManager.create(user->getIp(), login, password))
	{
		status = 0;
		response = "Login already taken.";
	}
	else
		user->setName(login);
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat("cs");
	toSend->updateData(3 + 4 + response.size());
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::addContact(User *user, Packet *packet)
{
	std::string		login;
	char			status = 1;
	Packet			*toSend;
	std::string		response = "";

	login = packet->getString(0);
	if (!this->_accountManager.addContact(user->getName(), login))
	{
		status = 0;
		response = "Unknown user " + login + ".";
	}
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat(status ? "c" : "cs");
	toSend->updateData(!status ? (3 + 4 + response.size()) : 3);
	toSend->appendToData<char>(0, status);
	if (!status)
		toSend->appendToData(1, response);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::removeContact(User *user, Packet *packet)
{
	std::string		login;
	char			status = 1;
	Packet			*toSend;
	std::string		response = "";

	login = packet->getString(0);
	if (!this->_accountManager.removeContact(user->getName(), login))
	{
		status = 0;
		response = "Unknown user " + login + ".";
	}
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat(status ? "c" : "cs");
	toSend->updateData(!status ? (3 + 4 + response.size()) : 3);
	toSend->appendToData<char>(0, status);
	if (!status)
		toSend->appendToData(1, response);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::blockContact(User *user, Packet *packet)
{
	std::string		login;
	char			status = 1;
	Packet			*toSend;
	std::string		response = "";

	login = packet->getString(0);
	if (!this->_accountManager.blockContact(user->getName(), login))
	{
		status = 0;
		response = "Unknown user " + login + ".";
	}
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat(status ? "c" : "cs");
	toSend->updateData(!status ? (3 + 4 + response.size()) : 3);
	toSend->appendToData<char>(0, status);
	if (!status)
		toSend->appendToData(1, response);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::chat(User *user, Packet *packet)
{
	std::string		login;
	std::string		msg;
	char			status = 1;
	Packet			*toSend;
	std::string		response = "";
	Account			*toChat;

	login = packet->getString(0);
	msg = packet->getString(0);
	response = user->getName();
	toChat = this->_accountManager.getAccountByName(login);
	if (!toChat)
	{
		status = 0;
		response = "Unknown user " + login + ".";
	}
	toSend = new Packet();
	toSend->header(packet->serialize());
	toSend->setFormat(status ? "css" : "cs");
	toSend->updateData(3 + 4 + response.size() + (status ? (4 + msg.size()) : 0));
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	if (status)
		toSend->appendToData(2, msg);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
	user = this->_userCollection.getUserByName(login);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
}

void				Server::error(User *, Packet *)
{
}

void				Server::handshake(User *user, Packet *)
{
	if (user->timeout(10))
	{
		this->_userCollection.removeUserById(user->getUID());
		std::cout << "Player Disconnected on handshake" << std::endl;
	}
}

void				Server::ping(User *user, Packet *)
{
	if (user->timeout(60))
	{
		this->_userCollection.removeUserById(user->getUID());
		std::cout << "Player Disconnected on ping" << std::endl;
	}
}
