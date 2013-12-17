#include "Include/Model/myChatModel.h"

MyChatModel::MyChatModel(const std::string &name, QWidget *parent)
{
    _w = new ChatWindow(name, parent);
}

MyChatModel::~MyChatModel()
{
}

void  MyChatModel::myShow()
{
  _w->myShow();
}

void  MyChatModel::setChat(std::vector<std::string> &hist)
{
  _w->setChat(hist);
}

void  MyChatModel::setCalling(bool b)
{
  _w->setCalling(b);
  _call = b;
}

bool  MyChatModel::isCalling() const
{
  return (_call);
}
