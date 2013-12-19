#include "Include/Model/myConnectModel.h"

MyConnectModel::MyConnectModel(QWidget *parent) : _w(this, parent)
{
}

MyConnectModel::~MyConnectModel()
{
}

void    MyConnectModel::connect(const std::string &ip, int port)
{
    try
    {
        this->_net.connect(ip, port);
    }
    catch (Exception &e)
    {
        throw Exception(e);
    }
}

Network&    MyConnectModel::getNetwork()
{
    return (this->_net);
}
