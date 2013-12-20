#pragma once

#include						<string>
#include						"IUser.h"

class							Contact : public IUser
{
	unsigned int				_uid;
	std::string					_ip;
	std::string					_name;

public:
	Contact();
	Contact(unsigned int, const std::string&, const std::string&);
	virtual ~Contact();

	virtual bool				operator==(const IUser&);
	virtual bool				operator==(const std::string&);
	virtual bool				operator==(unsigned int);
	virtual const std::string&	getName() const;
	virtual const std::string&	getIp() const;
	virtual unsigned int		getUID() const;
	virtual void				setName(const std::string&);
};