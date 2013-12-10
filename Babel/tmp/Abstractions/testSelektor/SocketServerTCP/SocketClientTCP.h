#pragma once

#include <string>
#include <map>
#include <vector>

#include "ISocketClient.h"
#include "SeleKtor.hh"
#include "Thread.hpp"

class	SocketClientTCP : public ISocketClient
{
	SocketAvd							*_sock;
	SeleKtor							_socketPool;
	Thread<SeleKtor, void, void *>		*_th;

	char								*getMyIpAddr();
	void								connectAvd(const char *ipAddress, int port);
public:
	SocketClientTCP();
	virtual ~SocketClientTCP();

	virtual	void	init(int, const char *);
	virtual	bool	isReadable();
	virtual	bool	isWritable();
	virtual	void	send(const char *, int);
	virtual	char	*recv(char *,int, int *);
	virtual	void	close();
};