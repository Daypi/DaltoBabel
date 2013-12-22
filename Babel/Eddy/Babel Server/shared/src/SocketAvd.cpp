#include "SocketAvd.hh"
#include "SeleKtor.hh"

SocketAvd::SocketAvd(Thread<SeleKtor, void, void *> *thread, SeleKtor *pool, ISocket::TypeSocket type) : Socket(type)
{
	this->_isReadable = false;
	this->_isWritable = false;
	this->_allowWritable = false;
	this->_isSend = false;
	this->_isRead = false;
	this->_askWritable = false;
	if (pool->getNbSocket() == 0)
	  {
	    pool->addSocket(this);
		thread->start();
	  }
	else
	  pool->addSocket(this);
	this->_pool = pool;
}

SocketAvd::~SocketAvd()
{

}

void		SocketAvd::init(Thread<SeleKtor, void, void *> *thread, SeleKtor *pool)
{
	this->_isReadable = false;
	this->_isWritable = false;
	this->_allowWritable = false;
	this->_isSend = false;
	this->_isRead = false;
	this->_askWritable = false;
	if (pool->getNbSocket() == 0)
	  {
	    pool->addSocket(this);
		thread->start();
	  }
	else
	  pool->addSocket(this);
	this->_pool = pool;
}

bool		SocketAvd::isWritable()
{
	if (this->_isWritable == true)
		this->_askWritable = true;
	return (this->_isWritable);
}

bool		SocketAvd::isReadable()
{
	return (this->_isReadable);
}

bool		SocketAvd::isAllowWritable()
{
	return (this->_allowWritable);
}


void		SocketAvd::setWritable(bool value)
{
	this->_isWritable = value;
}

void		SocketAvd::setReadable(bool value)
{
	this->_isReadable = value;
}

void		SocketAvd::setAllowWritable(bool value)
{
	this->_allowWritable = value;
}

void		SocketAvd::setSended(bool value)
{
	this->_isSend = value;
}

bool		SocketAvd::isSended()
{
	return (this->_isSend);
}

void		SocketAvd::closeSocketAvd()
{
	this->_pool->clearWrite(*this);
	this->_pool->delSocket(this);
	if ((this->_sock != -1) && (FUNCCLOSESOCKET(this->_sock) != 0))
		throw Exception("closesocket of sock has failed.");
}

bool				SocketAvd::isRead()
{
	return (this->_isRead);
}

void				SocketAvd::setRead(bool value)
{
	this->_isRead = value;
}

bool				SocketAvd::getAskWritable()
{
	return (this->_askWritable);
}

void				SocketAvd::setAskWritable(bool value)
{
	this->_askWritable = value;
}

void				SocketAvd::iReaded()
{
  this->_isRead = true;
  this->_pool->clearWrite(*this);
  this->setReadable(false);
  this->setWritable(true);
  this->setAllowWritable(false);
  this->setAskWritable(false);
}

void				SocketAvd::iSended()
{
	this->_isSend = true;
	this->_pool->clearWrite(*this);
	this->setReadable(false);
	this->setWritable(true);
	this->setAllowWritable(false);
	this->setAskWritable(false);
}
