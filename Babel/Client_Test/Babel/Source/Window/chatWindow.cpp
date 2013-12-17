#include "Include/Window/chatWindow.h"
#include "ui_chatWindow.h"

ChatWindow::ChatWindow(const std::string &name, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ChatWindow)
{
  ui->setupUi(this);
  ui->name->setText(name.c_str());
  this->setWindowTitle(name.c_str());
  this->hide();
}

ChatWindow::~ChatWindow()
{
  delete ui;
}

void          ChatWindow::myShow()
{
  if (this->isHidden())
    this->show();
  else
    this->activateWindow();
}

void           ChatWindow::setChat(std::vector<std::string> &hist)
{
  QString       str;
  unsigned int  size;
  unsigned int  i;

  ui->chat->clear();
  size = hist.size();
  for (i = 0; i < size; ++i)
    {
      str += hist[i].c_str();
      str += "\n";
    }
  if (!str.isEmpty())
    ui->chat->setText(str);
}

void          ChatWindow::setCalling(bool b)
{
  if (b)
    {
      this->ui->call->setText("Hang up");
      this->ui->close->setText("Close and Hang up");
    }
  else
    {
      this->ui->call->setText("Call");
      this->ui->close->setText("Close");
    }
}

void          ChatWindow::on_close_clicked()
{
    this->hide();
}
