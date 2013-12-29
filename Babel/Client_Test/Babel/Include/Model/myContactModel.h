#ifndef MYCONTACTW_H
#define MYCONTACTW_H

#include "Include/Model/contact.h"

#define MY_TIMEOUT (15)

class ContactWindow;
class Network;
class MyConnectModel;

class MyContactModel
{
    std::vector<Contact *>  _contactList;
    Contact::eStatus        _status;
    std::string             _statusText;
    Network                 *_net;
    ContactWindow           *_w;
    MyConnectModel          *_connect;

public:
    MyContactModel(QWidget *parent = 0);
    ~MyContactModel();

    void    setContacts(std::vector<std::string>& list);
    void    setStatusText(const std::string& newStat);
    void    setStatus(Contact::eStatus status);
    void    addContact(const std::string &name, const std::string &statusText, Contact::eStatus status);
    void    clearContact();
    void    sendAdd(const std::string& name);
    void    sendRm(const std::string& name);
    void    sendBlock(const std::string& name);
    std::vector<Contact *>& getContacts();
    void    changeStatusText(const std::string& newStat);
    void    changeStatus(Contact::eStatus status);
    void    handleCall(const std::string&, const std::string&);
    void    show();
    void    close();
    bool    isClosed();
    void    loop();
};

#include "Include/Window/contactWindow.h"
#include "Include/Network/network.h"
#include "Include/Model/myConnectModel.h"

#endif // MYCONTACTW_H
