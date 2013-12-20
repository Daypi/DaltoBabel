#include		"Account.h"

Account::Account(unsigned int uid, const std::string& ip, const std::string& name, const std::string& password) : _uid(uid), _ip(ip), _name(name), _password(password), _status(Account::AVAILABLE), _statusText("")
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

Account::eStatus		Account::getStatus() const
{
	return (this->_status);
}

const std::string&		Account::getStatusText() const
{
	return (this->_statusText);
}

void		Account::setStatus(Account::eStatus status)
{
	this->_status = status;
}

void		Account::setStatusText(const std::string& statusText)
{
	this->_statusText = statusText;
}

bool		Account::addContact(Contact *contact)
{
	if (!contact)
		return (false);
	this->_contactList.push_back(contact);
	return (true);
}

bool		Account::addContact(unsigned int id, const std::string& ip, const std::string& name)
{
	return (this->addContact(new Contact(id, ip, name)));
}