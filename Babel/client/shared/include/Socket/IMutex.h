#pragma once

#include <string>

class IMutex
{
public:
	virtual ~IMutex() {}

	virtual void	lock() = 0;
	virtual void	unLock() = 0;
	virtual bool	tryLock() = 0;
};
