#pragma once

#include <string>
#include <map>
#include <vector>
#include <string.h>

class	ISocketClient
{
public:
	virtual ~ISocketClient() {}

	virtual	void	init(int, const char *) = 0;
	virtual	bool	isReadable() = 0;
	virtual	bool	isWritable() = 0;
	virtual	void	send(const char *, int) = 0;
	virtual	char	*recv(char *, int, int *) = 0;
	virtual	void	close() = 0;
};
