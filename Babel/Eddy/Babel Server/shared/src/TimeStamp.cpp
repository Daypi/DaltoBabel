#include		"TimeStamp.h"
#include		"LibC.h"

TimeStamp::TimeStamp()
{
	this->_previousTime = 0;
	this->_previousTime = 0;
	this->_actualTime = LibC::time(0);
}

TimeStamp::~TimeStamp()
{
}

time_t		TimeStamp::elapsedTime()
{
	this->_previousTime = this->_actualTime;
	this->_actualTime = LibC::time(0);
	return (this->_actualTime - this->_previousTime);
}
