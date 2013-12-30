#include		"Account.h"

Account::Account(unsigned int uid, const std::string& ip, const std::string& name, const std::string& password) : _uid(uid), _ip(ip), _name(name), _password(password), _connected(true), _status(Account::AVAILABLE), _statusText(""), _currentCall(0), _calling(false)
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

bool		Account::connected() const
{
	return (this->_connected);
}

void		Account::connect()
{
	this->_connected = true;
}

void		Account::disconnect()
{
	this->_connected = false;
}

const std::string&		Account::getPassword() const
{
	return (this->_password);
}

void			Account::setPassword(const std::string& password)
{
	this->_password = password;
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

const std::vector<std::pair<Account *, bool> >&		Account::getContactList() const
{
	return (this->_contactList);
}

bool		Account::addContact(Account *contact)
{
	if (!contact)
		return (false);
	this->_contactList.push_back(std::pair<Account *, bool>(contact, true));
	return (true);
}

bool									Account::removeContact(Account *contact)
{
	return (contact ? this->removeContact(contact->getName()) : false);
}

bool													Account::removeContact(const std::string& name)
{
	std::vector<std::pair<Account *, bool> >::iterator	tmp;
	bool												found = false;

	for (std::vector<std::pair<Account *, bool> >::iterator it = this->_contactList.begin(); it != this->_contactList.end(); ++it)
	{
		if (*((*it).first) == name)
		{
			tmp = it;
			found = true;
		}
	}
	if (found)
		this->_contactList.erase(tmp);
	return (found);
}

bool		Account::blockContact(Account *contact)
{
	return (contact ? this->blockContact(contact->getName()) : false);
}

bool		Account::blockContact(const std::string& name)
{
	for (unsigned int i = 0; i < this->_contactList.size(); ++i)
	{
		if (*this->_contactList[i].first == name)
		{
			this->_contactList[i].second = false;
			return (true);
		}
	}
	return (false);
}

bool		Account::contactBlocked(Account *contact) const
{
	return (contact ? this->contactBlocked(contact->getName()) : false);
}

bool		Account::contactBlocked(const std::string& name) const
{
	for (unsigned int i = 0; i < this->_contactList.size(); ++i)
	{
		if (*this->_contactList[i].first == name)
			return (!this->_contactList[i].second);
	}
	return (false);
}

bool		Account::hasContact(Account *contact) const
{
	return (contact ? this->hasContact(contact->getName()) : false);
}

bool		Account::hasContact(const std::string& name) const
{
	for (unsigned int i = 0; i < this->_contactList.size(); ++i)
	{
		if (*this->_contactList[i].first == name)
			return (true);
	}
	return (false);
}

void		Account::setCurrentCall(Account *account)
{
	this->_currentCall = account;
}

Account		*Account::getCurrentCall() const
{
	return (this->_currentCall);
}

bool		Account::inCall() const
{
	return (this->_currentCall != 0);
}

void		Account::callWaiting()
{
	this->_calling = true;
}

void		Account::callAccepted()
{
	this->_calling = false;
}

bool		Account::pending() const
{
	return (this->_calling);
}
