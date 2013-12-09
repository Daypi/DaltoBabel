#pragma					once
#pragma comment(lib, "ws2_32.lib")
#include				"ISocket.hh"
#include				<winsock2.h>
#include				<windows.h>
#include				<ws2tcpip.h>

class					CWSocket : public ISocket
{
protected:
	ISocket::TypeSocket	_type;
	SOCKET				_sock;
	sockaddr_in			_info;
	int					_sizeInfo;
	bool				_isStartUp;
	FuncSocket			_func;
	CWSocket			*_sockUdpSrv;
	CWSocket(CWSocket *socketSrv);
	CWSocket(ISocket::TypeSocket type, bool isClient);
public:
	CWSocket(ISocket::TypeSocket type = ISocket::TCP);
	virtual				~CWSocket();
	virtual void		bind(int port);
	virtual void		connect(const char *ipAddress, int port);
	virtual void		listen(int nbConnexion);
	virtual ISocket		*accept();
	virtual void		send(const char *message, int size);
	virtual ISocket		*receivUdp(char *message, int size, int *received);
	virtual void		receiv(char *message, int size, int *received);
	virtual void		closeSocket();
	virtual void		setSocket(SOCKET sock);
	virtual void		setInfo(sockaddr_in info);
	virtual sockaddr_in	getInfo() const;
	virtual SOCKET		getSocket() const;
};
