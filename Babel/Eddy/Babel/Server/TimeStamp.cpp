#include		"TimeStamp.h"

#ifdef		_WIN32

int					gettimeofday(struct timeval *p, void *tz)
{
	ULARGE_INTEGER	ul;
	FILETIME		ft;

	GetSystemTimeAsFileTime(&ft);
	ul.LowPart = ft.dwLowDateTime;
	ul.HighPart = ft.dwHighDateTime;
	ul.QuadPart /= 10ULL;
	ul.QuadPart -= 11644473600000000ULL;
	p->tv_usec = (long)(ul.QuadPart % 1000000LL);
	p->tv_sec = (long)(ul.QuadPart / 1000000LL);
	return 0;
}

#else
#include <sys/time.h>

#endif

TimeStamp::TimeStamp()
{
	this->_previousTime.tv_sec = 0;
	this->_previousTime.tv_usec = 0;
	gettimeofday(&this->_actualTime, 0);
}

TimeStamp::~TimeStamp()
{
}

unsigned long		TimeStamp::elapsedTime()
{
	this->_previousTime = this->_actualTime;
	gettimeofday(&this->_actualTime, 0);
	return (this->_actualTime.tv_usec - this->_previousTime.tv_usec);
}
