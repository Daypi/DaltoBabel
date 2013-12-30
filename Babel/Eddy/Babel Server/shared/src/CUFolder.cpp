#include		"CUFolder.h"

CUFolder::CUFolder(const std::string& name) : _name(name)
{
}

CUFolder::~CUFolder()
{
}

bool			CUFolder::open(const std::string& name)
{
	return (this->open(name.c_str()));
}

bool			CUFolder::open(const char *name)
{
	this->_name = std::string(name);
	this->_dir = opendir(name);
	return (!(this->_dir == 0));
}

bool			CUFolder::open()
{
	return (this->open(this->_name));
}

bool			CUFolder::close()
{
	return (closedir(this->_dir) == 0);
}

bool			CUFolder::create(const std::string& name)
{
	return (this->create(name.c_str()));
}

bool			CUFolder::create(const char *name)
{
	this->_name = std::string(name);
	return (::mkdir(name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0);
}

bool			CUFolder::create()
{
	return (this->create(this->_name));
}

bool			CUFolder::remove(const std::string& name) const
{
	return (this->remove(name.c_str()));
}

bool			CUFolder::remove(const char *name) const
{
	return (::rmdir(name) == 0);
}

bool			CUFolder::remove() const
{
	return (this->remove(this->_name));
}

bool					CUFolder::nextFile(File& file)
{
	struct dirent		*ent;
	struct stat			st;

	ent = readdir(this->_dir);
	if (!ent)
		return (false);
	file.name = std::string(ent->d_name);
	file.size = 0;
	file.folder = false;
	if (::stat(ent->d_name, &st) != -1)
	{
		file.size = st.st_size;
		file.folder = S_ISDIR(st.st_mode) != 0;
	}
	return (true);
}