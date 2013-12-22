#include			<fstream>
#include			<iostream>
#include			"AccountManager.h"

AccountManager::AccountManager()
{
}

AccountManager::~AccountManager()
{
}

unsigned int		AccountManager::size() const
{
	return (this->_accountList.size());
}

const std::vector<Account *>&		AccountManager::getAccountList() const
{
	return (this->_accountList);
}

bool				AccountManager::create(Account *account)
{
	if (!account)
		return (false);
	this->_accountList.push_back(account);
	return (true);
}

bool				AccountManager::create(const std::string& ip, const std::string& name, const std::string& password)
{
	if (this->accountExists(name))
		return (false);
	return (this->create(new Account(this->newId(), ip, name, password)));
}

Account				*AccountManager::getAccountById(unsigned int id) const
{
	for (unsigned int i = 0; i < this->_accountList.size(); ++i)
	{
		if (*this->_accountList[i] == id)
			return (this->_accountList[i]);
	}
	return (0);
}

Account				*AccountManager::getAccountByName(const std::string& name) const
{
	for (unsigned int i = 0; i < this->_accountList.size(); ++i)
	{
		if (*this->_accountList[i] == name)
			return (this->_accountList[i]);
	}
	return (0);
}

Account				*AccountManager::getAccountByName(const char *name) const
{
	std::string		tmp(name);

	for (unsigned int i = 0; i < this->_accountList.size(); ++i)
	{
		if (*this->_accountList[i] == tmp)
			return (this->_accountList[i]);
	}
	return (0);
}

Account				*AccountManager::getAccountByIp(const std::string& ip) const
{
	for (unsigned int i = 0; i < this->_accountList.size(); ++i)
	{
		if (this->_accountList[i]->getIp() == ip)
			return (this->_accountList[i]);
	}
	return (0);
}

Account				*AccountManager::getAccountByIp(const char *ip) const
{
	std::string		tmp(ip);

	for (unsigned int i = 0; i < this->_accountList.size(); ++i)
	{
		if (this->_accountList[i]->getIp() == tmp)
			return (this->_accountList[i]);
	}
	return (0);
}

bool									AccountManager::removeAccountById(unsigned int id)
{
	std::vector<Account *>::iterator	tmp;
	bool								found = false;

	for (std::vector<Account *>::iterator it = this->_accountList.begin(); it != this->_accountList.end(); ++it)
	{
		if (*(*it) == id)
		{
			tmp = it;
			found = true;
		}
	}
	if (found)
		this->_accountList.erase(tmp);
	return (found);
}

bool									AccountManager::removeAccountByName(const std::string& name)
{
	std::vector<Account *>::iterator	tmp;
	bool								found = false;

	for (std::vector<Account *>::iterator it = this->_accountList.begin(); it != this->_accountList.end(); ++it)
	{
		if (*(*it) == name)
		{
			tmp = it;
			found = true;
		}
	}
	if (found)
		this->_accountList.erase(tmp);
	return (found);
}

bool									AccountManager::removeAccountByName(const char *name)
{
	std::vector<Account *>::iterator	tmp;
	bool								found = false;
	std::string							nameTmp(name);

	for (std::vector<Account *>::iterator it = this->_accountList.begin(); it != this->_accountList.end(); ++it)
	{
		if (*(*it) == nameTmp)
		{
			tmp = it;
			found = true;
		}
	}
	if (found)
		this->_accountList.erase(tmp);
	return (found);
}

bool									AccountManager::removeAccountByIp(const std::string& ip)
{
	std::vector<Account *>::iterator	tmp;
	bool								found = false;

	for (std::vector<Account *>::iterator it = this->_accountList.begin(); it != this->_accountList.end(); ++it)
	{
		if ((*it)->getIp() == ip)
		{
			tmp = it;
			found = true;
		}
	}
	if (found)
		this->_accountList.erase(tmp);
	return (found);
}

bool									AccountManager::removeAccountByIp(const char *ip)
{
	std::vector<Account *>::iterator	tmp;
	bool								found = false;
	std::string							nameTmp(ip);

	for (std::vector<Account *>::iterator it = this->_accountList.begin(); it != this->_accountList.end(); ++it)
	{
		if ((*it)->getIp() == nameTmp)
		{
			tmp = it;
			found = true;
		}
	}
	if (found)
		this->_accountList.erase(tmp);
	return (found);
}

bool				AccountManager::accountExists(unsigned int id) const
{
	return (this->getAccountById(id) != 0);
}

bool				AccountManager::accountExists(const std::string& name) const
{
	return (this->getAccountByName(name) != 0);
}

bool				AccountManager::accountExists(const char *name) const
{
	return (this->getAccountByName(name) != 0);
}

bool				AccountManager::addContact(Account *account, const std::string& name)
{
	Account			*other;

	other = this->getAccountByName(name);
	if (!account || !other)
		return (false);
	account->addContact(other);
	return (true);
}

bool				AccountManager::addContact(unsigned int id, const std::string& name)
{
	return (this->addContact(this->getAccountById(id), name));
}

bool				AccountManager::addContact(const std::string& name, const std::string& nameToAdd)
{
	return (this->addContact(this->getAccountByName(name), nameToAdd));
}

bool				AccountManager::addContact(const char *name, const std::string& nameToAdd)
{
	return (this->addContact(this->getAccountByName(name), nameToAdd));
}

bool				AccountManager::removeContact(Account *account, const std::string& name)
{
	Account			*other;

	other = this->getAccountByName(name);
	if (!account || !other)
		return (false);
	account->removeContact(name);
	return (true);
}

bool				AccountManager::removeContact(unsigned int id, const std::string& name)
{
	return (this->removeContact(this->getAccountById(id), name));
}

bool				AccountManager::removeContact(const std::string& name, const std::string& nameToAdd)
{
	return (this->removeContact(this->getAccountByName(name), nameToAdd));
}

bool				AccountManager::removeContact(const char *name, const std::string& nameToAdd)
{
	return (this->removeContact(this->getAccountByName(name), nameToAdd));
}

bool				AccountManager::blockContact(Account *account, const std::string& name)
{
	Account			*other;

	other = this->getAccountByName(name);
	if (!account || !other)
		return (false);
	account->blockContact(other);
	return (true);
}

bool				AccountManager::blockContact(unsigned int id, const std::string& name)
{
	return (this->removeContact(this->getAccountById(id), name));
}

bool				AccountManager::blockContact(const std::string& name, const std::string& nameToAdd)
{
	return (this->removeContact(this->getAccountByName(name), nameToAdd));
}

bool				AccountManager::blockContact(const char *name, const std::string& nameToAdd)
{
	return (this->removeContact(this->getAccountByName(name), nameToAdd));
}

void				AccountManager::save()
{
	std::fstream	fs("Accounts.sav", std::ios::in | std::ios::out | std::ios::binary);

	if (!fs)
		std::cerr << "Could not open Accounts.sav" << std::endl;
	fs.write(reinterpret_cast<const char *>(this), sizeof(AccountManager));
}

void				AccountManager::load()
{
	std::fstream	fs("Accounts.sav", std::ios::in | std::ios::out | std::ios::binary);

	if (!fs)
		std::cerr << "Could not open Accounts.sav" << std::endl;
	fs.read(reinterpret_cast<char *>(this), sizeof(AccountManager));
}

unsigned int		AccountManager::newId() const
{
	unsigned int	id = 0;

	for (unsigned int i = 0; i < this->_accountList.size(); ++i)
	{
		if (this->_accountList[i]->getUID() > id)
			id = this->_accountList[i]->getUID();
	}
	return (id + 1);
}