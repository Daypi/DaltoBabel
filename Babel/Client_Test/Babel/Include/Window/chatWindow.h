#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>

class MyChatModel;

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QDialog
{
    Q_OBJECT
    MyChatModel     *_model;

public:
    explicit ChatWindow(const std::string &name, MyChatModel *model, QWidget *parent = 0);
    ~ChatWindow();

    void    myShow();
    void    setChat(std::vector<std::string> &hist);
    void    addMsg(const std::string& msg);
    void    setCalling(bool b);

private slots:
    void on_close_clicked();
    void on_send_clicked();
    void on_call_clicked();

private:
    Ui::ChatWindow *ui;
};

#include "Include/Model/myChatModel.h"
#endif // CHATWINDOW_H
