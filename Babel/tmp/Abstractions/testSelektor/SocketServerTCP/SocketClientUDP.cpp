#include "SocketClientUDP.h"

SocketClientUDP::SocketClientUDP()
{
	this->_sock = NULL;
}

SocketClientUDP::~SocketClientUDP()
{
	this->_socketPool.getMutex()->lock("SELEKTOR");
	delete this->_th;
	delete this->_sock;
	this->_socketPool.getMutex()->unLock("SELEKTOR");
}

void	SocketClientUDP::init(int port, const char *ipAddress)
{
	this->_th = new Thread<SeleKtor, void, void *>(&this->_socketPool, &SeleKtor::routineNetwork, NULL);
	this->_socketPool.getMutex()->lock("SELEKTOR");
	try
	{
		this->_sock = new SocketAvd(this->_th, &this->_socketPool, ISocket::UDP);
	}
	catch (const Exception& e)
	{
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}

	try
	{
	  this->_sock->connect(ipAddress, port);
	}
	catch (const Exception& e)
	{
		this->close();
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
}

bool	SocketClientUDP::isReadable()
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

bool	SocketClientUDP::isWritable()
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

void	SocketClientUDP::send(const char *message, int size)
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
		catch (const Exception& e)
		{
			this->close();
			this->_socketPool.getMutex()->unLock("SELEKTOR");
			throw e;
		}
	}
	else
	{
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw Exception("isAllowWritable is false.");
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
}

char	*SocketClientUDP::recv(char *buffer, int size, int *received)
{
	*received = 0;
	this->_socketPool.getMutex()->lock("SELEKTOR");
	memset(buffer, 0, size);
	try
	{
		this->_sock->receiv(buffer, size, received);
		this->_sock->iReaded();
	}
	catch (const Exception& e)
	{
		this->close();
		this->_socketPool.getMutex()->unLock("SELEKTOR");
		throw e;
	}
	this->_socketPool.getMutex()->unLock("SELEKTOR");
	return (buffer);
}

void	SocketClientUDP::close()
{
	try
	{
		this->_sock->closeSocketAvd();
	}
	catch (const Exception& e)
	{
		throw e;
	}
}
