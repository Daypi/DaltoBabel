#pragma once

#include				<ctime>
#include				<cstring>

class					LibC
{
public:
	static void			*memcpy(void *, const void *, size_t);
	static void			*memset(void *, int, size_t);
	static time_t		time(time_t *);
};