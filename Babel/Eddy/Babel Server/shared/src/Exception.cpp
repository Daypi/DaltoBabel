#include "Exception.h"

Exception::Exception(const char *msg) : _msg(msg)
{
}

Exception::~Exception() throw()
{

}

const char	*Exception::what() const throw()
{
	return(this->_msg);
}
