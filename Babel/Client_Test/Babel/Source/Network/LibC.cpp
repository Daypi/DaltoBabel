#include		"Include/Network/LibC.h"

void			*LibC::memcpy(void *dest, const void *src, size_t n)
{
	return (::memcpy(dest, src, n));
}

void			*LibC::memset(void *s, int c, size_t n)
{
	return (::memset(s, c, n));
}

time_t			LibC::time(time_t *t)
{
	return (::time(t));
}
