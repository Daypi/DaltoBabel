#include <QRect>
#include <QDesktopWidget>
#include <QPixmap>
#include <QLabel>
#include "Include/Window/connectWindow.h"
#include "Include/Model/myContactModel.h"
#include "ui_connectWindow.h"

ConnectWindow::ConnectWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ConnectWindow)
{
  QPalette pal;
  pal.setBrush(QPalette::Background, QBrush(QPixmap("../media/image.jpg")));
  this->setPalette(pal);

  ui->setupUi(this);
  centerWindow();
  this->show();
}

void    ConnectWindow::centerWindow()
{
  QRect position = frameGeometry();
  position.moveCenter(QDesktopWidget().availableGeometry().center());
  move(position.topLeft());
}

ConnectWindow::~ConnectWindow()
{
  delete ui;
}

void ConnectWindow::on_valider_clicked()
{
  this->close();
  MyContactModel *w = new MyContactModel();
}
