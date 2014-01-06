#include "CUSocket.hh"

CUSocket::CUSocket(ISocket::TypeSocket type)
: _type(type)
{
	int		one = 1;

	this->_sock = -1;
	if ((this->_sock = socket(AF_INET, ((this->_type == ISocket::TCP) ? (SOCK_STREAM) : (SOCK_DGRAM)), 0)) == -1)
	{
		this->_sock = -1;
		throw Exception("socket has failed.");
	}
	this->_func = ISocket::NONE;
	this->_sockUdpSrv = NULL;
	if ((setsockopt(this->_sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int))) == -1)
		throw Exception("setsockopt has failed.");
}

CUSocket::CUSocket(ISocket::TypeSocket type, bool isClient)
  : _type(type)
{
	if (isClient == true)
		this->_func = ISocket::CLIENT;
	else
		this->_func = ISocket::SERVER;
	this->_sockUdpSrv = NULL;
	this->_sock = -1;
}

CUSocket::CUSocket(CUSocket *socketSrv)
: _type(ISocket::UDP)
{
	this->_func = ISocket::CLIENT;
	this->_sockUdpSrv = socketSrv;
	this->_sock = -1;
}

CUSocket::~CUSocket()
{

}

void		CUSocket::bind(int port)
{
	sockaddr_in			service;

	if (this->_func != ISocket::NONE)
		throw Exception(((this->_func == ISocket::CLIENT) ? ("this socket is client socket.") : ("this socket is already bind to server.")));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;
	service.sin_port = htons(port);
	this->_func = ISocket::SERVER;
	if (::bind(this->_sock, (SOCKADDR *)&service, sizeof(service)) != 0)
		throw Exception("bind has failed.");
}

void		CUSocket::connect(const char *ipAddress, int port)
{
	sockaddr_in			server_info;

	if (this->_func != ISocket::NONE)
		throw Exception(((this->_func == ISocket::SERVER) ? ("this socket is server socket.") : ("this socket is already connected to server.")));
	server_info.sin_family = AF_INET;
	server_info.sin_addr.s_addr = inet_addr(ipAddress);
	server_info.sin_port = htons(port);
	this->_func = ISocket::CLIENT;
	if (::connect(this->_sock, (SOCKADDR *)&server_info, sizeof(server_info)) != 0)
		throw Exception("connect has failed.");
}

void		CUSocket::listen(int nbConnexion)
{
	if (this->_type == ISocket::UDP)
		throw Exception("This socket type is UDP.");
	if (this->_func != ISocket::SERVER)
		throw Exception(((this->_func == ISocket::NONE) ? ("this socket isn't initialized.") : ("this socket isn't socket server.")));
	if (::listen(this->_sock, nbConnexion) != 0)
		throw Exception("listen thas failed.");
}

ISocket			*CUSocket::accept()
{
	sockaddr_in	tmpInfo;
	int			sizeTmp = sizeof(tmpInfo);
	int		tmp;
	CUSocket	*newSocket = new CUSocket(this->_type, true);

	if (this->_type == ISocket::UDP)
		throw Exception("This socket type is UDP.");
	if (this->_func != ISocket::SERVER)
		throw Exception(((this->_func == ISocket::NONE) ? ("this socket isn't initialized.") : ("this socket isn't socket server.")));
	if ((tmp = ::accept(this->_sock, (SOCKADDR*) &tmpInfo, (socklen_t *) &sizeTmp)) == -1)
		throw Exception("accept has failed.");
	newSocket->setSocket(tmp);
	newSocket->setInfo(tmpInfo);
	return (newSocket);
}

void		CUSocket::send(const char *message, int size)
{
	if (this->_func == ISocket::NONE)
		throw Exception("This socket type isn't initialized.");
	if ((this->_type == ISocket::TCP) || ((this->_func == ISocket::CLIENT) && (this->_sock != -1)))
	{
	  if (::send(this->_sock, message, size, 0) == -1)
			throw Exception("send has failed.");
	}
	else
	{
		if (!this->_sockUdpSrv)
			throw Exception("Socket server UDP invalid for sending client message.");
		if (::sendto(this->_sockUdpSrv->_sock, message, size, 0, (SOCKADDR*)&this->_info, this->_sizeInfo) == -1)
			throw Exception("sendto has failed.");
	}
}

ISocket					*CUSocket::receivUdp(char *message, int size, int *received)
{
	sockaddr_in			tmpInfo;
	int					sizeTmp = sizeof(tmpInfo);


	if ((this->_type != ISocket::UDP) || (this->_sock == -1) || (this->_func == ISocket::CLIENT))
		throw Exception("This socket type isn't valid.");
	if (this->_func == ISocket::NONE)
		throw Exception("This socket type isn't initialized.");
	CUSocket			*newSocket = new CUSocket(this);
	if ((*received = ::recvfrom(this->_sock, message, size, 0, (SOCKADDR*)&tmpInfo,
		       (socklen_t *) &sizeTmp)) == -1)
		throw Exception("recvfrom has failed.");
	newSocket->setInfo(tmpInfo);
	return (newSocket);
}

void					CUSocket::receiv(char *message, int size, int *received)
{
	if (this->_func == ISocket::NONE)
		throw Exception("This socket type isn't initialized.");
	if (((this->_func == ISocket::SERVER) && (this->_type == ISocket::UDP)) || (this->_sock == -1))
		throw Exception("This socket is invalid.");
	if ((*received = ::recv(this->_sock, message, size, 0)) == -1)
		throw Exception("recv has failed.");
}

void		CUSocket::closeSocket()
{
	if ((this->_sock != -1) && (close(this->_sock) != 0))
		throw Exception("closesocket of sock has failed.");
}

void		CUSocket::setSocket(int sock)
{
	this->_sock = sock;
}

void		CUSocket::setInfo(sockaddr_in info)
{
	this->_info = info;
	this->_sizeInfo = sizeof(this->_info);
}

int		CUSocket::getSocket() const
{
	return (this->_sock);
}

sockaddr_in	CUSocket::getInfo() const
{
	return (this->_info);
}
