#include "CWSocket.hh"

CWSocket::CWSocket(ISocket::TypeSocket type) 
: _type(type)
{
	WSADATA				wsaData;
	bool				bOptVal = 0;
	int					bOptLen = sizeof(bool);

	this->_isStartUp = true;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		throw Exception("WSAStartup has failed.");
	this->_sock = -1;
	if ((this->_sock = WSASocket(AF_INET, ((this->_type == ISocket::TCP) ? (SOCK_STREAM) : (SOCK_DGRAM)),
		((this->_type == ISocket::TCP) ? (IPPROTO_TCP) : (IPPROTO_UDP)), NULL, 0, 0)) == INVALID_SOCKET)
	{
		this->_sock = INVALID_SOCKET;
		throw Exception("WSASocket has failed.");
	}
	if (setsockopt(this->_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&bOptVal, bOptLen) != 0)
		throw Exception("setsockopt has failed.");
	this->_func = ISocket::NONE;
	this->_sockUdpSrv = NULL;
}

CWSocket::CWSocket(ISocket::TypeSocket type, bool isClient) : _type(type)
{
	this->_isStartUp = false;
	if (isClient == true)
		this->_func = ISocket::CLIENT;
	else
		this->_func = ISocket::SERVER;
	this->_sockUdpSrv = NULL;
	this->_sock = -1;
}

CWSocket::CWSocket(CWSocket *socketSrv)
: _type(ISocket::UDP)
{
	this->_isStartUp = false;
	this->_func = ISocket::CLIENT;
	this->_sockUdpSrv = socketSrv;
	this->_sock = -1;
}

CWSocket::~CWSocket()
{
	if ((this->_isStartUp) && (WSACleanup() != 0))
		std::cerr << "ERROR: WSACleanup has failed." << std::endl;
}

void		CWSocket::bind(const char *ipAddress, int port)
{
	sockaddr_in			service;

	if (this->_func != ISocket::NONE)
		throw Exception(((this->_func == ISocket::CLIENT) ? ("this socket is client socket.") : ("this socket is already bind to server.")));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(ipAddress);
	WSAHtons(this->_sock, port, &service.sin_port);
	this->_func = ISocket::SERVER;
	if (::bind(this->_sock, (SOCKADDR *)&service, sizeof(service)) != 0)
		throw Exception("bind has failed.");
}

void		CWSocket::connect(const char *ipAddress, int port)
{
	sockaddr_in			server_info;

	if (this->_func != ISocket::NONE)
		throw Exception(((this->_func == ISocket::SERVER) ? ("this socket is server socket.") : ("this socket is already connected to server.")));
	server_info.sin_family = AF_INET;
	server_info.sin_addr.s_addr = inet_addr(ipAddress);
	WSAHtons(this->_sock, port, &server_info.sin_port);
	this->_func = ISocket::CLIENT;
	if (WSAConnect(this->_sock, (SOCKADDR *)&server_info, sizeof(server_info), NULL, NULL, NULL, NULL) != 0)
		throw Exception("WSAConnect has failed.");
}

void		CWSocket::listen(int nbConnexion)
{
	if (this->_type == ISocket::UDP)
		throw Exception("This socket type is UDP.");
	if (this->_func != ISocket::SERVER)
		throw Exception(((this->_func == ISocket::NONE) ? ("this socket isn't initialized.") : ("this socket isn't socket server.")));
	if (::listen(this->_sock, nbConnexion) != 0)
		throw Exception("listen has failed.");
}

ISocket			*CWSocket::accept()
{
	sockaddr_in	tmpInfo;
	int			sizeTmp = sizeof(tmpInfo);
	SOCKET		tmp;
	CWSocket	*newSocket = new CWSocket(this->_type, true);

	if (this->_type == ISocket::UDP)
		throw Exception("This socket type is UDP.");
	if (this->_func != ISocket::SERVER)
		throw Exception(((this->_func == ISocket::NONE) ? ("this socket isn't initialized.") : ("this socket isn't socket server.")));
	if ((tmp = WSAAccept(this->_sock, (SOCKADDR*) &tmpInfo, &sizeTmp, NULL, NULL)) == INVALID_SOCKET)
		throw Exception("WSAAccept has failed.");
	newSocket->setSocket(tmp);
	newSocket->setInfo(tmpInfo);
	return (newSocket);
}

void		CWSocket::send(const char *message, int size)
{
	DWORD				sendBytes;
	WSABUF				dataBuf;

	if (this->_func == ISocket::NONE)
		throw Exception("This socket type isn't initialized.");
	dataBuf.len = size;
	dataBuf.buf = const_cast<char *>(message);
	if ((this->_type == ISocket::TCP) || ((this->_func == ISocket::CLIENT) && (this->_sock != -1)))
	{
		if (WSASend(this->_sock, &dataBuf, 1, &sendBytes, NULL, NULL, NULL) != 0)
			throw Exception("WSASend has failed.");
	}
	else
	{
		if (!this->_sockUdpSrv)
			throw Exception("Socket server UDP invalid for sending client message.");
		if (WSASendTo(this->_sockUdpSrv->_sock, &dataBuf, 1, &sendBytes, NULL, (SOCKADDR*)&this->_info, this->_sizeInfo, NULL, NULL) != 0)
			throw Exception("WSASendTo has failed.");
	}
}

ISocket					*CWSocket::receivUdp(char *message, int size, int *received)
{
	sockaddr_in			tmpInfo;
	int					sizeTmp = sizeof(tmpInfo);
	DWORD				flags;
	WSABUF				dataBuf;

	if ((this->_type != ISocket::UDP) || (this->_sock == -1) || (this->_func == ISocket::CLIENT))
		throw Exception("This socket type isn't valid.");
	if (this->_func == ISocket::NONE)
		throw Exception("This socket type isn't initialized.");
	CWSocket			*newSocket = new CWSocket(this);
	dataBuf.buf = message;
	dataBuf.len = size;
	flags = 0;
	if (WSARecvFrom(this->_sock, &dataBuf, 1, (DWORD *)received, &flags, (SOCKADDR*)&tmpInfo, &sizeTmp, NULL, NULL) != 0)
		throw Exception("WSARecvFrom has failed.");
	newSocket->setInfo(tmpInfo);
	return (newSocket);
}

void					CWSocket::receiv(char *message, int size, int *received)
{
	DWORD				flags;
	WSABUF				dataBuf;

	if (this->_func == ISocket::NONE)
		throw Exception("This socket type isn't initialized.");
	if (((this->_func == ISocket::SERVER) && (this->_type == ISocket::UDP)) || (this->_sock == -1))
		throw Exception("This socket is invalid.");
	dataBuf.buf = message;
	dataBuf.len = size;
	flags = 0;
	if (WSARecv(this->_sock, &dataBuf, 1, (DWORD *)received, &flags, NULL, NULL) != 0)
		throw Exception("WSARecv has failed.");
}

void		CWSocket::closeSocket()
{
	if ((this->_sock != -1) && (closesocket(this->_sock) != 0))
		throw Exception("closesocket of sock has failed.");
}

void		CWSocket::setSocket(SOCKET sock)
{
	this->_sock = sock;
}

void		CWSocket::setInfo(sockaddr_in info)
{
	this->_info = info;
	this->_sizeInfo = sizeof(this->_info);
}

SOCKET		CWSocket::getSocket() const
{
	return (this->_sock);
}

sockaddr_in	CWSocket::getInfo() const
{
	return (this->_info);
}