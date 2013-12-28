#include <QCoreApplication>
#include <ctime>
#include "Include/Model/myContactModel.h"

MyContactModel::MyContactModel(QWidget *parent)
    : _status(Contact::AVAILABLE),
      _net(new Network(this)),
      _w(new ContactWindow(this, parent)),
      _connect(new MyConnectModel(_net, this, _w))
{
}

MyContactModel::~MyContactModel()
{
}

void    MyContactModel::setContacts(std::vector<std::string>& list)
{
    unsigned int  size;
    unsigned int  i;
    unsigned int  j;

    size = list.size();
    for (i = 0; i < size; ++i)
    {
        bool      find(false);

        for (j = 0; j < _contactList.size(); ++j)
            if (_contactList[j]->getName() == list[i])
                find = true;
        if (!find)
            _contactList.push_back(new Contact(list[i], _contactList.size() + 1, "Online", Contact::AVAILABLE, _w));
    }
    this->_w->setContacts(_contactList);
}

void    MyContactModel::setStatusText(const std::string& newStat)
{
    this->_statusText = newStat;
}

void    MyContactModel::setStatus(Contact::eStatus status)
{
    this->_status = status;
}

void    MyContactModel::addContact(const std::string &name, const std::string &statusText, Contact::eStatus status)
{
    unsigned int    i;
    bool            find(false);

    for (i = 0; i < _contactList.size(); ++i)
        if (_contactList[i]->getName() == name)
            find = true;
    if (!find)
        _contactList.push_back(new Contact(name, _contactList.size() + 1, statusText, status, _w));
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

void    MyContactModel::changeStatusText(const std::string& newStat)
{
    this->_net->sendStatusText(newStat);
}

void    MyContactModel::changeStatus(Contact::eStatus status)
{
    this->_net->sendStatus(status);
}

void    MyContactModel::handleCall(const std::string& login, const std::string& ip)
{
    if (this->_w->displayCall(login))
        this->_net->sendAccept(login);
    this->_net->sendReject(login);
}

std::vector<Contact *>  &MyContactModel::getContacts()
{
    return(this->_contactList);
}

void    MyContactModel::show()
{
    this->_w->show();
    this->loop();
}

void    MyContactModel::loop()
{
    clock_t   time;

    time = clock();
    while (this->_w->isVisible())
    {
        this->_w->refresh();
        if ((clock() - time) / CLOCKS_PER_SEC > MY_TIMEOUT)
        {
            std::cout << "PING" << std::endl;
            this->_net->sendPing();
            time = clock();
        }
        try
        {
            this->_net->handleNetwork();
        }
        catch (Exception &e)
        {
            throw Exception(e);
        }
    }
}

void    MyContactModel::close()
{
    this->_w->close();
}

bool    MyContactModel::isVisible()
{
    return (this->_w->isVisible());
}



