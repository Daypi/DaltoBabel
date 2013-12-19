#pragma once

#include						<vector>
#include						"Account.h"

class							AccountManager
{
	std::vector<Account *>		_accountList;

public:
	AccountManager();
	virtual ~AccountManager();

	void						save();
	void						load();
};