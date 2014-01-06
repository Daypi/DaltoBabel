#include		<iostream>
#include		"Server.h"
#include		"Util.hpp"

Server::Server(int port, int nbListen) : _port(port), _nbListen(nbListen), _started(false)
{
	this->_instruction[Packet::LIST] = &Server::list;
	this->_instruction[Packet::CALL] = &Server::call;
	this->_instruction[Packet::HANGUP] = &Server::hangUp;
	this->_instruction[Packet::STATUSTEXT] = &Server::statusText;
	this->_instruction[Packet::STATUS] = &Server::status;
	this->_instruction[Packet::ACCEPT_CALL] = &Server::acceptCall;
	this->_instruction[Packet::REJECT_CALL] = &Server::rejectCall;
	this->_instruction[Packet::LOGIN] = &Server::login;
	this->_instruction[Packet::CREATE_ACCOUNT] = &Server::createAccount;
	this->_instruction[Packet::ADD_CONTACT] = &Server::addContact;
	this->_instruction[Packet::REMOVE_CONTACT] = &Server::removeContact;
	this->_instruction[Packet::BLOCK_CONTACT] = &Server::blockContact;
	this->_instruction[Packet::CHAT] = &Server::chat;
	this->_instruction[Packet::ERROR_] = &Server::error;
	this->_instruction[Packet::HANDSHAKE] = &Server::handshake;
	this->_instruction[Packet::PING] = &Server::ping;
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

void								Server::start()
{
	Thread<Server, void, void *>	thread(this, &Server::start, 0);
	bool							stop = false;
	std::string						line = "";

	this->_accountManager.load();
	thread.start();
	while (!stop)
	{
		std::cout << "> ";
		std::getline(std::cin, line);
		if (line == "exit")
		{
			stop = true;
			this->stop();
		}
	}
	this->_accountManager.save();
	//thread.stop();
}

void									Server::start(void *)
{
	unsigned int						i;
	std::pair<unsigned int, char *>		ret;
	Packet								*packet;
	User								*user;

	this->_mutex.lock();
	this->_started = true;
	this->_mutex.unLock();
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
				packet = this->getPacket(user, true);
				while (packet)
				{
					if (packet->getMagicNumber() == Packet::MAGIC_NUMBER && packet->getInstruction() < Packet::ENUM_COUNT)
						(this->*(this->_instruction[(Packet::eInstruction)packet->getInstruction()]))(user, packet);
					packet = this->getPacket(user, false);
				}
			}
		}
		this->sendTCP();
		this->timeout();
	}
}

void			Server::stop()
{
	this->_mutex.lock();
	this->_started = false;
	this->_mutex.unLock();
}

void						Server::timeout()
{
	std::vector<User *>		userList;
	Account					*account;

	userList = this->_userCollection.getUserList();
	for (unsigned int i = 0; i < userList.size(); ++i)
	{
		if (userList[i]->timeout(60, false))
		{
			// Disconnect the user
			this->_sockTCP.releaseClient(userList[i]->getSockId());
			account = this->_accountManager.getAccountByName(userList[i]->getName());
			if (account)
				account->disconnect();
			this->_userCollection.removeUserByName(userList[i]->getName());
			std::cout << "User disconnected on timeout" << std::endl;
		}
	}
}

Packet					*Server::getPacket(User *user, bool first)
{
	Packet				*packet = 0;
	Account				*account;

	if (!user)
	{
		std::cout << "User NULL on getPacket" << std::endl;
		return (0);
	}
	if (!first)
		return (user->getPacket());
	this->_received = this->_sockTCP.recv(user->getSockId(), 1500);
	if (this->_received.size() == 0)
	{
		//user->disconnect();
		account = this->_accountManager.getAccountByName(user->getName());
		if (account)
			account->disconnect();
		this->_userCollection.removeUserByName(user->getName());
		std::cout << "User disconnected on recv" << std::endl;
		//std::cin.get();
	}
	else
	{
		unsigned char *str = (unsigned char *)this->_received[0].first;
		std::cout << "received size = " << this->_received.size() << ", size read = " << this->_received[0].second << std::endl;
		for (unsigned int i = 0; i < (unsigned int)this->_received[0].second; ++i)
		{
			std::cout << Util::format<const std::string&>('0', 2, Util::toHex<unsigned int>(str[i])) << " ";
		}
		std::cout << std::endl;
		packet = user->getPacket(this->_received[user->getSockId()].first, this->_received[user->getSockId()].second);
	}
	return (packet);
}

