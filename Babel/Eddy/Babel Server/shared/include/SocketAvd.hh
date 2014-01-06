#pragma		once

#include	"Socket.hh"
#include	"Thread.hpp"
#ifdef _WIN32
# define	FUNCCLOSESOCKET(x) closesocket(x)
#else
# define	FUNCCLOSESOCKET(x) close(x)
#endif // !WIN

class		SeleKtor;

class SocketAvd : public Socket
{
	bool		_isWritable;
	bool		_isReadable;
	bool		_allowWritable;
	bool		_isSend;
	bool		_isRead;
	bool		_askWritable;
	SeleKtor	*_pool;
public:
	SocketAvd(Thread<SeleKtor, void, void *> *thread, SeleKtor *pool, ISocket::TypeSocket type = ISocket::TCP);
	SocketAvd(ISocket::TypeSocket type = ISocket::TCP);
	virtual ~SocketAvd();

	SocketAvd			*accept();
	void				init(Thread<SeleKtor, void, void *> *thread, SeleKtor *pool);
	bool				isWritable();
	bool				isReadable();
	bool				isAllowWritable();
	void				setWritable(bool value);
	void				setReadable(bool value);
	void				setAllowWritable(bool value);
	void				setSended(bool value);
	bool				isSended();
	bool				isRead();
	void				setRead(bool value);
	bool				getAskWritable();
	void				setAskWritable(bool value);
	void				iReaded();
	void				iSended();
	void				closeSocketAvd();
};
