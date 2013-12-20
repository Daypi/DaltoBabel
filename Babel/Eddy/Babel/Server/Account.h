#pragma once

#include						<string>
#include						<vector>
#include						"IUser.h"
#include						"Contact.h"

class							Account : public IUser
{
public:
	enum						eStatus
	{
		AVAILABLE,
		BUSY,
		AWAY,
		INVISIBLE,
		ENUM_COUNT
	};

private:
	unsigned int				_uid;
	std::string					_ip;
	std::string					_name;
	std::string					_password;
	Account::eStatus			_status;
	std::string					_statusText;
	std::vector<Contact *>		_contactList;

public:
	Account(unsigned int, const std::string&, const std::string&, const std::string&);
	virtual ~Account();

	virtual bool				operator==(const IUser&);
	virtual bool				operator==(const std::string&);
	virtual bool				operator==(unsigned int);
	virtual const std::string&	getName() const;
	virtual const std::string&	getIp() const;
	virtual unsigned int		getUID() const;
	virtual void				setName(const std::string&);

	Account::eStatus			getStatus() const;
	const std::string&			getStatusText() const;
	void						setStatus(Account::eStatus);
	void						setStatusText(const std::string&);

	bool						addContact(Contact *);
	bool						addContact(unsigned int, const std::string&, const std::string&);
};