void									Server::sendTCP()
{
	std::pair<Packet *, unsigned int>	packet;
	User								*user;
	Account								*account;
	unsigned int						nb = 0;
	bool								deco = false;
	unsigned int						decoNb = 0;

	while (this->_toSendTCP.size() > 0)
	{
		try
		{
			packet = this->_toSendTCP.front();
			this->_clientList = this->_sockTCP.isWritable(packet.second);
			std::cout << "packet.second = " << packet.second << std::endl;
			if (this->_clientList.size() == 1)
			{
				deco = false;
				decoNb = 0;
				user = this->_userCollection.getUserBySockId(packet.second);
				std::cout << "I CAN WRITE TCP " << nb << " to " << (user ? user->getName() : "NULL") << " : " << packet.second << std::endl;
				packet.first->show();
				this->_clientList = this->_sockTCP.send(packet.second, packet.first->serialize(), packet.first->size());
				for (unsigned int i = 0; i < this->_clientList.size(); ++i)
				{
					user = this->_userCollection.getUserBySockId(this->_clientList[i]);
					if (user)
					{
						//user->disconnect();
						account = this->_accountManager.getAccountByName(user->getName());
						if (account)
							account->disconnect();
						this->_userCollection.removeUserByName(user->getName());
						std::cout << "User disconnected on send" << std::endl;
						//std::cin.get();
					}
				}
				delete packet.first;
				this->_toSendTCP.pop();
			}
		}
		catch (const Exception& e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "toSendTCP.size() = " << this->_toSendTCP.size() << std::endl;
			deco = true;
		}
		if (deco)
			++decoNb;
		if (deco && decoNb > 10)
		{
			std::cout << "deco && decoNb > 10" << std::endl;
			return;
		}
		++nb;
	}
}

void											Server::list(User *user, Packet *packet)
{
	this->list(user, packet->getRequestUID());
}

void											Server::list(User *user, unsigned short req)
{
	Packet										*toSend = 0;
	std::vector<std::pair<Account *, bool> >	contactList;
	Account										*account = 0;
	char										status = 1;
	std::string									response = "";
	short										id = 2;
	unsigned int								nb = 0;

	std::cout << "LIST" << std::endl;
	account = this->_accountManager.getAccountByName(user->getName());
	if (!account)
	{
		std::cout << "Account not found" << std::endl;
		return;
	}
	contactList = account->getContactList();
	for (unsigned int i = 0; i < contactList.size(); ++i)
	{
		nb += 4 + contactList[i].first->getName().size();
		nb += 4 + contactList[i].first->getStatusText().size();
		nb += 3;
	}
	toSend = new Packet(req, Packet::LIST);
	toSend->setFormat(status ? "clssc" : "cs");
	toSend->updateData(3 + 4 + (status ? nb : response.size()));
	toSend->appendToData<char>(0, status);
	if (status)
	{
		toSend->appendToData<short>(1, contactList.size());
		for (unsigned int i = 0; i < contactList.size(); ++i)
		{
			toSend->appendToData(id, contactList[i].first->getName());
			toSend->appendToData(id + 1, contactList[i].first->getStatusText());
			toSend->appendToData<char>(id + 2, contactList[i].first->contactBlocked(user->getName()) ? Account::INVISIBLE : contactList[i].first->getStatus());
			id += 3;
		}
	}
	else
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

	std::cout << "CALL" << std::endl;
	login = packet->getString(0);
	fromCall = this->_accountManager.getAccountByName(user->getName());
	toCall = this->_accountManager.getAccountByName(login);
	response = fromCall->getName();
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
	toSend = new Packet(packet->getRequestUID(), Packet::CALL);
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
	User			*tmp = 0;

	std::cout << "HANGUP" << std::endl;
	login = user->getName();
	response = login;
	if (!this->_accountManager.accountExists(login))
	{
		status = 0;
		response = "Unknown user " + login + ".";
	}
	fromCall = this->_accountManager.getAccountByName(user->getName());
	toCall = fromCall->getCurrentCall();
	if (!toCall)
	{
		std::cerr << "toCall NULL" << std::endl;
		return;
	}
	toSend = new Packet(packet->getRequestUID(), Packet::HANGUP);
	toSend->setFormat(status ? "cs" : "css");
	toSend->updateData(3 + 4 + response.size() + (status ? 0 : (4 + toCall->getName().size())));
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	tmp = user;
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
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, tmp->getSockId()));
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(new Packet(*toSend), user->getSockId()));
}

void				Server::statusText(User *user, Packet *packet)
{
	std::string		statusTextStr;
	char			status = 1;
	std::string		response = "";

	statusTextStr = packet->getString(0);
	response = statusTextStr;
	this->statusText(user, packet->getRequestUID(), status, response);
}

