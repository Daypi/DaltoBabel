#pragma once

#ifdef					_WIN32
#include				<Winsock2.h>
#endif

class					TimeStamp
{
	struct timeval		_previousTime;
	struct timeval		_actualTime;

public:
	TimeStamp();
	~TimeStamp();

	unsigned long		elapsedTime();
};