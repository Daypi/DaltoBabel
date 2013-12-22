#include "CWMutex.h"
#include <iostream>
CWMutex::CWMutex()
{
	InitializeCriticalSection(&_mutex);
}

CWMutex::~CWMutex()
{
	DeleteCriticalSection(&_mutex);
}

void	CWMutex::lock()
{
	EnterCriticalSection(&_mutex);
}

void	CWMutex::unLock()
{
	LeaveCriticalSection(&_mutex);
}

bool	CWMutex::tryLock()
{
	return (TryEnterCriticalSection(&_mutex));
}

CRITICAL_SECTION	*CWMutex::getMutex()
{
	return (&this->_mutex);
}
