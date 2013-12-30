#pragma once

#include		<unistd.h>
#include		<sys/types.h>
#include		<sys/stat.h>
#include		<dirent.h>
#include		"IFolder.h"

class					CUFolder : public IFolder
{
	std::string			_name;
	DIR					*_dir;

public:
	CUFolder(const std::string& name = "");
	virtual ~CUFolder();

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