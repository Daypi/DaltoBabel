#ifndef MYCONTACTW_H
#define MYCONTACTW_H

#include "Include/Model/contact.h"
#include "Include/Window/contactWindow.h"

class MyContactModel
{
  std::vector<Contact *>  _contactList;
  ContactWindow           _w;

public:
  MyContactModel(QWidget *parent = 0);
  ~MyContactModel();

   void    setContacts(std::vector<std::string>& list);
   std::vector<Contact *>& getContacts();
};

#endif // MYCONTACTW_H
