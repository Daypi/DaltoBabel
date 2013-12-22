#pragma once

#ifdef _WIN32

# include	"CWThread.hpp"
template <typename T, typename U, typename V>
class Thread : public CWThread<T, U, V>
{
public:
	Thread(T *obj, callBack func, V param) : CWThread(obj, func, param) {}
	virtual ~Thread() {}
};

#else

# include	"CUThread.hpp"
template <typename T, typename U, typename V>
class Thread : public CUThread<T, U, V>
{
private:
typedef U(T::*callBack)(V);
public:
  Thread(T *obj, callBack func, V param) : CUThread<T, U, V>(obj, func, param) {}
	virtual ~Thread() {}
};

#endif // _WIN32
