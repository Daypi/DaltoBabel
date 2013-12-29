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
    bool                    _ok;

public:
    MyConnectModel(Network *net, MyContactModel *contact, QWidget *parent);
    ~MyConnectModel();

    void        connect(const std::string &ip, int port);
    void        show();
    void        close();
    void        closeWin();
};

#include "Include/Model/myContactModel.h"

#endif // MYCONNECTMODEL_H