void						Server::statusText(User *user, unsigned short req, char status, const std::string& response)
{
	Packet					*toSend = 0;
	Account					*account;
	std::vector<User *>		userList;

	std::cout << "STATUSTEXT" << std::endl;
	account = this->_accountManager.getAccountByName(user->getName());
	if (account && status)
		account->setStatusText(response);
	toSend = new Packet(req, Packet::STATUSTEXT);
	toSend->setFormat("cs");
	toSend->updateData(3 + 4 + response.size());
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
	userList = this->_userCollection.getUserList();
	for (unsigned int i = 0; i < userList.size(); ++i)
	{
	  this->list(userList[i], (unsigned short)0);
	}
}

void				Server::status(User *user, Packet *packet)
{
	char			stat;
	char			status = 1;
	std::string		response = "";

	stat = packet->getChar(0);
	if (stat < 0 || stat >= Account::ENUM_COUNT)
	{
		status = 0;
		response = "Invalid status value.";
	}
	this->status(user, packet->getRequestUID(), status, stat, response);
}

void						Server::status(User *user, unsigned short req, char status, char stat, const std::string& response)
{
	Packet					*toSend = 0;
	Account					*account;
	std::vector<User *>		userList;

	std::cout << "STATUS" << std::endl;
	account = this->_accountManager.getAccountByName(user->getName());
	if (account && status)
		account->setStatus((Account::eStatus)stat);
	toSend = new Packet(req, Packet::STATUS);
	toSend->setFormat(status ? "cc" : "cs");
	toSend->updateData(3 + (status ? 3 : (4 + response.size())));
	toSend->appendToData<char>(0, status);
	if (!status)
		toSend->appendToData(1, response);
	else
		toSend->appendToData(1, stat);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
	userList = this->_userCollection.getUserList();
	for (unsigned int i = 0; i < userList.size(); ++i)
	{
	  this->list(userList[i], (unsigned short)0);
	}
}

void				Server::acceptCall(User *user, Packet *packet)
{
	std::string		login;
	Account			*toCall;
	Account			*fromCall;
	char			status = 0;
	Packet			*toSend = 0;
	std::string		response = "";

	std::cout << "ACCEPT_CALL" << std::endl;
	fromCall = this->_accountManager.getAccountByName(user->getName());
	toCall = fromCall->getCurrentCall();
	login = packet->getString(0);
	response = fromCall->getName();
	if (!toCall)
		response = "Unknown user " + login + ".";
	else if (!toCall->connected())
		response = "User disconnected.";
	/*else if (toCall->pending() || toCall->inCall())
		response = "User already in call.";*/
	else if (fromCall->hasContact(toCall) && fromCall->contactBlocked(toCall))
		response = "Contact blocked.";
	else
		status = 1;
	toSend = new Packet(packet->getRequestUID(), Packet::ACCEPT_CALL);
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

	std::cout << "REJECT_CALL" << std::endl;
	fromCall = this->_accountManager.getAccountByName(user->getName());
	toCall = fromCall->getCurrentCall();
	login = packet->getString(0);
	response = fromCall->getName();
	if (!toCall)
		response = "Unknown user " + login + ".";
	else if (!toCall->connected())
		response = "User disconnected.";
	/*else if (toCall->pending() || toCall->inCall())
		response = "User already in call.";*/
	else if (fromCall->hasContact(toCall) && fromCall->contactBlocked(toCall))
		response = "Contact blocked.";
	else
		status = 1;
	toSend = new Packet(packet->getRequestUID(), Packet::REJECT_CALL);
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
	this->login(user, packet->getRequestUID(), status, response, account);
}

void				Server::login(User *user, unsigned short req, char status, const std::string& response, Account *account)
{
	Packet			*toSend = 0;

	std::cout << "LOGIN" << std::endl;
	toSend = new Packet(req, Packet::LOGIN);
	toSend->setFormat("cs");
	toSend->updateData(3 + 4 + response.size());
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	if (status)
	{
		account->connect();
		account->setStatus(Account::AVAILABLE);
		user->setName(account->getName());
	}
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
	if (status)
	{
		this->statusText(user, 0, 1, account->getStatusText());
		this->status(user, 0, 1, account->getStatus(), "");
		this->list(user, (unsigned short)0);
	}
}

void				Server::createAccount(User *user, Packet *packet)
{
	std::string		login;
	std::string		password;
	char			status = 1;
	Packet			*toSend = 0;
	std::string		response = "";
	Account			*account = 0;

	std::cout << "CREATE_ACCOUNT" << std::endl;
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
	toSend = new Packet(packet->getRequestUID(), Packet::CREATE_ACCOUNT);
	toSend->setFormat("cs");
	toSend->updateData(3 + 4 + response.size());
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
	account = this->_accountManager.getAccountByName(login);
	this->login(user, 0, status, response, account);
	this->_accountManager.save();
}

