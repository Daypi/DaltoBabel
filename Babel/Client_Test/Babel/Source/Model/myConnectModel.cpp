#include "Include/Model/myConnectModel.h"

MyConnectModel::MyConnectModel(Network *net, MyContactModel *contact, QWidget *parent)
    : _net(net),
      _w(this, parent),
      _contact(contact),
      _ok(false)
{
    while (!this->_w.isClosed())
    {
        this->_w.refresh();
        try
        {
            this->_net->handleNetwork();
        }
        catch (Exception &e)
        {
            throw Exception(e);
        }

        if (this->_net->getHandshake())
            this->_net->sendLogin(this->_w.getNewUser(), this->_w.getLogin(), this->_w.getMdp());
        if (this->_net->getLog())
        {
            this->_w.setClose(true);
            this->_ok = true;
        }
    }
    if (this->_ok)
    {
        this->_w.hide();
        this->show();
    }
    else
    {
        this->close();
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
}

void    MyConnectModel::closeWin()
{
    this->_w.close();
}
