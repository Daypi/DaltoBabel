#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include "Include/Window/contactWindow.h"
#include "ui_contactWindow.h"

ContactWindow::ContactWindow(MyContactModel *model, QWidget *parent) :
    QDialog(parent),
    _model(model),
    _close(false),
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
    std::vector<QString> tab;

    tab.push_back("Available");
    tab.push_back("Busy");
    tab.push_back("Away");
    tab.push_back("Invisible");
    size = list.size();
    this->ui->listContact->clear();
    for (i = 0; i < size; ++i)
    {
        QString tmp;
        tmp = list[i]->getName().c_str();
        tmp += " - ";
        tmp += list[i]->getStatusText().c_str();
        tmp += " (";
        if (list[i]->getStatus() <= 3)
            tmp += tab[list[i]->getStatus()];
        tmp += ")";
        this->ui->listContact->addItem(tmp);
    }
    if (i == 0)
        this->ui->listContact->addItem("No Contact Yet");
}

void    ContactWindow::refresh()
{
    QCoreApplication::processEvents();
}

bool    ContactWindow::displayCall(const std::string& login)
{
    QMessageBox msgBox;
    int         ret;
    QString     tmp(login.c_str());

    msgBox.setText("You have a call from " + tmp);
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
        return (true);
    return (false);
}

bool    ContactWindow::isClosed()
{
    return (this->_close);
}

void    ContactWindow::on_call_clicked()
{
    if (this->ui->listContact->selectedItems().isEmpty())
        return;
    QString tmp(this->ui->listContact->selectedItems().front()->text());
    tmp = tmp.split(" ")[0];
    this->_model->sendCall(tmp.toStdString());
}

void ContactWindow::on_chat_clicked()
{
    if (this->ui->listContact->selectedItems().isEmpty())
        return;
    QString tmp(this->ui->listContact->selectedItems().front()->text());
    tmp = tmp.split(" ")[0];
    this->_model->showChat(tmp.toStdString());
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
        this->_model->sendAdd(text.toStdString());
}

void ContactWindow::on_remove_clicked()
{
    QMessageBox msgBox;
    int         ret;

    if (this->ui->listContact->selectedItems().isEmpty())
        return;
    QString     tmp(this->ui->listContact->selectedItems().front()->text());

    tmp = tmp.split(" ")[0];
    msgBox.setText("Are you sure you want to remove : " + tmp);
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
        this->_model->sendRm(tmp.toStdString());
}

void ContactWindow::on_block_clicked()
{
    QMessageBox msgBox;
    int         ret;

    if (this->ui->listContact->selectedItems().isEmpty())
        return;
    QString     tmp(this->ui->listContact->selectedItems().front()->text());

    tmp = tmp.split(" ")[0];
    msgBox.setText("Are you sure you want to block : " + tmp);
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
        this->_model->sendBlock(tmp.toStdString());
}

void    ContactWindow::closeEvent(QCloseEvent *event)
{
    if (!this->_close)
    {
        _close = true;
        event->ignore();
    }
    else
        event->accept();
}

void ContactWindow::on_status_currentIndexChanged(int index)
{
    this->_model->changeStatus((eStatus)index);
}

void ContactWindow::on_editStatusText_editingFinished()
{
    this->_model->changeStatusText(this->ui->editStatusText->text().toStdString());
}