void				Server::addContact(User *user, Packet *packet)
{
	std::string		login;
	char			status = 0;
	Packet			*toSend;
	std::string		response = "";

	std::cout << "ADD_CONTACT" << std::endl;
	login = packet->getString(0);
	if (!this->_accountManager.addContact(user->getName(), login))
		response = "Unknown user " + login + ".";
	else if (user->getName() == login)
		response = "Cannot add yourself.";
	else
		status = 1;
	toSend = new Packet(packet->getRequestUID(), Packet::ADD_CONTACT);
	toSend->setFormat(status ? "c" : "cs");
	toSend->updateData(!status ? (3 + 4 + response.size()) : 3);
	toSend->appendToData<char>(0, status);
	if (!status)
		toSend->appendToData(1, response);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
	this->list(user, (unsigned short)0);
}

void				Server::removeContact(User *user, Packet *packet)
{
	std::string		login;
	char			status = 1;
	Packet			*toSend;
	std::string		response = "";

	std::cout << "REMOVE_CONTACT" << std::endl;
	login = packet->getString(0);
	if (!this->_accountManager.removeContact(user->getName(), login))
	{
		status = 0;
		response = "Unknown user " + login + ".";
	}
	toSend = new Packet(packet->getRequestUID(), Packet::REMOVE_CONTACT);
	toSend->setFormat(status ? "c" : "cs");
	toSend->updateData(!status ? (3 + 4 + response.size()) : 3);
	toSend->appendToData<char>(0, status);
	if (!status)
		toSend->appendToData(1, response);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
	this->list(user, (unsigned short)0);
}

void				Server::blockContact(User *user, Packet *packet)
{
	std::string		login;
	char			status = 1;
	Packet			*toSend;
	std::string		response = "";

	std::cout << "BLOCK_CONTACT" << std::endl;
	login = packet->getString(0);
	if (!this->_accountManager.blockContact(user->getName(), login))
	{
		status = 0;
		response = "Unknown user " + login + ".";
	}
	toSend = new Packet(packet->getRequestUID(), Packet::BLOCK_CONTACT);
	toSend->setFormat(status ? "c" : "cs");
	toSend->updateData(!status ? (3 + 4 + response.size()) : 3);
	toSend->appendToData<char>(0, status);
	if (!status)
		toSend->appendToData(1, response);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
	user = this->_userCollection.getUserByName(login);
	if (user)
	  this->list(user, (unsigned short)0);
}

void				Server::chat(User *user, Packet *packet)
{
	std::string		login;
	std::string		msg;
	char			status = 1;
	Packet			*toSend;
	std::string		response = "";
	Account			*toChat;

	std::cout << "CHAT" << std::endl;
	login = packet->getString(0);
	msg = packet->getString(1);
	response = login;
	toChat = this->_accountManager.getAccountByName(login);
	if (!toChat)
	{
		status = 0;
		response = "Unknown user " + login + ".";
	}
	toSend = new Packet(packet->getRequestUID(), Packet::CHAT);
	toSend->setFormat(status ? "css" : "cs");
	toSend->updateData(3 + 4 + response.size() + (status ? (4 + msg.size()) : 0));
	toSend->appendToData<char>(0, status);
	toSend->appendToData(1, response);
	if (status)
		toSend->appendToData(2, msg);
	this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
	if (status)
	  response = user->getName();
	user = this->_userCollection.getUserByName(login);
	if (user)
	  {
	    toSend = new Packet(0, Packet::CHAT);
	    toSend->setFormat(status ? "css" : "cs");
	    toSend->updateData(3 + 4 + response.size() + (status ? (4 + msg.size()) : 0));
	    toSend->appendToData<char>(0, status);
	    toSend->appendToData(1, response);
	    if (status)
	      toSend->appendToData(2, msg);
	    this->_toSendTCP.push(std::pair<Packet *, unsigned int>(toSend, user->getSockId()));
	  }
}

void				Server::error(User *, Packet *)
{
	std::cout << "ERROR" << std::endl;
}

void				Server::handshake(User *user, Packet *)
{
	Account			*account;

	std::cout << "HANDSHAKE" << std::endl;
	if (user->timeout(10))
	{
		// Disconnect the user
		this->_sockTCP.releaseClient(user->getSockId());
		account = this->_accountManager.getAccountByName(user->getName());
		if (account)
			account->disconnect();
		this->_userCollection.removeUserByName(user->getName());
		std::cout << "User Disconnected on handshake" << std::endl;
		//std::cin.get();
	}
}

void				Server::ping(User *user, Packet *)
{
	Account			*account;

	std::cout << "PING" << std::endl;
	if (user->timeout(60))
	{
		// Disconnect the user
		this->_sockTCP.releaseClient(user->getSockId());
		account = this->_accountManager.getAccountByName(user->getName());
		if (account)
			account->disconnect();
		this->_userCollection.removeUserByName(user->getName());
		std::cout << "User Disconnected on ping" << std::endl;
		//std::cin.get();
	}
}
