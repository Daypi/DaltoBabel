#include "Include/Window/contactWindow.h"
#include "Include/Model/contact.h"

Contact::Contact(const std::string& ip, const std::string& name, unsigned int uid, QWidget *parent)
  :  _uid(uid), _ip(ip), _name(name)
{
  _c = new MyChatModel(name, parent);
}

Contact::Contact(const Contact& oldContact)
  :  _uid(oldContact._uid), _ip(oldContact._ip), _name(oldContact._name), _c(oldContact._c)
{
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

void                    Contact::setChat(std::vector<std::string>& chat)
{
  this->_chat.clear();
  this->_chat = chat;
  this->_c->setChat(_chat);
}

void                    Contact::setStatus(std::string& status)
{
  this->_status = status;
}

void                    Contact::setName(std::string& name)
{
  this->_name = name;
}

const std::string&      Contact::getStatus() const
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
