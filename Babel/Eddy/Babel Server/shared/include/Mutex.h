#pragma once

#ifdef _WIN32
# include "CWMutex.h"
typedef	CWMutex	CMutex;
#else
# include "CUMutex.h"
typedef	CUMutex	CMutex;
#endif // _WIN32

class Mutex : public CMutex
{
public:
	Mutex();
	virtual ~Mutex();
};

