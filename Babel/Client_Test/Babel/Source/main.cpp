#include <QApplication>
#include "Include/Model/myContactModel.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MyContactModel w;

  return a.exec();
}
