#include "Include/Window/contactWindow.h"
#include "Include/Model/contact.h"

Contact::Contact(Network *net, const std::string& name, unsigned int uid, const std::string& statusText, eStatus status, QWidget *parent)
    :  _uid(uid), _name(name), _statusText(statusText), _status(status)
{
    _c = new MyChatModel(net, name, parent);
}

Contact::Contact(const Contact& oldContact)
    :  _uid(oldContact._uid), _ip(oldContact._ip), _name(oldContact._name), _statusText(oldContact._statusText), _status(oldContact._status), _c(oldContact._c)
{
}

Contact     &Contact::operator=(const Contact &other)
{
    if (this != &other)
    {
        _uid = other._uid;
        _statusText = other._statusText;
        _status = other._status;
    }
    return (*this);
}

Contact     *Contact::operator=(Contact *other)
{
    if (this != other)
    {
        _uid = other->getId();
        _statusText = other->getStatusText();
        _status = other->getStatus();
    }
    return (this);
}

Contact::~Contact()
{
}

bool                    Contact::operator==(const std::string& name)
{
    return (this->_name == name);
}

bool                    Contact::operator==(const Contact& contact)
{
    return (this->_name == contact.getName());
}

void                    Contact::clearChat()
{
    this->_chat.clear();
    this->_c->setChat(_chat);
}

void                    Contact::setMsg(const std::string& msg)
{
    this->_chat.push_back(msg);
    this->_c->setChat(_chat);
}

void                    Contact::setChat(const std::vector<std::string>& chat)
{
    this->_chat.clear();
    this->_chat = chat;
    this->_c->setChat(_chat);
}

void                    Contact::setStatusText(const std::string& status)
{
    this->_statusText = status;
}

void                    Contact::setStatus(eStatus status)
{
    this->_status = status;
}

void                    Contact::setName(const std::string& name)
{
    this->_name = name;
}

void                    Contact::setIp(const std::string& ip)
{
    this->_ip = ip;
}

const std::string&      Contact::getStatusText() const
{
    return (this->_statusText);
}

eStatus      Contact::getStatus() const
{
    return (this->_status);
}

const std::string&      Contact::getName() const
{
    return (this->_name);
}

const std::string&      Contact::getIp() const
{
    return (this->_ip);
}

unsigned int            Contact::getId() const
{
    return (this->_uid);
}

std::vector<std::string>&    Contact::getChat()
{
    return (this->_chat);
}

void                    Contact::myShow()
{
    _c->myShow();
}

void                    Contact::setCalling(bool b)
{
    this->_c->setCalling(b);
}

bool                    Contact::isCalling() const
{
    return (this->_c->isCalling());
}

void                    Contact::close()
{
    this->_c->close();
}

void                    Contact::displayMsg(const std::string &login, const std::string &msg)
{
    this->_c->displayMsg(login, msg);
}
