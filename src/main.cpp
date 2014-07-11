#include <QApplication>

#include "mainwindow.h"
#include "selectwindow.h"

int main( int argv, char* argc[] ) {

  QApplication app( argv, argc );

  SelectWindow selectWindow;
  selectWindow.setWindowTitle("Select Players");
  selectWindow.show();

  return app.exec();
}
