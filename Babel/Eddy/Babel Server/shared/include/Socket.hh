#pragma		once

#ifdef _WIN32
# include "CWSocket.hh"
typedef	CWSocket CSocket;
#else
# include "CUSocket.hh"
typedef CUSocket CSocket;
#endif // !WIN

class Socket : public CSocket
{
public:
	Socket(ISocket::TypeSocket type = ISocket::TCP);
	virtual ~Socket();
	static int	select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout);
};
