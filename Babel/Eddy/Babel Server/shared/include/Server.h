#pragma once

#include				<string>
#include													<vector>
#include													"Packet.h"
#include													"UserCollection.h"
#include													"SocketServerTCP.h"
#include													"AccountManager.h"

class														Server
{
	int														_port;
	int														_nbListen;
	bool													_started;
	UserCollection											_userCollection;
	AccountManager											_accountManager;

	SocketServerTCP											_sockTCP;
	std::queue<std::pair<Packet *, unsigned int> >			_toSendTCP;
	std::map<unsigned int, std::pair<const char *, int> >	_received;
	std::vector<unsigned int>								_clientList;

	typedef void (Server::*instructionPtr)(User *, Packet *);

	std::vector<Server::instructionPtr>						_instruction;

public:
	Server(int, int);
	~Server();

	void													start();
	void													stop();
	
	Packet													*getPacket(User *);
	void													sendTCP();

	// Instruction methods
	void													list(User *, Packet *);
	void													call(User *, Packet *);
	void													hangUp(User *, Packet *);
	void													statusText(User *, Packet *);
	void													status(User *, Packet *);
	void													acceptCall(User *, Packet *);
	void													rejectCall(User *, Packet *);
	void													login(User *, Packet *);
	void													createAccount(User *, Packet *);
	void													addContact(User *, Packet *);
	void													removeContact(User *, Packet *);
	void													blockContact(User *, Packet *);
	void													chat(User *, Packet *);
	void													error(User *, Packet *);
	void													handshake(User *, Packet *);
	void													ping(User *, Packet *);

	/*
	void													sendMsg(const User&, const Account&, const std::string&);
	void													wizz(const User&, const Account&);
	void													changeStatus(const User&);*/
};