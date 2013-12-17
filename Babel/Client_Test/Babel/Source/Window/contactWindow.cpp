#include "Include/Window/contactWindow.h"
#include "ui_contactWindow.h"

ContactWindow::ContactWindow(MyContactModel *model, QWidget *parent) :
  QDialog(parent),
  _model(model),
  ui(new Ui::ContactWindow)
{
    ui->setupUi(this);
    this->show();
}

ContactWindow::~ContactWindow()
{
    delete ui;
}

void    ContactWindow::setContacts(std::vector<Contact *>& list)
{
  unsigned int  size;
  unsigned int  i;

  size = list.size();
  for (i = 0; i < size; ++i)
    {
      this->ui->listContact->addItem(list[i]->getName().c_str());
    }
}

void    ContactWindow::on_call_clicked()
{
  std::string   tmp;
  unsigned int  i;
  unsigned int  size;
  std::vector<Contact *> _contactList(_model->getContacts());

  if (this->ui->listContact->selectedItems().isEmpty())
    return;
  tmp = this->ui->listContact->selectedItems().front()->text().toStdString();
  size = _contactList.size();
  for (i = 0; i < size; ++i)
    {
      if (tmp == _contactList[i]->getName())
        {
          _contactList[i]->myShow();
          _contactList[i]->setCalling(true);
        }
    }
}

void ContactWindow::on_chat_clicked()
{
//  std::string   tmp;
//  unsigned int  i;
//  unsigned int  size;

//  if (this->ui->listContact->selectedItems().isEmpty())
//    return;
//  tmp = this->ui->listContact->selectedItems().front()->text().toStdString();
//  size = _contactList.size();
//  for (i = 0; i < size; ++i)
//    {
//      if (tmp == _contactList[i]->getName())
//        {
//          _contactList[i]->myShow();
//          _contactList[i]->setCalling(false);
//        }
//    }
}
