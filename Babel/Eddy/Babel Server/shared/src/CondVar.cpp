#include "CondVar.hh"

CondVar::CondVar(Mutex &mutex) : CCondVar(mutex)
{

}

CondVar::~CondVar()
{

}