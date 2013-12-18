#pragma once

#include <Windows.h>
#include "IThread.h"

template <typename T, typename U, typename V>
class				CWThread : public IThread
{
protected:
	typedef			U (T::*callBack)(V);

	HANDLE			_thread;
	DWORD			_id;
public:
	callBack		_func;
	T				*_obj;
	V				_param;
	bool			_running;

	CWThread(T *obj, callBack func, V param)
		: _running(false), _func(func), _obj(obj), _param(param)
	{}

	CWThread(const CWThread& copy)
		: _running(false), _func(copy._func), _obj(copy._obj), _param(copy._param)
	{}

	virtual ~CWThread() {}

	CWThread&		operator=(const CWThread& other)
	{
		if (this != &other)
		{
			this->_running = other._running;
			this->_func = other._func;
			this->_obj = other._obj;
			this->_param = other._param;
		}
		return (*this);
	}

	virtual void		start()
	{
		_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&startThread<T, U, V>, this, 0, &_id);
	}

	virtual void		join()
	{
		WaitForSingleObject(_thread, INFINITE);
	}

	virtual void		stop()
	{
		TerminateThread(_thread, _id);
	}
};

template <typename T, typename U, typename V>
void				*startThread(void *arg)
{
	CWThread<T, U, V>	*tmp = reinterpret_cast<CWThread<T, U, V> *>(arg);

	tmp->_running = true;
	(tmp->_obj->*(tmp->_func))(tmp->_param);
	tmp->_running = false;

	return (NULL);
}