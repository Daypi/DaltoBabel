#include <QRect>
#include <QDesktopWidget>
#include <QPixmap>
#include <QLabel>
#include "Include/Window/connectWindow.h"
#include "Include/Model/myContactModel.h"
#include "ui_connectWindow.h"

ConnectWindow::ConnectWindow(MyConnectModel *model, QWidget *parent) :
    QMainWindow(parent),
    _model(model),
    ui(new Ui::ConnectWindow)
{
    QPalette pal;
    pal.setBrush(QPalette::Background, QBrush(QPixmap("/home/mckevin/Projects/image.jpg")));
    this->setPalette(pal);
    ui->setupUi(this);
    centerWindow();
    this->show();
}

ConnectWindow::~ConnectWindow()
{
    delete ui;
}

void    ConnectWindow::centerWindow()
{
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
}

void    ConnectWindow::on_valider_clicked()
{
    if (ui->editLogin->text().size() > 0 && ui->editMdp->text().size() > 0)
    {
        try
        {
            this->_model->connect(ui->editLogin->text().toStdString(), ui->editMdp->text().toInt());
            this->close();
            MyContactModel *w = new MyContactModel();
        }
        catch (Exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}
