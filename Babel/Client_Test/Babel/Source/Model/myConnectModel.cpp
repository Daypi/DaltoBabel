#include "Include/Model/myConnectModel.h"

MyConnectModel::MyConnectModel(Network *net, MyContactModel *contact, QWidget *parent)
    : _net(net),
      _w(this, parent),
      _contact(contact)
{
    this->_w.Loop();
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
