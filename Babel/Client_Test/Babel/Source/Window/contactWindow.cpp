#include <QMessageBox>
#include <QInputDialog>
#include "Include/Window/contactWindow.h"
#include "ui_contactWindow.h"

ContactWindow::ContactWindow(MyContactModel *model, QWidget *parent) :
    QDialog(parent),
    _model(model),
    ui(new Ui::ContactWindow)
{
    ui->setupUi(this);
    this->hide();
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
    this->ui->listContact->clear();
    for (i = 0; i < size; ++i)
    {
        this->ui->listContact->addItem(list[i]->getName().c_str());
    }
}

void    ContactWindow::refresh()
{
    QCoreApplication::processEvents();
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
            _contactList[i]->setCalling(false);
        }
    }
}

void ContactWindow::on_wizz_clicked()
{
    QMessageBox msgBox;

    msgBox.setText("WIZZ");
    msgBox.exec();
}

void    ContactWindow::on_add_clicked()
{
    bool    ok;
    QString text = QInputDialog::getText(this, "Add contact",
                                         "User name:", QLineEdit::Normal, "Name", &ok);
    if (ok && !text.isEmpty())
        this->_model->addContact(text.toStdString(), "Online", Contact::AVAILABLE, this);
}

void ContactWindow::on_remove_clicked()
{
    QMessageBox msgBox;
    int         ret;

    if (this->ui->listContact->selectedItems().isEmpty())
        return;
    msgBox.setText("Are you sure you want to remove : " + this->ui->listContact->selectedItems().front()->text());
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
        this->_model->rmContact(this->ui->listContact->selectedItems().front()->text().toStdString());
}

void ContactWindow::on_block_clicked()
{
    //To do
}

void    ContactWindow::showEvent(QShowEvent *event)
{
    event->accept();
}

void    ContactWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    exit(0);
}
