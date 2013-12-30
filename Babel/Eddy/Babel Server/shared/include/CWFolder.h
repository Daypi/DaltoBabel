#pragma once

#include				"IFolder.h"
#include				<Windows.h>

class					CWFolder : public IFolder
{
	std::string			_name;
	WIN32_FIND_DATA		_ffd;
	HANDLE				_hFind;
	bool				_first;

public:
	CWFolder(const std::string& name = "");
	virtual ~CWFolder();

	virtual bool		open(const std::string&);
	virtual bool		open(const char *);
	virtual bool		open();
	virtual bool		close();
	virtual bool		create(const std::string&);
	virtual bool		create(const char *);
	virtual bool		create();
	virtual bool		remove(const std::string&) const;
	virtual bool		remove(const char *) const;
	virtual bool		remove() const;
	virtual bool		nextFile(File&);
};