#pragma once

class	ICondVar
{
public:
	virtual			~ICondVar() {}

	virtual void	wait() = 0;
	virtual void	signal() = 0;
	virtual void	broadcast() = 0;
};