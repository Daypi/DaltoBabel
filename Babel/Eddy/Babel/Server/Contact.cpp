#include		"Contact.h"

Contact::Contact()
{
}

Contact::Contact(unsigned int uid, const std::string& ip, const std::string& name) :_uid(uid), _ip(ip), _name(name)
{
}

Contact::~Contact()
{
}

bool		Contact::operator==(const IUser& contact)
{
	return (this->_name == contact.getName());
}

bool		Contact::operator==(const std::string& name)
{
	return (this->_name == name);
}

bool		Contact::operator==(unsigned int id)
{
	return (this->_uid == id);
}

const std::string&		Contact::getName() const
{
	return (this->_name);
}

const std::string&		Contact::getIp() const
{
	return (this->_ip);
}

unsigned int		Contact::getUID() const
{
	return (this->_uid);
}

void			Contact::setName(const std::string& name)
{
	this->_name = name;
}