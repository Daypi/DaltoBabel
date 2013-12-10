#pragma once

#include <string>
#include <map>
#include <vector>

#include "ISocketServer.h"
#include "SeleKtor.hh"
#include "Thread.hpp"

class	SocketServerTCP : public ISocketServer
{
	SocketAvd													*_sock;
	std::map<unsigned int, SocketAvd *>							_tabSock;
	std::vector<unsigned int>									_ids;
	std::map<unsigned int, std::pair<const char *, int>>		_map;
	unsigned int												_uid;
	SeleKtor													_socketPool;
	Thread<SeleKtor, void, void *>								*_th;
	std::vector<unsigned int>									_sendRet;

	char														*getMyIpAddr();
	void														bindAvd(int port);
public:
	SocketServerTCP();
	virtual ~SocketServerTCP();

	virtual	void			init(int, int);
	virtual	unsigned int	checkConnection();
	virtual	std::vector<unsigned int>&	isReadable();
	virtual	std::vector<unsigned int>&	isReadable(unsigned int);
	virtual	std::vector<unsigned int>&	isWritable();
	virtual	std::vector<unsigned int>&	isWritable(unsigned int);
	virtual	std::vector<unsigned int>&	send(std::vector<unsigned int>& tab, const char *, int);
	virtual	std::vector<unsigned int>&	send(unsigned int, const char *, int);
	virtual	std::map<unsigned int, std::pair<const char *, int>>&	recv(std::vector<unsigned int>& tab, int);
	virtual	std::map<unsigned int, std::pair<const char *, int>>&	recv(unsigned int, int);
	virtual void	closeClient(unsigned int id);
	virtual void	closeServer();
	virtual void	eraseClient(unsigned int id);
	virtual void	deleteMap();
};
