#include		"UserCollection.h"

UserCollection::UserCollection()
{
}

UserCollection::~UserCollection()
{
	for (unsigned int i = 0; i < this->_userList.size(); ++i)
	{
		delete this->_userList[i];
	}
	this->_userList.clear();
}

bool			UserCollection::add(User *user)
{
	if (!user || this->getUserById(user->getUID()))
		return (false);
	this->_userList.push_back(user);
	return (true);
}

bool			UserCollection::add(unsigned int sockId, const std::string& name, const std::string& ip)
{
	User		*user;

	user = this->getUserByIp(ip);
	if (user/* && user->connected()*/)
		return (false);
	user = new User(this->newId(), name, ip);
	user->setSockId(sockId);
	this->_userList.push_back(user);
	return (true);
}

unsigned int	UserCollection::size() const
{
	return (this->_userList.size());
}

User			*UserCollection::getUserById(unsigned int id) const
{
	for (unsigned int i = 0; i < this->_userList.size(); ++i)
	{
		if (*this->_userList[i] == id)
			return (this->_userList[i]);
	}
	return (0);
}

User			*UserCollection::getUserByName(const std::string& name) const
{
	for (unsigned int i = 0; i < this->_userList.size(); ++i)
	{
		if (*this->_userList[i] == name)
			return (this->_userList[i]);
	}
	return (0);
}

User				*UserCollection::getUserByName(const char *name) const
{
	std::string		tmp(name);

	for (unsigned int i = 0; i < this->_userList.size(); ++i)
	{
		if (*this->_userList[i] == tmp)
			return (this->_userList[i]);
	}
	return (0);
}

User				*UserCollection::getUserByIp(const std::string& ip) const
{
	for (unsigned int i = 0; i < this->_userList.size(); ++i)
	{
		if (this->_userList[i]->getIp() == ip)
			return (this->_userList[i]);
	}
	return (0);
}

User				*UserCollection::getUserByIp(const char *ip) const
{
	std::string		tmp(ip);

	for (unsigned int i = 0; i < this->_userList.size(); ++i)
	{
		if (this->_userList[i]->getIp() == tmp)
			return (this->_userList[i]);
	}
	return (0);
}

User				*UserCollection::getUserBySockId(unsigned int sockId) const
{
	for (unsigned int i = 0; i < this->_userList.size(); ++i)
	{
		if (this->_userList[i]->getSockId() == sockId)
			return (this->_userList[i]);
	}
	return (0);
}

void								UserCollection::removeUserById(unsigned int id)
{
	std::vector<User *>::iterator	tmp;
	bool							found = false;

	for (std::vector<User *>::iterator it = this->_userList.begin(); it != this->_userList.end(); ++it)
	{
		if (*(*it) == id)
		{
			tmp = it;
			found = true;
		}
	}
	if (found)
		this->_userList.erase(tmp);
}

void								UserCollection::removeUserByName(const std::string& name)
{
	std::vector<User *>::iterator	tmp;
	bool							found = false;

	for (std::vector<User *>::iterator it = this->_userList.begin(); it != this->_userList.end(); ++it)
	{
		if (*(*it) == name)
		{
			tmp = it;
			found = true;
		}
	}
	if (found)
		this->_userList.erase(tmp);
}

void								UserCollection::removeUserByName(const char *name)
{
	std::vector<User *>::iterator	tmp;
	bool							found = false;
	std::string						nameTmp(name);

	for (std::vector<User *>::iterator it = this->_userList.begin(); it != this->_userList.end(); ++it)
	{
		if (*(*it) == nameTmp)
		{
			tmp = it;
			found = true;
		}
	}
	if (found)
		this->_userList.erase(tmp);
}

unsigned int		UserCollection::newId() const
{
	unsigned int	id = 0;

	for (unsigned int i = 0; i < this->_userList.size(); ++i)
	{
		if (this->_userList[i]->getUID() > id)
			id = this->_userList[i]->getUID();
	}
	return (id + 1);
}