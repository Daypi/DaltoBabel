#pragma once

#include					<string>
#include					<vector>
#include					"User.h"

class						UserCollection
{
	std::vector<User *>		_userList;

	unsigned int			newId() const;

public:
	UserCollection();
	virtual ~UserCollection();

	bool					add(User *);
	bool					add(unsigned int, const std::string& name = "", const std::string& ip = "");
	unsigned int			size() const;

	User					*getUserById(unsigned int) const;
	User					*getUserByName(const std::string&) const;
	User					*getUserByName(const char *) const;
	User					*getUserByIp(const std::string&) const;
	User					*getUserByIp(const char *) const;
	User					*getUserBySockId(unsigned int) const;

	void					removeUserById(unsigned int);
	void					removeUserByName(const std::string&);
	void					removeUserByName(const char *);

	bool					userExists(unsigned int) const;
	bool					userExists(const std::string&) const;
	bool					userExists(const char *) const;
};