#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <vector>
#include "Include/Model/myChatModel.h"

class Contact
{
  unsigned int    _uid;
  std::string     _ip;
  std::string     _name;
  std::string     _status;
  std::vector<std::string>    _chat;
  MyChatModel     *_c;

public:
  Contact(const std::string& ip, const std::string& name, unsigned int uid, QWidget *parent);
  Contact(const Contact& oldContact);
  ~Contact();

  bool                    operator==(const std::string& name);
  bool                    operator==(const Contact& contact);
  void                    clearChat();
  void                    setMsg(const std::string& msg);
  void                    setChat(std::vector<std::string>& msg);
  void                    setStatus(std::string& status);
  void                    setName(std::string& name);
  const std::string&      getStatus() const;
  const std::string&      getName() const;
  const std::string&      getIp() const;
  unsigned int            getId() const;
  std::vector<std::string>&    getChat();

  void                    myShow();
  void                    setCalling(bool b);
  bool                    isCalling() const;
};

#endif // CONTACT_H
