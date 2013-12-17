#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>

namespace Ui {
  class ChatWindow;
}

class ChatWindow : public QDialog
{
  Q_OBJECT

public:
  explicit ChatWindow(const std::string &name, QWidget *parent = 0);
  ~ChatWindow();

  void    myShow();
  void    setChat(std::vector<std::string> &hist);
  void    setCalling(bool b);
private slots:
  void on_close_clicked();

private:
  Ui::ChatWindow *ui;
};

#endif // CHATWINDOW_H
