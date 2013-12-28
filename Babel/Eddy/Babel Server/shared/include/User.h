#pragma once

#include						<string>
#include						<ctime>
#include						<vector>
#include						"IUser.h"
#include						"PacketFactory.h"
#include						"TimeStamp.h"

class							User : public IUser
{
	unsigned int				_uid;
	std::string					_name;
	std::string					_ip;
	bool						_connected;
	unsigned int				_sockId;
	PacketFactory				_packetFactory;
	TimeStamp					_timeStamp;

public:
	User();
	User(unsigned int, const std::string& name = "Jeanjean", const std::string& ip = "127.0.0.1");
	virtual ~User();

	virtual bool				operator==(const IUser&);
	virtual bool				operator==(const std::string&);
	virtual bool				operator==(unsigned int);
	virtual const std::string&	getName() const;
	virtual const std::string&	getIp() const;
	virtual unsigned int		getUID() const;
	virtual void				setName(const std::string&);
	virtual bool				connected() const;
	virtual void				connect();
	virtual void				disconnect();
	unsigned int				getSockId() const;
	void						setSockId(unsigned int);
	Packet						*getPacket(const char *data = 0, unsigned int size = 0);
	bool						timeout(time_t, bool change = true);
};
