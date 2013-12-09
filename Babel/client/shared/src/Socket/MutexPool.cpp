#include "MutexPool.h"

MutexPool::MutexPool()
{
}

MutexPool::~MutexPool()
{
	this->_mutex.erase(_mutex.begin(), this->_mutex.end());
}

bool	MutexPool::init(const std::string &name)
{
	if (_mutex.find(name) != _mutex.end())
		return false;
	this->_mutex[name] = new Mutex;
	return true;
}

bool	MutexPool::destroy(const std::string &name)
{
	if (_mutex.find(name) == _mutex.end())
		return false;
	_mutex.erase(_mutex.find(name));
	return true;
}

bool	MutexPool::lock(const std::string &name)
{
	if (_mutex.find(name) == _mutex.end())
		return false;
	this->_mutex[name]->lock();
	return true;
}

bool	MutexPool::unLock(const std::string &name)
{
	if (_mutex.find(name) == _mutex.end())
		return false;
	this->_mutex[name]->unLock();
	return true;
}

bool	MutexPool::tryLock(const std::string &name)
{
	if (_mutex.find(name) == _mutex.end())
		return false;
	return (this->_mutex[name]->tryLock());
}

Mutex	&MutexPool::getMutex(const std::string &name)
{
	if (_mutex.find(name) != _mutex.end())
		return (*this->_mutex[name]);
	else
	  throw Exception("MUTEX NOT FOUND");
}
