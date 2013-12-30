#pragma once

#ifdef _WIN32
# include			"CWFolder.h"
typedef	CWFolder	CCFolder;
#else
# include			"CUFolder.h"
typedef	CUFolder	CCFolder;
#endif

class				Folder : public CCFolder
{
public:
	Folder(const std::string& name = "");
	virtual ~Folder();
};