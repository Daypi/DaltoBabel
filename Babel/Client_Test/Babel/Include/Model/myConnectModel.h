#ifndef MYCONNECTMODEL_H
#define MYCONNECTMODEL_H

#include "Include/Network/network.h"
#include "Include/Window/connectWindow.h"

class MyConnectModel
{
    Network                 _net;
    ConnectWindow           _w;
public:
    MyConnectModel(QWidget *parent = 0);
    ~MyConnectModel();

    void    connect(const std::string &ip, int port);
};

#endif // MYCONNECTMODEL_H
