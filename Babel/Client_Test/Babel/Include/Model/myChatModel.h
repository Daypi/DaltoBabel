#ifndef MYCHATW_H
#define MYCHATW_H

#include "Include/Window/chatWindow.h"

class Network;

class MyChatModel
{
    Network     *_net;
    ChatWindow  *_w;
    bool        _call;

public:
    MyChatModel(Network *net, const std::string &name, QWidget *parent);
    ~MyChatModel();

    void        myShow();
    void        setChat(std::vector<std::string> &hist);
    void        setCalling(bool b);
    bool        isCalling() const;
    void        close();
};

#include "Include/Model/myContactModel.h"
//#include "Include/Network/network.h"

#endif // MYCHATW_H
