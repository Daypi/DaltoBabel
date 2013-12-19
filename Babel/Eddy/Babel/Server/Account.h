#pragma once

#include						<string>
#include						<vector>
#include						"IUser.h"
#include						"Contact.h"

class							Account : public IUser
{
	unsigned int				_uid;
	std::string					_ip;
	std::string					_name;
	std::string					_password;
	std::vector<Contact *>		_contactList;

public:
	Account();
	Account(unsigned int, const std::string&, const std::string&, const std::string&);
	virtual ~Account();

	virtual bool				operator==(const IUser&);
	virtual bool				operator==(const std::string&);
	virtual bool				operator==(unsigned int);
	virtual const std::string&	getName() const;
	virtual const std::string&	getIp() const;
	virtual unsigned int		getUID() const;
	virtual void				setName(const std::string&);
};