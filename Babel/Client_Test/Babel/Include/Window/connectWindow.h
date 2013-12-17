#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QMainWindow>

namespace Ui {
  class ConnectWindow;
}

class ConnectWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit ConnectWindow(QWidget *parent = 0);
  ~ConnectWindow();

  void    centerWindow();

private slots:
  void on_valider_clicked();

private:
  Ui::ConnectWindow *ui;
};

#endif // CONNECTWINDOW_H
