#include <QtGui/QApplication>
#include "Include/Model/myConnectModel.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MyConnectModel w;

  return a.exec();
}