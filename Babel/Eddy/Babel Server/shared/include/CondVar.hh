#pragma once

#ifdef _WIN32
# include "CWCondVar.h"
typedef	CWCondVar CCondVar;
#else
# include "CUCondVar.h"
typedef	CUCondVar CCondVar;
#endif // !WIN

class CondVar : public CCondVar
{
public:
	CondVar(Mutex &);
	virtual ~CondVar();
};
