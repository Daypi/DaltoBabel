#pragma once

#include				<string>
#include													<vector>
#include													"Packet.h"
#include													"UserCollection.h"
#include													"Contact.h"
#include													"SocketServerTCP.h"

class														Server
{
	int														_port;
	int														_nbListen;
	bool													_started;
	UserCollection											_userCollection;
	User													*_currentUser;

	SocketServerTCP											_sockTCP;
	std::queue<std::pair<Packet *, unsigned int> >			_toSendTCP;
	std::map<unsigned int, std::pair<const char *, int> >	_received;
	std::vector<unsigned int>								_clientList;

	typedef void (Server::*instructionPtr)();

	std::vector<Server::instructionPtr>						_instruction;

public:

	enum						eInstruction
	{
		// MANDATORY
		LIST,
		CALL,
		HANGUP,
		// FEATURES
		STATUSTEXT,
		STATUS,
		ACCEPT_CALL,
		REJECT_CALL,
		LOGIN,
		CREATE_ACCOUNT,
		ADD_CONTACT,
		REMOVE_CONTACT,
		BLOCK_CONTACT,
		CHAT,
		ERROR_,
		HANDSHAKE,
		PING,
		ENUM_COUNT
	};

	Server(int, int);
	~Server();

	void													start();
	void													stop();
	
	Packet													*getPacket(User *);
	void													sendTCP();

	// Instruction methods
	void													list();
	void													call();
	void													hangUp();
	void													statusText();
	void													status();
	void													acceptCall();
	void													rejectCall();
	void													login();
	void													createAccount();
	void													addContact();
	void													removeContact();
	void													blockContact();
	void													chat();
	void													error();
	void													handshake();
	void													ping();

	void													addContact(const User&, const Contact&);
	void													rmContact(const User&, const Contact&);
	void													sendMsg(const User&, const Contact&, const std::string&);
	void													wizz(const User&, const Contact&);
	void													changeStatus(const User&);
};