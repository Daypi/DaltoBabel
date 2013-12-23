#ifndef MYCONNECTMODEL_H
#define MYCONNECTMODEL_H

#include "Include/Network/network.h"
#include "Include/Window/connectWindow.h"
#include "Include/Model/myContactModel.h"

class MyContactModel;

class MyConnectModel
{
    Network                 *_net;
    ConnectWindow           _w;
    MyContactModel          *_contact;
public:
    MyConnectModel(Network *net, MyContactModel *contact, QWidget *parent);
    ~MyConnectModel();

    void        connect(const std::string &ip, int port);
    void        show();
    void        close();
};

#include "Include/Model/myContactModel.h"

#endif // MYCONNECTMODEL_H
