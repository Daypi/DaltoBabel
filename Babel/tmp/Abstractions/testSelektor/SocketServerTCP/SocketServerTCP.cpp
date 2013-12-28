#include "SocketServerTCP.h"

SocketServerTCP::SocketServerTCP()
{
	this->_uid = 0;
}

SocketServerTCP::~SocketServerTCP()
{

}

void	SocketServerTCP::init(int port, int nbListen)
{
	this->_th = new Thread<SeleKtor, void, void *>(&this->_socketPool, &SeleKtor::routineNetwork, NULL);
	this->_socketPool.getMutex()->lock("SELEKTOR");
	try
	{
		this->_sock = new SocketAvd(this->_th, &this->_socketPool, ISocket::TCP);
	}
	catch (const Exception& e)
	{
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}

	try
	{
		this->_sock->bind(port);
		this->_sock->listen(nbListen);
	}
	catch (const Exception& e)
	{
		this->closeServer();
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
}

std::pair<unsigned int, char *>	&SocketServerTCP::checkConnection()
{
	ISocket		*tmp;
	SocketAvd	*tmpCasted;

	this->_socketPool.getMutex()->lock("SELEKTOR");
	try
	{
		tmp = this->_sock->accept();
	}
	catch (const Exception& e)
	{
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}

	this->_sock->iReaded();
	if ((tmpCasted = reinterpret_cast<SocketAvd *>(tmp)) == NULL)
	{
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw Exception("Init new socket has failed in accept method.");
	}
	++this->_uid;
	this->_tabSock[this->_uid] = tmpCasted;
	this->_tabSock[this->_uid]->init(this->_th, &this->_socketPool); //TODO EXECPTION
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	this->_ipPair = std::pair<unsigned int, char *>(this->_uid, inet_ntoa(this->_tabSock[this->_uid]->getInfo().sin_addr));
	return (this->_ipPair);
}

std::vector<unsigned int>&	SocketServerTCP::isReadable()
{
	std::map<unsigned int, SocketAvd *>::iterator	it;

	this->_ids.clear();
	this->_socketPool.getMutex()->lock("SELEKTOR");
	if (this->_sock->isReadable())
		this->_ids.push_back(0);
	for (it = this->_tabSock.begin(); it != this->_tabSock.end(); ++it)
	{
		if (it->second->isReadable())
			this->_ids.push_back(it->first);
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (this->_ids);
}

std::vector<unsigned int>&	SocketServerTCP::isReadable(unsigned int id)
{
	this->_ids.clear();
	this->_socketPool.getMutex()->lock("SELEKTOR");
	if ((id == 0) && (this->_sock->isReadable()))
	{
		this->_ids.push_back(0);
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		return (this->_ids);
	}
	else if ((id <= this->_uid) && (id != 0) && (this->_tabSock.find(id) != this->_tabSock.end()) && (this->_tabSock[id]->isReadable()))
		this->_ids.push_back(id);
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (this->_ids);
}

std::vector<unsigned int>&	SocketServerTCP::isWritable()
{
	this->_ids.clear();
	this->_socketPool.getMutex()->lock("SELEKTOR");
	if (this->_sock->isWritable())
		this->_ids.push_back(0);
	for (unsigned int i = 0; i < this->_uid; ++i)
	{
		if (this->_tabSock[i]->isWritable())
			this->_ids.push_back(i);
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (this->_ids);
}

std::vector<unsigned int>&	SocketServerTCP::isWritable(unsigned int id)
{
	this->_ids.clear();
	this->_socketPool.getMutex()->lock("SELEKTOR");
	if ((id == 0) && (this->_sock->isWritable()))
	{
		this->_ids.push_back(0);
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		return (this->_ids);
	}
	else if ((id <= this->_uid) && (id != 0) && (this->_tabSock.find(id) != this->_tabSock.end()) && (this->_tabSock[id]->isWritable()))
		this->_ids.push_back(id);
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (this->_ids);
}

std::vector<unsigned int>	&SocketServerTCP::send(std::vector<unsigned int>& tab, const char *message, int size)
{
	std::vector<unsigned int>::iterator	it;

	for (it = tab.begin(); it != tab.end(); ++it)
	{
		this->_socketPool.getMutex()->lock("SELEKTOR");
		this->_socketPool.getCondVar().wait();
		if (this->_tabSock[*it]->isAllowWritable() == true)
		{
			try
			{
				this->_tabSock[*it]->send(message, size);
				this->_tabSock[*it]->iSended();
			}
			catch (const Exception&)
			{
				this->closeClient(*it);
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

std::vector<unsigned int>	&SocketServerTCP::send(unsigned int id, const char *message, int size)
{
	if (this->_tabSock.find(id) == this->_tabSock.end())
		throw Exception("Client disconnected.");
	if (id <= this->_uid && (id != 0))
	{
		this->_socketPool.getMutex()->lock("SELEKTOR");
		this->_socketPool.getCondVar().wait();
		if (this->_tabSock[id]->isAllowWritable() == true)
		{
			try
			{
				this->_tabSock[id]->send(message, size);
				this->_tabSock[id]->iSended();
			}
			catch (const Exception&)
			{
				this->closeClient(id);
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

std::map<unsigned int, std::pair<const char *, int>>&	SocketServerTCP::recv(std::vector<unsigned int>& tab, int size)
{
	std::vector<unsigned int>::iterator	it;
	char	buffer[4096];
	int		tmp_read = 0;
	char	*tmp_receiv;

	this->deleteMap();
	this->_socketPool.getMutex()->lock("SELEKTOR");
	for(it = tab.begin(); it != tab.end(); ++it)
	{
		memset(buffer, 0, 4096);
		tmp_read = 0;
		try
		{
			this->_tabSock[*it]->receiv(buffer, size, &tmp_read);
			if (size == 0)
				throw Exception("Client disconnected.");
			this->_tabSock[*it]->iReaded();
			tmp_receiv = new char[tmp_read + 1];
			memset(tmp_receiv, 0, tmp_read + 1);
			memcpy(tmp_receiv, buffer, tmp_read);
			this->_map[*it] = std::pair<const char *, int>(tmp_receiv, tmp_read);
		}
		catch (const Exception&)
		{
			this->closeClient(*it);
			this->eraseClient(*it);
		}
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (this->_map);
}

std::map<unsigned int, std::pair<const char *, int>>&	SocketServerTCP::recv(unsigned int id, int size)
{
	char	buffer[4096];
	int		tmp_read = 0;
	char	*tmp_receiv;

	this->_socketPool.getMutex()->lock("SELEKTOR");
	memset(buffer, 0, 4096);
	this->deleteMap();
	try
	{
		this->_tabSock[id]->receiv(buffer, size, &tmp_read);
		if (size == 0)
			throw Exception("Client disconnected.");
		this->_tabSock[id]->iReaded();
		tmp_receiv = new char[tmp_read + 1];
		memset(tmp_receiv, 0, tmp_read + 1);
		memcpy(tmp_receiv, buffer, tmp_read);
		this->_map[id] = std::pair<const char *, int>(tmp_receiv, tmp_read);
	}
	catch (const Exception&)
	{
		this->closeClient(id);
		this->eraseClient(id);
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (this->_map);
}

void	SocketServerTCP::closeServer()
{
	std::map<unsigned int, SocketAvd *>::iterator it;

	if (this->_tabSock.size() != 0)
	{
		for (it = this->_tabSock.begin(); it != this->_tabSock.end(); it++)
		{
			try
			{
				it->second->closeSocketAvd();
			}
			catch (const Exception&)
			{
			}
		}
	}
	try
	{
		this->_sock->closeSocket();
	}
	catch (const Exception& e)
	{
		throw e;
	}
}

void	SocketServerTCP::closeClient(unsigned int id)
{
	if ((id <= this->_uid) && (id != 0))
	{
		try
		{
			this->_tabSock[id]->closeSocketAvd();
		}
		catch (const Exception& e)
		{
			throw e;
		}
	}
}

void	SocketServerTCP::eraseClient(unsigned int id)
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

void	SocketServerTCP::deleteMap()
{
	std::map<unsigned int, std::pair<const char *, int>>::iterator	it;

	for (it = this->_map.begin(); it != this->_map.end(); ++it)
		 delete (it->second.first);
	this->_map.clear();
}

std::map<unsigned int, char *>	*SocketServerTCP::getIP()
{
	std::map<unsigned int, SocketAvd *>::iterator	it;
	std::map<unsigned int, char *>					*mapIP = new std::map<unsigned int, char *>;

	mapIP->clear();
	for (it = this->_tabSock.begin(); it != this->_tabSock.end(); ++it)
	{
		(*mapIP)[(*it).first] = inet_ntoa((*it).second->getInfo().sin_addr);
	}
	return (mapIP);
}

void							SocketServerTCP::releaseClient(unsigned int id)
{
	std::map<unsigned int, SocketAvd *>::iterator	it;

	for (it = this->_tabSock.begin(); it != this->_tabSock.end(); ++it)
	{
		if (it->first == id)
		{
			this->_socketPool.getMutex()->lock("SELEKTOR");
			this->_socketPool.delSocket(it->second);
			this->_socketPool.getMutex()->unLock("SELEKTOR");
			this->closeClient(id);
			this->eraseClient(id);
			break;
		}
	}
}
