#pragma once

#include <pthread.h>
#include <errno.h>
#include "IMutex.h"

class				CUMutex : public IMutex
{
protected:
	pthread_mutex_t	_mutex;

public:
	CUMutex();
	~CUMutex();

	void			lock();
	void			unLock();
	bool			tryLock();
	pthread_mutex_t		*getMutex();
};

