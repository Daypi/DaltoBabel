#include <QtWidgets/QApplication>
#include "Include/Model/myContactModel.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MyContactModel w;

  while (!w.isClosed())
      a.processEvents();
  return 0;
}
