#pragma once

#include <pthread.h>
#include "ICondVar.h"
#include "Mutex.h"

class	CUCondVar : public ICondVar
{
	Mutex			&_mutex;
	pthread_cond_t	_cond;

public:
	CUCondVar(Mutex &);
	virtual			~CUCondVar();

	virtual void	wait();
	virtual void	signal();
	virtual void	broadcast();
};