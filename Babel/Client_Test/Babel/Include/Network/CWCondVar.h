#pragma once

#include <Windows.h>
#include "ICondVar.h"
#include "Mutex.h"

class	CWCondVar : public ICondVar
{
	Mutex				&_mutex;
	CONDITION_VARIABLE	_cond;
	bool				_lock;

public:
	CWCondVar(Mutex &);
	virtual			~CWCondVar();

	virtual void	wait();
	virtual void	signal();
	virtual void	broadcast();
};