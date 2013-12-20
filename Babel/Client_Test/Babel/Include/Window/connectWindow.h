#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>


class MyConnectModel;

namespace Ui {
class ConnectWindow;
}

class ConnectWindow : public QDialog
{
    Q_OBJECT
    MyConnectModel  *_model;
public:
    explicit ConnectWindow(MyConnectModel *model, QWidget *parent = 0);
    ~ConnectWindow();

    void    centerWindow();
    void    setBackground();
    void    Loop();
    void    closeEvent(QCloseEvent *event);

private slots:
    void on_valider_clicked();

private:
    Ui::ConnectWindow *ui;
};

#include "Include/Model/myConnectModel.h"

#endif // CONNECTWINDOW_H
