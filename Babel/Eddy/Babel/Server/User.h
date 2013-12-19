#pragma once

#include						<string>
#include						<vector>
#include						"IUser.h"
#include						"Contact.h"
#include						"PacketFactory.h"
#include						"TimeStamp.h"

class							User : public IUser
{
	unsigned int				_uid;
	std::string					_ip;
	std::string					_name;
	bool						_connected;
	std::vector<Contact *>		_contactList;
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
	void						connect();
	void						disconnect();
	bool						connected() const;
	unsigned int				getSockId() const;
	void						setSockId(unsigned int);
	Packet						*getPacket(const char *, unsigned int);
	bool						timeout(unsigned long);
};