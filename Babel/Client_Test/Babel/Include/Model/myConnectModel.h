#ifndef MYCONNECTMODEL_H
#define MYCONNECTMODEL_H

#include "Include/Window/connectWindow.h"

class MyConnectModel
{
    ConnectWindow           _w;
public:
    MyConnectModel(QWidget *parent = 0);
    ~MyConnectModel();
};

#endif // MYCONNECTMODEL_H
