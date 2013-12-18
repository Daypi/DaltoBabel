#include "Include/Network/CUCondVar.h"
#include "Include/Network/Exception.h"

CUCondVar::CUCondVar(Mutex &mutex) : _mutex(mutex)
{
	if (pthread_cond_init(&_cond, NULL))
		throw Exception("pthread_cond_init failed");
}

CUCondVar::~CUCondVar()
{
	this->broadcast();
	pthread_cond_destroy(&_cond);
}

void	CUCondVar::wait()
{
	if (pthread_cond_wait(&this->_cond, this->_mutex.getMutex()))
		throw Exception("pthread_cond_wait failed");
}

void	CUCondVar::signal()
{
	if (pthread_cond_signal(&_cond))
		throw Exception("pthread_cond_signal failed");
}

void	CUCondVar::broadcast()
{
	if (pthread_cond_broadcast(&_cond))
		throw Exception("pthread_cond_broadcast failed");
}
