#pragma					once

#include				<sys/types.h>
#include				<sys/socket.h>
#include				<netinet/in.h>
#include				<arpa/inet.h>
#include				"ISocket.hh"

typedef struct sockaddr			SOCKADDR;

class					CUSocket : public ISocket
{
protected:
	ISocket::TypeSocket	_type;
	int				_sock;
	sockaddr_in			_info;
	int					_sizeInfo;
	FuncSocket			_func;
	CUSocket			*_sockUdpSrv;
	CUSocket(CUSocket *socketSrv);
	CUSocket(ISocket::TypeSocket type, bool isClient);
public:
	CUSocket(ISocket::TypeSocket type = ISocket::TCP);
	virtual				~CUSocket();
	virtual void		bind(const char *ipAddress, int port);
	virtual void		connect(const char *ipAddress, int port);
	virtual void		listen(int nbConnexion);
	virtual ISocket		*accept();
	virtual void		send(const char *message, int size);
	virtual ISocket		*receivUdp(char *message, int size, int *received);
	virtual void		receiv(char *message, int size, int *received);
	virtual void		closeSocket();
	virtual void		setSocket(int sock);
	virtual void		setInfo(sockaddr_in info);
	virtual sockaddr_in	getInfo() const;
	virtual int			getSocket() const;
};
