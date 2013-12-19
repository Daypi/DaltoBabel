#include "SocketServerUDP.h"

SocketServerUDP::SocketServerUDP()
{
	this->_uid = 0;
}

SocketServerUDP::~SocketServerUDP()
{

}

void	SocketServerUDP::init(int port, int nbListen)
{
	(void)nbListen;
	return (this->init(port));
}
void	SocketServerUDP::init(int port)
{
	this->_th = new Thread<SeleKtor, void, void *>(&this->_socketPool, &SeleKtor::routineNetwork, NULL);
	this->_socketPool.getMutex()->lock("SELEKTOR");
	try
	{
		this->_sock = new SocketAvd(this->_th, &this->_socketPool, ISocket::UDP);
	}
	catch (Exception &e)
	{
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}

	try
	{
		this->_sock->bind(port);
	}
	catch (Exception &e)
	{
		this->closeServer();
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
}

std::pair<unsigned int, char *>	&SocketServerUDP::checkConnection()
{
	this->_ipPair = std::pair<unsigned int, char *>(this->_uid, "127.0.0.1");
	return (this->_ipPair);
}

bool	SocketServerUDP::isIAmReadable()
{
	this->_socketPool.getMutex()->lock("SELEKTOR");
	if (this->_sock->isReadable())
	{
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		return (true);
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (false);
}

std::vector<unsigned int>&	SocketServerUDP::isReadable()
{
	this->_ids.clear();
	this->_socketPool.getMutex()->lock("SELEKTOR");
	if (this->_sock->isReadable())
		this->_ids.push_back(0);

	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (this->_ids);
}

std::vector<unsigned int>&	SocketServerUDP::isReadable(unsigned int id)
{
	(void)id;
	return (this->isReadable());
}

std::vector<unsigned int>&	SocketServerUDP::isWritable()
{
	std::map<unsigned int, SocketAvd *>::iterator it_bis;

	this->_ids.clear();
	this->_socketPool.getMutex()->lock("SELEKTOR");
	if (this->_sock->isWritable())
		for(it_bis = this->_tabSock.begin(); it_bis != this->_tabSock.end() ; ++it_bis)
			this->_ids.push_back(it_bis->first);
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (this->_ids);
}

std::vector<unsigned int>&	SocketServerUDP::isWritable(unsigned int id)
{
	(void)id;
	return (this->isWritable());
}

std::vector<unsigned int>&	SocketServerUDP::send(std::vector<unsigned int>& tab, const char* message, int size)
{
	std::vector<unsigned int>::iterator	it;

	for (it = tab.begin(); it != tab.end(); ++it)
	{
		this->_socketPool.getMutex()->lock("SELEKTOR");
		this->_socketPool.getCondVar().wait();
		if (this->_sock->isAllowWritable() == true)
		{
			try
			{
				this->_tabSock[*it]->send(message, size);
				this->_sock->iSended();
			}
			catch (Exception)
			{
				this->eraseClient(*it);
				this->_sendRet.push_back(*it);
			}
		}
		else
		{
			this->_socketPool.getMutex()->unLock("SELEKTOR");
			throw Exception("isAllowWritable is false.");
		}
		this->_socketPool.getMutex()->unLock("SELEKTOR");
	}
	return (this->_sendRet);
}

std::vector<unsigned int>&	SocketServerUDP::send(unsigned int id, const char *message, int size)
{
	if (id <= this->_uid && (id != 0))
	{
		this->_socketPool.getMutex()->lock("SELEKTOR");
		this->_socketPool.getCondVar().wait();
		if (this->_sock->isAllowWritable() == true)
		{
			try
			{
				this->_tabSock[id]->send(message, size);
				this->_sock->iSended();
			}
			catch (Exception)
			{
				this->eraseClient(id);
				this->_sendRet.push_back(id);
			}
		}
		else
		{
			this->_socketPool.getMutex()->unLock("SELEKTOR");
			throw Exception("isAllowWritable is false.");
		}
		this->_socketPool.getMutex()->unLock("SELEKTOR");
	}
	return (this->_sendRet);
}

std::map<unsigned int, std::pair<const char *, int>>&	SocketServerUDP::recv(int size)
{
	char						buffer[4096];
	SocketAvd					*tmpCasted;
	std::map<unsigned int, SocketAvd *>::iterator it_bis;
	ISocket *tmp;
	int		tmp_read = 0;
	char	*tmp_receiv;

	this->_socketPool.getMutex()->lock("SELEKTOR");
	this->deleteMap();
	memset(buffer, 0, size);
	try
	{
		tmp = this->_sock->receivUdp(buffer, size, &tmp_read);
		this->_sock->iReaded();
	}
	catch (Exception &e)
	{
		this->_sock->iReaded();
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}

	if ((tmpCasted = reinterpret_cast<SocketAvd *>(tmp)) == NULL)
	{
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw Exception("Init new socket has failed in receivUDP.");
	}
	for (it_bis = this->_tabSock.begin(); it_bis != this->_tabSock.end(); ++it_bis)
	{
		if (this->checkClientUDP(tmpCasted->getInfo(), it_bis->second->getInfo()))
		{
			tmp_receiv = new char[tmp_read + 1];
			memset(tmp_receiv, 0, tmp_read + 1);
			memcpy(tmp_receiv, buffer, tmp_read);
			this->_map[it_bis->first] = std::pair<const char *, int>(tmp_receiv, tmp_read);
			break;
		}
	}
	if (it_bis == this->_tabSock.end())
	{
		++this->_uid;
		this->_tabSock[this->_uid] = tmpCasted;
		tmp_receiv = new char[tmp_read + 1];
		memset(tmp_receiv, 0, tmp_read + 1);
		memcpy(tmp_receiv, buffer, tmp_read);
		this->_map[this->_uid] = std::pair<const char *, int>(tmp_receiv, tmp_read);
	}
	else
		delete (tmpCasted);
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (this->_map);
}

std::map<unsigned int, std::pair<const char *, int>>&	SocketServerUDP::recv(std::vector<unsigned int>& tab, int size)
{
	(void)tab;
	return (this->recv(size));
}

std::map<unsigned int, std::pair<const char *, int>>&	SocketServerUDP::recv(unsigned int id, int size)
{
	(void)id;
	return (this->recv(size));
}

void	SocketServerUDP::closeServer()
{
	try
	{
		this->_sock->closeSocketAvd();
	}
	catch (Exception &e)
	{
		throw e;
	}
}

void	SocketServerUDP::closeClient(unsigned int id)
{
	if ((id <= this->_uid) && (id != 0))
	{
		try
		{
			this->_tabSock[id]->closeSocket();
		}
		catch (Exception &e)
		{
			throw e;
		}
	}
}

void	SocketServerUDP::eraseClient(unsigned int id)
{
	std::map<unsigned int, SocketAvd *>::iterator it;

	if ((id <= this->_uid) && (id != 0))
	{
		for (it = this->_tabSock.begin(); it != this->_tabSock.end(); it++)
		{
			if (id == it->first)
			{
				this->_tabSock.erase(it);
				break;
			}
		}
	}
}

bool			SocketServerUDP::checkClientUDP(sockaddr_in one, sockaddr_in two)
{
	if (memcmp(((SOCKADDR *)&one)->sa_data, ((SOCKADDR *)&two)->sa_data, 14))
		return (false);
	return (true);
}

void		SocketServerUDP::deleteMap()
{
	std::map<unsigned int, std::pair<const char *, int>>::iterator	it;

	for (it = this->_map.begin(); it != this->_map.end(); ++it)
		delete (it->second.first);
	this->_map.clear();
}
