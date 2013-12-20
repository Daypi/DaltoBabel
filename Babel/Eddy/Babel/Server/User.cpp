#include		"User.h"

User::User()
{
}

User::User(unsigned int id, const std::string& name, const std::string& ip) : _uid(id), _name(name), _ip(ip), _connected(false), _sockId(0)
{
}

User::~User()
{
}

bool		User::operator==(const IUser& user)
{
	return (this->_name == user.getName());
}

bool		User::operator==(const std::string& name)
{
	return (this->_name == name);
}

bool		User::operator==(unsigned int id)
{
	return (this->_uid == id);
}

const std::string&		User::getName() const
{
	return (this->_name);
}

const std::string&		User::getIp() const
{
	return (this->_ip);
}

unsigned int		User::getUID() const
{
	return (this->_uid);
}

void			User::setName(const std::string& name)
{
	this->_name = name;
}

bool			User::connected() const
{
	return (this->_connected);
}

void			User::connect()
{
	this->_connected = true;
}

void			User::disconnect()
{
	this->_connected = false;
}

unsigned int	User::getSockId() const
{
	return (this->_sockId);
}

void			User::setSockId(unsigned int sockId)
{
	this->_sockId = sockId;
}

Packet			*User::getPacket(const char *data, unsigned int size)
{
	Packet			*packet = 0;

	this->_packetFactory.feed(data, size);
	packet = this->_packetFactory.getPacket();
	return (packet);
}

bool			User::timeout(unsigned long time)
{
	return (this->_timeStamp.elapsedTime() >= time);
}