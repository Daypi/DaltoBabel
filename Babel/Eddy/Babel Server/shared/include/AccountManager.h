#pragma once

#include												<string>
#include												<vector>
#include												"Account.h"

class													AccountManager
{
	std::vector<Account *>								_accountList;

	unsigned int										newId() const;

public:
	AccountManager();
	virtual ~AccountManager();

	unsigned int										size() const;
	void												clear();
	void												show() const;

	const std::vector<Account *>&						getAccountList() const;

	bool												create(Account *);
	bool												create(const std::string&, const std::string&, const std::string&);

	Account												*getAccountById(unsigned int) const;
	Account												*getAccountByName(const std::string&) const;
	Account												*getAccountByName(const char *) const;
	Account												*getAccountByIp(const std::string&) const;
	Account												*getAccountByIp(const char *) const;

	bool												removeAccountById(unsigned int);
	bool												removeAccountByName(const std::string&);
	bool												removeAccountByName(const char *);
	bool												removeAccountByIp(const std::string&);
	bool												removeAccountByIp(const char *);

	bool												accountExists(unsigned int) const;
	bool												accountExists(const std::string&) const;
	bool												accountExists(const char *) const;

	bool												addContact(Account *, const std::string&);
	bool												addContact(unsigned int, const std::string&);
	bool												addContact(const std::string&, const std::string&);
	bool												addContact(const char *, const std::string&);
	
	bool												removeContact(Account *, const std::string&);
	bool												removeContact(unsigned int, const std::string&);
	bool												removeContact(const std::string&, const std::string&);
	bool												removeContact(const char *, const std::string&);

	bool												blockContact(Account *, const std::string&);
	bool												blockContact(unsigned int, const std::string&);
	bool												blockContact(const std::string&, const std::string&);
	bool												blockContact(const char *, const std::string&);

	void												save();
	void												load();
};