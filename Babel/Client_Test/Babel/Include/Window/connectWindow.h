#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

class MyConnectModel;

namespace Ui {
class ConnectWindow;
}

class ConnectWindow : public QMainWindow
{
    Q_OBJECT
    MyConnectModel  *_model;
public:
    explicit ConnectWindow(MyConnectModel *model, QWidget *parent = 0);
    ~ConnectWindow();

    void    centerWindow();

private slots:
    void on_valider_clicked();

private:
    Ui::ConnectWindow *ui;
};

#include "Include/Model/myConnectModel.h"

#endif // CONNECTWINDOW_H
