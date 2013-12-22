#pragma once

#include <string>
#include <map>
#include <vector>
#include <string.h>
#include "Exception.h"

class	ISocketServer
{
public:
	virtual ~ISocketServer() {}

	virtual	void							init(int, int) = 0;
	virtual	std::pair<unsigned int, char *>	&checkConnection() = 0;
	virtual	std::vector<unsigned int>&		isReadable() = 0;
	virtual	std::vector<unsigned int>&		isReadable(unsigned int) = 0;
	virtual	std::vector<unsigned int>&		isWritable() = 0;
	virtual	std::vector<unsigned int>&		isWritable(unsigned int) = 0;
	virtual	std::vector<unsigned int>&		send(std::vector<unsigned int>& tab, const char *, int) = 0;
	virtual	std::vector<unsigned int>&		send(unsigned int, const char *, int) = 0;
	virtual	std::map<unsigned int, std::pair<const char *, int>>&	recv(std::vector<unsigned int>& tab, int) = 0;
	virtual	std::map<unsigned int, std::pair<const char *, int>>&	recv(unsigned int, int) = 0;
	virtual void	closeClient(unsigned int id) = 0;
	virtual void	closeServer() = 0;
	virtual void	eraseClient(unsigned int id) = 0;
	virtual void	deleteMap() = 0;
};
