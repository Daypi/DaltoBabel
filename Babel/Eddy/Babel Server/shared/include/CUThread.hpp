#pragma once

#include <cerrno>
#include <pthread.h>
#include "IThread.h"

template <typename T, typename U, typename V>
void			*startThread(void *);

template <typename T, typename U, typename V>
class				CUThread : public  IThread
{
protected:
	typedef U(T::*callBack)(V);

	pthread_t		_thread;

public:
	callBack		_func;
	T				*_obj;
	V				_param;

	CUThread(T *obj, callBack func, V param)
	{
		this->_func = func;
		this->_obj = obj;
		this->_param = param;
	}

	CUThread(const CUThread& copy)
		: _func(copy._func), _obj(copy._obj), _param(copy._param)
	{}

	virtual ~CUThread()
	{}

	CUThread&		operator=(const CUThread& other)
	{
		if (this != &other)
		{
			this->_func = other._func;
			this->_obj = other._obj;
			this->_param = other._param;
		}
		return (*this);
	}

	void			start()
	{
		pthread_create(&this->_thread, NULL, startThread<T, U, V>, this);
	}

	void			join()
	{
		pthread_join(this->_thread, NULL);
	}

	bool			tryJoin()
	{
		if (pthread_tryjoin_np(this->_thread, NULL) == EBUSY)
			return (false);
		return (true);
	}

	void			stop()
	{
		pthread_exit(NULL);
	}
};

template <typename T, typename U, typename V>
void				*startThread(void *arg)
{
	CUThread<T, U, V>	*tmp = reinterpret_cast<CUThread<T, U, V> *>(arg);

	(tmp->_obj->*(tmp->_func))(tmp->_param);
	return (NULL);
}
