#ifndef MYCONTACTW_H
#define MYCONTACTW_H

#include "Include/Model/contact.h"
#include "Include/Model/myConnectModel.h"
#include "Include/Network/network.h"
#include "Include/Window/contactWindow.h"

class MyContactModel
{
  std::vector<Contact *>  _contactList;
  Network                 _net;
  ContactWindow           _w;
  MyConnectModel          _connect;

public:
  MyContactModel(QWidget *parent = 0);
  ~MyContactModel();

   void    setContacts(std::vector<std::string>& list);
   void    addContact(const std::string &ip, const std::string &name, QWidget *parent);
   void    rmContact(const std::string &name);
   std::vector<Contact *>& getContacts();
   void    show();
   void    close();
   bool    isVisible();
};

#endif // MYCONTACTW_H
