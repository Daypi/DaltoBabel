#ifndef MYCONTACTW_H
#define MYCONTACTW_H

#define MY_TIMEOUT (45)

#include <string>
#include <vector>
#include <QWidget>

enum eStatus
{
    AVAILABLE = 0,
    BUSY,
    AWAY,
    INVISIBLE,
    ENUM_COUNT
};

class ContactWindow;
class Network;
class MyConnectModel;
class Contact;

class MyContactModel
{
    std::vector<Contact *>  _contactList;
    eStatus                 _status;
    std::string             _statusText;
    Network                 *_net;
    ContactWindow           *_w;
    MyConnectModel          *_connect;

public:
    MyContactModel(QWidget *parent = 0);
    ~MyContactModel();

    void    setContacts(std::vector<Contact *> &list);
    void    setStatusText(const std::string& newStat);
    void    setStatus(eStatus status);
    void    addContact(const std::string &name, const std::string &statusText, eStatus status);
    void    clearContact();
    void    sendAdd(const std::string& name);
    void    sendRm(const std::string& name);
    void    sendBlock(const std::string& name);
    void    sendCall(const std::string& login);
    std::vector<Contact *>& getContacts();
    void    openChat(const std::string& login);
    ContactWindow *getWin();
    void    changeStatusText(const std::string& newStat);
    void    changeStatus(eStatus status);
    void    handleCall(const std::string&, const std::string&);
    void    show();
    void    showChat(const std::string &login);
    void    displayMsg(const std::string& login, const std::string& msg);
    void    close();
    bool    isClosed();
    void    loop();
};

#include "Include/Window/contactWindow.h"
#include "Include/Network/network.h"
#include "Include/Model/myConnectModel.h"
#include "Include/Model/contact.h"

#endif // MYCONTACTW_H
