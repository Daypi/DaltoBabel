#pragma once

#include												<string>
#include												<vector>
#include												"IUser.h"

class													Account : public IUser
{
public:
	enum												eStatus
	{
		AVAILABLE,
		BUSY,
		AWAY,
		INVISIBLE,
		ENUM_COUNT
	};

private:
	unsigned int										_uid;
	std::string											_ip;
	std::string											_name;
	std::string											_password;
	bool												_connected;
	Account::eStatus									_status;
	std::string											_statusText;
	std::vector<std::pair<Account *, bool> >			_contactList;
	Account												*_currentCall;
	bool												_calling;

public:
	Account(unsigned int id = 0, const std::string& ip = "", const std::string& name = "", const std::string& password = "");
	virtual ~Account();

	virtual bool										operator==(const IUser&);
	virtual bool										operator==(const std::string&);
	virtual bool										operator==(unsigned int);
	virtual const std::string&							getName() const;
	virtual const std::string&							getIp() const;
	virtual unsigned int								getUID() const;
	virtual void										setName(const std::string&);
	virtual bool										connected() const;
	virtual void										connect();
	virtual void										disconnect();

	const std::string&									getPassword() const;
	void												setPassword(const std::string&);

	Account::eStatus									getStatus() const;
	const std::string&									getStatusText() const;
	void												setStatus(Account::eStatus);
	void												setStatusText(const std::string&);

	const std::vector<std::pair<Account *, bool> >&		getContactList() const;

	bool												addContact(Account *);

	bool												removeContact(Account *);
	bool												removeContact(const std::string&);

	bool												blockContact(Account *);
	bool												blockContact(const std::string&);

	bool												contactBlocked(Account *) const;
	bool												contactBlocked(const std::string&) const;

	bool												hasContact(Account *) const;
	bool												hasContact(const std::string&) const;

	void												setCurrentCall(Account *);
	Account												*getCurrentCall() const;
	bool												inCall() const;

	void												callWaiting();
	void												callAccepted();
	bool												pending() const;
};
