#pragma once

#include <string>
#include <map>
#include <vector>
#include <cstring>

#include "ISocketServer.h"
#include "SeleKtor.hh"
#include "Thread.hpp"

class	SocketServerUDP : public ISocketServer
{
	SocketAvd													*_sock;
	std::map<unsigned int, SocketAvd *>							_tabSock;
	std::vector<unsigned int>									_ids;
	std::map<unsigned int, std::pair<const char *, int> >		_map;
	unsigned int												_uid;
	SeleKtor													_socketPool;
	Thread<SeleKtor, void, void *>								*_th;
	std::vector<unsigned int>									_sendRet;
	std::pair<unsigned int, char *>								_ipPair;

public:
	SocketServerUDP();
	virtual ~SocketServerUDP();

	virtual	void			init(int, int);
	void					init(int);
	virtual	std::pair<unsigned int, char *>		&checkConnection();
	virtual	std::vector<unsigned int>&			isReadable();
	virtual	std::vector<unsigned int>&			isReadable(unsigned int);
	virtual	std::vector<unsigned int>&			isWritable();
	virtual	std::vector<unsigned int>&			isWritable(unsigned int);
	virtual	std::vector<unsigned int>&			send(std::vector<unsigned int>& tab, const char *, int);
	virtual	std::vector<unsigned int>&			send(unsigned int, const char *, int);
	std::map<unsigned int, std::pair<const char *, int> >&	recv(int);
	virtual	std::map<unsigned int, std::pair<const char *, int> >&	recv(std::vector<unsigned int>& tab, int);
	virtual	std::map<unsigned int, std::pair<const char *, int> >&	recv(unsigned int, int);
	virtual void	closeClient(unsigned int id);
    void            closeClients();
	virtual void	closeServer();
	virtual void	eraseClient(unsigned int id);
	virtual void	deleteMap();
	bool			checkClientUDP(sockaddr_in one, sockaddr_in two);
	bool	isIAmReadable();
};
