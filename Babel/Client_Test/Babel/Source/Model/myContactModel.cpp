#include <QCoreApplication>
#include <ctime>
#include "Include/Model/myContactModel.h"
#include "Include/Network/TimeStamp.h"

MyContactModel::MyContactModel(QWidget *parent)
    : _status(AVAILABLE),
      _net(new Network(this)),
      _w(new ContactWindow(this, parent)),
      _connect(new MyConnectModel(_net, this, _w))
{
}

MyContactModel::~MyContactModel()
{
}

void    MyContactModel::setContacts(std::vector<Contact *>& list)
{
    unsigned int  size;
    unsigned int  i;
    unsigned int  j;

    size = list.size();
    for (i = 0; i < size; ++i)
    {
        for (j = 0; j < _contactList.size() && _contactList[j]->getName() != list[i]->getName(); ++j);
        if (_contactList.size() == j)
            _contactList.push_back(new Contact(*(list[i])));
        else
            _contactList[j] = list[i];
    }
    for (std::vector<Contact *>::iterator it = _contactList.begin(); it != _contactList.end();)
    {
        bool      find(false);

        for (j = 0; j < size; ++j)
            if (list[j]->getName() == (*it)->getName())
                find = true;
        if (!find)
        {
            (*it)->close();
            delete (*it);
            _contactList.erase(it);
        }
        else
            ++it;
    }
    this->_w->setContacts(_contactList);
}


void    MyContactModel::setStatusText(const std::string& newStat)
{
    this->_statusText = newStat;
}

void    MyContactModel::setStatus(eStatus status)
{
    this->_status = status;
}

void    MyContactModel::addContact(const std::string &name, const std::string &statusText, eStatus status)
{
    unsigned int    i;
    bool            find(false);

    for (i = 0; i < _contactList.size(); ++i)
        if (_contactList[i]->getName() == name)
            find = true;
    if (!find)
        _contactList.push_back(new Contact(this->_net, name, _contactList.size() + 1, statusText, status, _w));
    this->_w->setContacts(_contactList);
}

void    MyContactModel::clearContact()
{
    for (unsigned int i = 0; i < this->_contactList.size(); ++i)
        delete this->_contactList[i];
    this->_contactList.clear();
}

void    MyContactModel::sendAdd(const std::string& name)
{
    this->_net->addContact(name);
}

void    MyContactModel::sendRm(const std::string& name)
{
    this->_net->rmContact(name);
}

void    MyContactModel::sendBlock(const std::string& name)
{
    this->_net->blockContact(name);
}

void    MyContactModel::sendCall(const std::string& login)
{
    this->_net->sendCall(login);
}

void    MyContactModel::changeStatusText(const std::string& newStat)
{
    this->_net->sendStatusText(newStat);
}

void    MyContactModel::changeStatus(eStatus status)
{
    this->_net->sendStatus(status);
}

void    MyContactModel::handleCall(const std::string& login, const std::string& ip)
{
    if (this->_w->displayCall(login))
        this->_net->sendAccept(login);
    else
        this->_net->sendReject(login);
}

void    MyContactModel::closeCall()
{
    for (std::vector<Contact *>::iterator it = _contactList.begin(); it != _contactList.end(); ++it)
    {
        if ((*it)->isCalling())
        {
            (*it)->setCalling(false);
            break;
        }
    }
}

std::vector<Contact *>  &MyContactModel::getContacts()
{
    return (this->_contactList);
}

void    MyContactModel::openChat(const std::string& login)
{
    for (std::vector<Contact *>::iterator it = _contactList.begin(); it != _contactList.end(); ++it)
    {
        if (*(*it) == login)
        {
            ((*it))->setCalling(true);
            ((*it)->myShow());
            break;
        }
    }
}

ContactWindow   *MyContactModel::getWin()
{
    return (this->_w);
}

void    MyContactModel::show()
{
    this->_w->show();
    this->loop();
}

void    MyContactModel::showChat(const std::string& name)
{
    unsigned int    size;
    unsigned int    i;

    size = _contactList.size();
    for (i = 0; i < size; ++i)
    {
        if (name == _contactList[i]->getName())
        {
            _contactList[i]->myShow();
            _contactList[i]->setCalling(false);
        }
    }
}

void    MyContactModel::displayMsg(const std::string& login, const std::string& msg)
{
    for (std::vector<Contact *>::iterator it = _contactList.begin(); it != _contactList.end(); ++it)
        {
            if (*(*it) == login)
            {
                (*it)->displayMsg(login, msg);
                break;
            }
        }
}

void    MyContactModel::loop()
{
    TimeStamp   time;

    while (!this->_w->isClosed())
    {
        this->_w->refresh();
        if (time.elapsedTime(false) > MY_TIMEOUT)
        {
            std::cout << "PING" << std::endl;
            this->_net->sendPing();
            time.elapsedTime();
        }
        try
        {
            this->_net->handleNetwork();
        }
        catch (Exception &e)
        {
            std::cout << e.what() << std::endl;
            this->close();
        }
    }
}

void    MyContactModel::close()
{
    this->_w->close();
    this->_w->refresh();
}

bool    MyContactModel::isClosed()
{
    return (this->_w->isClosed());
}



