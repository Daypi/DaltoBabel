#pragma once

#include <stdexcept>

class	Exception : public std::exception
{
	const char	*_msg;
public:
	Exception(const char *);
	virtual	~Exception() throw();

	virtual	const char	*what() const throw();
};