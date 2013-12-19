#include		"Account.h"

Account::Account()
{
}

Account::Account(unsigned int uid, const std::string& ip, const std::string& name, const std::string& password) : _uid(uid), _ip(ip), _name(name), _password(password)
{
}

Account::~Account()
{
}

bool		Account::operator==(const IUser& user)
{
	return (this->_name == user.getName());
}

bool		Account::operator==(const std::string& name)
{
	return (this->_name == name);
}

bool		Account::operator==(unsigned int id)
{
	return (this->_uid == id);
}

const std::string&		Account::getName() const
{
	return (this->_name);
}

const std::string&		Account::getIp() const
{
	return (this->_ip);
}

unsigned int		Account::getUID() const
{
	return (this->_uid);
}

void		Account::setName(const std::string& name)
{
	this->_name = name;
}