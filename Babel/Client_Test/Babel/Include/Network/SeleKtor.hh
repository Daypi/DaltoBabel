#pragma once

#include <map>
#include "SocketAvd.hh"
#include "MutexPool.h"
#include "CondVar.hh"

#ifdef _WIN32
# define SLEEP_ABSTRACT(x)	Sleep(1)
#else
# include <unistd.h>
# define SLEEP_ABSTRACT(x)	usleep(1001 - x)
#endif // !WIN

class SeleKtor
{
	std::map<unsigned int, SocketAvd *> _sockets;
	unsigned int							_uid;
	MutexPool							_mutex;
	CondVar								*_condVar;
	fd_set								_wfds;
	fd_set								_rfds;

	void								initFdSet(unsigned int *max);
	void								checkFdSet(fd_set *rfds_tmp, fd_set *wfds_tmp);
public:
	SeleKtor();
	virtual ~SeleKtor();
	void								addSocket(SocketAvd *socket);
	void								delSocket(SocketAvd *socket);
	void								routineNetwork(void *param);
	MutexPool							*getMutex();
	unsigned int							getNbSocket();
	CondVar								&getCondVar();
	void								clearWrite(SocketAvd &sock);
};

