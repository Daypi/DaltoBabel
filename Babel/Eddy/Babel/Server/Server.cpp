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
			}
			else
			{
				user = this->_userCollection.getUserBySockId(this->_clientList[i]);
				std::cout << "Client = " << this->_clientList[i] << std::endl;
				packet = this->getPacket(user);
				if (packet && packet->getInstruction() < Server::ENUM_COUNT)
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

void				Server::list(User *user, Packet *packet)
{
}

void				Server::call(User *user, Packet *packet)
{
}

void				Server::hangUp(User *user, Packet *packet)
{
}

void				Server::statusText(User *user, Packet *packet)
{
}

void				Server::status(User *user, Packet *packet)
{
}

void				Server::acceptCall(User *user, Packet *packet)
{
}

void				Server::rejectCall(User *user, Packet *packet)
{
}

void				Server::login(User *user, Packet *packet)
{
}

void				Server::createAccount(User *user, Packet *packet)
{
}

void				Server::addContact(User *user, Packet *packet)
{
}

void				Server::removeContact(User *user, Packet *packet)
{
}

void				Server::blockContact(User *user, Packet *packet)
{
}

void				Server::chat(User *user, Packet *packet)
{
}

void				Server::error(User *user, Packet *packet)
{
}

void				Server::handshake(User *user, Packet *packet)
{
}

void				Server::ping(User *user, Packet *packet)
{
}