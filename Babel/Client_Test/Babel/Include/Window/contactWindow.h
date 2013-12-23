#ifndef CONTACTWINDOW_H
#define CONTACTWINDOW_H

#include <QDialog>
#include "Include/Model/contact.h"

class MyContactModel;

namespace Ui {
class ContactWindow;
}

class ContactWindow : public QDialog
{
    Q_OBJECT
    MyContactModel  *_model;

public:
    explicit ContactWindow(MyContactModel *model, QWidget *parent = 0);
    ~ContactWindow();

    void  setContacts(std::vector<Contact *> &list);
    void  refresh();
    void    closeEvent(QCloseEvent *event);

private slots:
    void on_call_clicked();
    void on_chat_clicked();
    void on_wizz_clicked();
    void on_add_clicked();
    void on_remove_clicked();
    void on_block_clicked();

    void on_status_currentIndexChanged(int index);

    void on_editStatusText_editingFinished();

private:
    Ui::ContactWindow *ui;
};

#include "Include/Model/myContactModel.h"

#endif // CONTACTWINDOW_H
