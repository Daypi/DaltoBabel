#include <QCoreApplication>
#include "Include/Model/myContactModel.h"

MyContactModel::MyContactModel(QWidget *parent)
    : _status(Contact::AVAILABLE),
      _w(this, parent),
      _connect(&_net, this, &_w)
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
            _contactList.push_back(new Contact(list[i], _contactList.size() + 1, "Online", Contact::AVAILABLE, &_w));
    }
    this->_w.setContacts(_contactList);
}

void    MyContactModel::addContact(const std::string &name, const std::string &statusText, Contact::eStatus status, QWidget *parent)
{
    unsigned int    i;
    bool            find(false);

    for (i = 0; i < _contactList.size(); ++i)
        if (_contactList[i]->getName() == name)
            find = true;
    if (!find)
        _contactList.push_back(new Contact(name, _contactList.size() + 1, statusText, status, parent));
    this->_w.setContacts(_contactList);
}

void    MyContactModel::rmContact(const std::string &name)
{
    for (std::vector<Contact *>::iterator i = _contactList.begin(); i != _contactList.end();)
    {
        if ((*i)->getName() == name)
            _contactList.erase(i);
        if (i != _contactList.end())
            ++i;
    }
    this->_w.setContacts(_contactList);
}

std::vector<Contact *>  &MyContactModel::getContacts()
{
    return(this->_contactList);
}

void    MyContactModel::show()
{
    this->_w.show();
    this->loop();
}

void    MyContactModel::loop()
{
    while (this->_w.isVisible())
    {
        this->_w.refresh();
        try
        {
            this->_net.handleNetwork();
        }
        catch (Exception &e)
        {
            throw Exception(e);
        }
    }
}

void    MyContactModel::close()
{
    this->_w.close();
    //exit(0);
}

bool    MyContactModel::isVisible()
{
    return (this->_w.isVisible());
}



