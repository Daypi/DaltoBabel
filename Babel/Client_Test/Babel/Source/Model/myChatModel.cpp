#include "Include/Model/myChatModel.h"

MyChatModel::MyChatModel(Network *net, const std::string &name, QWidget *parent)
{
    this->_net = net;
    _w = new ChatWindow(name, parent);
}

MyChatModel::~MyChatModel()
{
}

void    MyChatModel::myShow()
{
    _w->myShow();
}

void    MyChatModel::setChat(std::vector<std::string> &hist)
{
    _w->setChat(hist);
}

void    MyChatModel::setCalling(bool b)
{
    _w->setCalling(b);
    _call = b;
}

bool    MyChatModel::isCalling() const
{
    return (_call);
}

void    MyChatModel::close()
{
    this->_w->close();
}
