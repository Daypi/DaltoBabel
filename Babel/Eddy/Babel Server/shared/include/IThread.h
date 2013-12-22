#pragma once

class IThread
{
public:
	virtual ~IThread() {}

	virtual void	start() = 0;
	virtual void	join() = 0;
	virtual void	stop() = 0;
};
