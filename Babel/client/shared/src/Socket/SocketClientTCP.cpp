#include "SocketClientTCP.h"

SocketClientTCP::SocketClientTCP()
{
	this->_sock = NULL;
}

SocketClientTCP::~SocketClientTCP()
{
	this->_socketPool.getMutex()->lock("SELEKTOR");
	delete this->_th;
	delete this->_sock;
	this->_socketPool.getMutex()->unLock("SELEKTOR");
}

void	SocketClientTCP::init(int port, const char *ipAddress)
{
	this->_th = new Thread<SeleKtor, void, void *>(&this->_socketPool, &SeleKtor::routineNetwork, NULL);
	this->_socketPool.getMutex()->lock("SELEKTOR");
	try
	{
		this->_sock = new SocketAvd(this->_th, &this->_socketPool, ISocket::TCP);
	}
	catch (Exception e)
	{
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}

	try
	{
		this->_sock->connect(ipAddress, port);
	}
	catch (Exception &e)
	{
		this->close();
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
}

bool	SocketClientTCP::isReadable()
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

bool	SocketClientTCP::isWritable()
{
	this->_socketPool.getMutex()->lock("SELEKTOR");
	if (this->_sock->isWritable())
	{
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		return (true);
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (false);
}

void	SocketClientTCP::send(const char *message, int size)
{
	this->_socketPool.getMutex()->lock("SELEKTOR");
	this->_socketPool.getCondVar().wait();
	if (this->_sock->isAllowWritable() == true)
	{
		try
		{
			this->_sock->send(message, size);
			this->_sock->iSended();
		}
		catch (Exception &e)
		{
			this->close();
			this->_socketPool.getMutex()->unLock("SELEKTOR");
			throw e;
		}
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
}

char	*SocketClientTCP::recv(char *buffer, int size, int *received)
{
	*received = 0;
	this->_socketPool.getMutex()->lock("SELEKTOR");
	memset(buffer, 0, size);
	try
	{
		this->_sock->receiv(buffer, size, received);
		this->_sock->iReaded();
	}
	catch (Exception &e)
	{
		this->close();
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (buffer);
}

void	SocketClientTCP::close()
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
