#pragma once

#include				<string>

struct					File
{
	std::string			name;
	unsigned long long	size;
	bool				folder;
};

class					IFolder
{
public:
	virtual ~IFolder() {}

	virtual bool		open(const std::string&) = 0;
	virtual bool		open(const char *) = 0;
	virtual bool		open() = 0;
	virtual bool		close() = 0;
	virtual bool		create(const std::string&) = 0;
	virtual bool		create(const char *) = 0;
	virtual bool		create() = 0;
	virtual bool		remove(const std::string&) const = 0;
	virtual bool		remove(const char *) const = 0;
	virtual bool		remove() const = 0;
	virtual bool		nextFile(File&) = 0;
};