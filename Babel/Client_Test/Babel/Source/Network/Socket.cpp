#include "Include/Network/Socket.hh"

Socket::Socket(ISocket::TypeSocket type) : CSocket(type)
{

}

Socket::~Socket()
{

}

int		Socket::select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout)
{
	return (::select(nfds, readfds, writefds, errorfds, timeout));
}
