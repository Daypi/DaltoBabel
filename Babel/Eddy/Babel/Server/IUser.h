#pragma once

#include						<string>

class							IUser
{
public:
	virtual ~IUser() {}

	virtual bool				operator==(const IUser&) = 0;
	virtual bool				operator==(const std::string&) = 0;
	virtual bool				operator==(unsigned int) = 0;
	virtual const std::string&	getName() const = 0;
	virtual const std::string&	getIp() const = 0;
	virtual unsigned int		getUID() const = 0;
	virtual void				setName(const std::string&) = 0;
};