#include			"CWFolder.h"
#include			<iostream>

CWFolder::CWFolder(const std::string& name) : _name(name + "\\*"), _first(true)
{
	this->_hFind = INVALID_HANDLE_VALUE;
}

CWFolder::~CWFolder()
{
}

bool			CWFolder::open(const std::string& name)
{
	return (this->open(name.c_str()));
}

bool			CWFolder::open(const char *name)
{
	this->_name = std::string(name) + "\\*";
	return (true);
}

bool			CWFolder::open()
{
	return (this->open(this->_name));
}

bool			CWFolder::close()
{
	FindClose(this->_hFind);
	this->_hFind = INVALID_HANDLE_VALUE;
	return (true);
}

bool			CWFolder::create(const std::string& name)
{
	return (this->create(name.c_str()));
}

bool			CWFolder::create(const char *name)
{
	this->_name = std::string(name) + "\\*";
	return (CreateDirectory(name, 0) == TRUE);
}

bool			CWFolder::create()
{
	return (this->create(this->_name));
}

bool			CWFolder::remove(const std::string& name) const
{
	return (this->remove(name.c_str()));
}

bool			CWFolder::remove(const char *name) const
{
	return (RemoveDirectory(name) == TRUE);
}

bool			CWFolder::remove() const
{
	return (this->remove(this->_name));
}

bool					CWFolder::nextFile(File& file)
{
	int					ret = 1;
	LARGE_INTEGER		fileSize;

	if (this->_first)
	{
		this->_hFind = FindFirstFile(this->_name.c_str(), &this->_ffd);
		if (this->_hFind == INVALID_HANDLE_VALUE)
			return (false);
		this->_first = false;
	}
	else
		ret = FindNextFile(this->_hFind, &this->_ffd);
	file.name = this->_ffd.cFileName;
	fileSize.LowPart = this->_ffd.nFileSizeLow;
	fileSize.HighPart = this->_ffd.nFileSizeHigh;
	file.size = fileSize.QuadPart;
	file.folder = (this->_ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	return (ret == 0 ? false : true);
}