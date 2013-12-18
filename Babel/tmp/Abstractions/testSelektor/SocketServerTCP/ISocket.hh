#pragma					once
#include				<iostream>
#include				<stdio.h>
#include				"Exception.h"

class					ISocket
{
protected:
	enum FuncSocket
	{
		SERVER,
		CLIENT,
		NONE
	};
public:
	enum TypeSocket
	{
		UDP,
		TCP
	};
	virtual				~ISocket() {}
	virtual void		bind(int port) = 0;
	virtual void		connect(const char *ipAddress, int port) = 0;
	virtual void		listen(int nbConnexion) = 0;
	virtual ISocket		*accept() = 0;
	virtual void		send(const char *message, int size) = 0;
	virtual ISocket		*receivUdp(char *message, int size, int *received) = 0;
	virtual void		receiv(char *message, int size, int *received) = 0;
	virtual void		closeSocket() = 0;
};
