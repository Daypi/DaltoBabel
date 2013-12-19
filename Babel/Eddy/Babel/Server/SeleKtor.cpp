#include <algorithm>
#include "SeleKtor.hh"

SeleKtor::SeleKtor()
{
	this->_uid = 0;
	this->_mutex.init("SELEKTOR");
	this->_condVar = new CondVar(this->_mutex.getMutex("SELEKTOR"));
	FD_ZERO(&this->_wfds);
	FD_ZERO(&this->_rfds);
	this->_sockets.clear();
}

SeleKtor::~SeleKtor()
{

}

void								SeleKtor::addSocket(SocketAvd *socket)
{
	this->_sockets[this->_uid] = socket;
	++this->_uid;
}

void								SeleKtor::delSocket(SocketAvd *socket)
{
	for (std::map<unsigned int, SocketAvd *>::iterator it = this->_sockets.begin(); it != this->_sockets.end(); ++it)
	{
		if (it->second == socket)
		{
			this->_sockets.erase(it->first);
			break;
		}
	}
}

void								SeleKtor::initFdSet(unsigned int *max)
{
	FD_ZERO(&this->_rfds);
	for (std::map<unsigned int, SocketAvd *>::iterator it = this->_sockets.begin(); it != this->_sockets.end(); ++it)
	{
		FD_SET(it->second->getSocket(), &this->_rfds);
		if ((it->second->isSended() == true) || (it->second->isRead() == true))
		{
			it->second->setSended(false);
			it->second->setRead(false);
		}
		if (it->second->isReadable() != true)
		{
			it->second->setWritable(true);
			if (it->second->getAskWritable() == true)
				FD_SET(it->second->getSocket(), &this->_wfds);
		}
		else
		{
			it->second->setWritable(false);
			it->second->setAllowWritable(false);
			if (it->second->getAskWritable() == true)
				it->second->setAskWritable(false);
		}
		*max = std::max<unsigned int>(*max, it->second->getSocket());
	}
}

void								SeleKtor::checkFdSet(fd_set *rfds_tmp, fd_set *wfds_tmp)
{
	for (std::map<unsigned int, SocketAvd *>::iterator it = this->_sockets.begin(); it != this->_sockets.end(); ++it)
	{
		if (FD_ISSET(it->second->getSocket(), rfds_tmp))
		{
			it->second->setReadable(true);
			it->second->setWritable(false);
			it->second->setRead(false);
			it->second->setSended(false);
			it->second->setAllowWritable(false);
			it->second->setAskWritable(false);
		}
		else if (FD_ISSET(it->second->getSocket(), wfds_tmp))
		{
			it->second->setReadable(false);
			it->second->setWritable(true);
			it->second->setRead(false);
			if (it->second->getAskWritable() == true)
				it->second->setAllowWritable(true);
		}
	}
	this->_condVar->signal();
}

void								SeleKtor::routineNetwork(void *param)
{
	struct timeval					timeout;
	unsigned int					max = 0;
	fd_set							wfds_tmp;
	fd_set							rfds_tmp;

	FD_ZERO(&this->_wfds);
	FD_ZERO(&this->_rfds);
	FD_ZERO(&wfds_tmp);
	FD_ZERO(&rfds_tmp);
	(void)param;
	while (42)
	{
		max = 0;
		timeout.tv_sec = 0;
		timeout.tv_usec = 1000;
		this->_mutex.lock("SELEKTOR");
		if (this->_sockets.size() <= 0)
		{
			this->_mutex.unLock("SELEKTOR");
			return;
		}
		initFdSet(&max);
		wfds_tmp = this->_wfds;
		rfds_tmp = this->_rfds;
		if (Socket::select(max + 1, &rfds_tmp, &wfds_tmp, NULL, &timeout) == -1)
		{
			std::cerr << "ERROR: select has failed. " << std::endl;
			this->_mutex.unLock("SELEKTOR");
			return;
		}
		checkFdSet(&rfds_tmp, &wfds_tmp);
		this->_mutex.unLock("SELEKTOR");
		SLEEP_ABSTRACT(timeout.tv_usec);
	}
}

MutexPool							*SeleKtor::getMutex()
{
	return (&this->_mutex);
}

unsigned int							SeleKtor::getNbSocket()
{
	return (this->_sockets.size());
}

CondVar								&SeleKtor::getCondVar()
{
	return (*this->_condVar);
}

void								SeleKtor::clearWrite(SocketAvd &sock)
{
	FD_CLR(sock.getSocket(), &this->_wfds);
}
