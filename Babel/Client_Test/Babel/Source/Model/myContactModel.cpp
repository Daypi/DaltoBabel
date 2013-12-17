#include "Include/Model/myContactModel.h"

MyContactModel::MyContactModel(QWidget *parent)
  : _w(this, parent)
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

std::vector<Contact *>  &MyContactModel::getContacts()
{
    return(this->_contactList);
}
