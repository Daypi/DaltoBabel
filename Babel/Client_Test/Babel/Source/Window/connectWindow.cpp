#include <QRect>
#include <QDesktopWidget>
#include <QPixmap>
#include <QLabel>
#include "Include/Window/connectWindow.h"
#include "Include/Model/myContactModel.h"
#include "ui_connectWindow.h"

ConnectWindow::ConnectWindow(MyConnectModel *model, QWidget *parent) :
    QDialog(parent),
    _model(model),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);
    setBackground();
    centerWindow();
    ui->editIP->setText("10.20.86.55");
    this->show();
}

ConnectWindow::~ConnectWindow()
{
    delete ui;
}

void    ConnectWindow::setBackground()
{
    QPalette pal;

    pal.setBrush(QPalette::Background, QBrush(QPixmap("Media/image.jpg")));
    this->setPalette(pal);
}

void    ConnectWindow::centerWindow()
{
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
}

void    ConnectWindow::refresh()
{
    QCoreApplication::processEvents();
}

void    ConnectWindow::on_valider_clicked()
{
    QMessageBox msgBox;

    if (ui->editLogin->text().size() > 0 && ui->editMdp->text().size() > 0 && ui->editIP->text().size() > 0)
    {
        try
        {
            this->_model->connect(ui->editIP->text().toStdString(), 11235);
            //this->_model->show();
            //this->hide();
        }
        catch (Exception &e)
        {
            msgBox.setText(e.what());
            msgBox.exec();
        }
    }
}

void    ConnectWindow::closeEvent(QCloseEvent *event)
{
    this->_model->close();
    event->accept();
}
