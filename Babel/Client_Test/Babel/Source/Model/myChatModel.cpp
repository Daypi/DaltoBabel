#include "Include/Model/myChatModel.h"

MyChatModel::MyChatModel(Network *net, const std::string &name, QWidget *parent)
{
    this->_net = net;
    _w = new ChatWindow(name, this, parent);
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

void    MyChatModel::sendCall(const std::string& login)
{
    this->_net->sendCall(login);
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

void    MyChatModel::displayMsg(const std::string& login, const std::string& msg)
{
    this->_w->myShow();
    this->_w->addMsg(login + " : " + msg);
}

void    MyChatModel::closeCall()
{
    this->_net->sendHangUp();
}

void    MyChatModel::close()
{
    this->_w->close();
}

void    MyChatModel::sendMsg(const std::string& login, const std::string& msg)
{
    this->_net->sendMsg(login, msg);
}

