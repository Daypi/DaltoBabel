#include <QRect>
#include <QDesktopWidget>
#include <QPixmap>
#include <QLabel>
#include <QCryptographicHash>
#include "Include/Window/connectWindow.h"
#include "Include/Model/myContactModel.h"
#include "ui_connectWindow.h"

ConnectWindow::ConnectWindow(MyConnectModel *model, QWidget *parent) :
    QDialog(parent),
    _model(model),
    _close(false),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);
    setBackground();
    centerWindow();
    ui->editIP->setText("192.168.1.16");
    ui->editPort->setText("11235");
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

    if (!ui->editLogin->text().isEmpty() && !ui->editMdp->text().isEmpty() && !ui->editIP->text().isEmpty() && !ui->editPort->text().isEmpty())
    {
        try
        {
            this->_model->connect(ui->editIP->text().toStdString(), ui->editPort->text().toInt());
        }
        catch (Exception &e)
        {
            msgBox.setText(e.what());
            msgBox.exec();
        }
    }
}

bool    ConnectWindow::getNewUser()
{
    return (this->ui->newUser->isChecked());
}

bool    ConnectWindow::isClosed()
{
    return (this->_close);
}

void    ConnectWindow::setClose(bool value)
{
    this->_close = value;
}

const std::string   ConnectWindow::getLogin()
{
    return (this->ui->editLogin->text().toStdString());
}

const std::string   ConnectWindow::getMdp()
{
    QString tmp = QCryptographicHash::hash((this->ui->editMdp->text().toAscii()),QCryptographicHash::Md5).toHex();
//    return (this->ui->editMdp->text().toStdString());
    return (tmp.toStdString());
}

void    ConnectWindow::closeEvent(QCloseEvent *event)
{
    if (!_close)
    {
        _close = true;
        event->ignore();
    }
    else
    {
        this->_model->close();
        event->accept();
    }
}
