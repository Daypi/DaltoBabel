#include "CWCondVar.h"
#include "Exception.h"

CWCondVar::CWCondVar(Mutex &mutex) : _mutex(mutex)
{
	this->_lock = false;
	InitializeConditionVariable(&_cond);
}

CWCondVar::~CWCondVar()
{
}

void	CWCondVar::wait()
{
	this->_lock = true;
	if (!SleepConditionVariableCS(&_cond, _mutex.getMutex(), INFINITE))
		throw Exception("SleepConditionVariableCS failed");
}

void	CWCondVar::signal()
{
	if (this->_lock)
	{
		WakeConditionVariable(&_cond);
		this->_lock = false;
	}
}

void	CWCondVar::broadcast()
{
	WakeAllConditionVariable(&_cond);
}