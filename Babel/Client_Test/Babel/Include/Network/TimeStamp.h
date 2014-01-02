#pragma once

#include				<ctime>

class					TimeStamp
{
	time_t				_previousTime;
	time_t				_actualTime;

public:
	TimeStamp();
	~TimeStamp();

	time_t				elapsedTime(bool change = true);
};