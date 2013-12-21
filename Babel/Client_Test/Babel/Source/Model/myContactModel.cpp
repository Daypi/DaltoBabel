#include <QCoreApplication>
#include "Include/Model/myContactModel.h"

MyContactModel::MyContactModel(QWidget *parent)
    : _w(this, parent),
      _connect(&_net, this, &_w)
{
    std::vector<std::string> test;

    test.push_back("DaltoCon");
    test.push_back("Zizi");
    test.push_back("Daypi");
    test.push_back("Collegue");
    test.push_back("eddy le gay");
    setContacts(test);
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
            _contactList.push_back(new Contact("127.0.0.1", list[i], _contactList.size() + 1, &_w));
    }
    this->_w.setContacts(_contactList);
}


void    MyContactModel::addContact(const std::string &ip, const std::string &name, QWidget *parent)
{
    unsigned int    i;
    bool            find(false);

    for (i = 0; i < _contactList.size(); ++i)
        if (_contactList[i]->getName() == name)
            find = true;
    if (!find)
        _contactList.push_back(new Contact(ip, name, _contactList.size() + 1, parent));
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
}

void    MyContactModel::close()
{
    this->_w.close();
    exit(0);
}

bool    MyContactModel::isVisible()
{
    return (this->_w.isVisible());
}

