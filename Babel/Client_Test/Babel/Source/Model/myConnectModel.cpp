#include "Include/Model/myConnectModel.h"

MyConnectModel::MyConnectModel(Network *net, MyContactModel *contact, QWidget *parent)
    : _net(net),
      _w(this, parent),
      _contact(contact)
{
    while (this->_w.isVisible())
    {
        this->_w.refresh();
        this->_net->handleNetwork();
    }
}

MyConnectModel::~MyConnectModel()
{
}

void    MyConnectModel::connect(const std::string &ip, int port)
{
    try
    {
        this->_net->connect(ip, port);
    }
    catch (Exception &e)
    {
        throw Exception(e);
    }
}

void    MyConnectModel::show()
{
    this->_contact->show();
}

void    MyConnectModel::close()
{
    this->_contact->close();
    this->~MyConnectModel();
}
