#include "mainwindow.h"
#include "gamewindow.h"


#include <QApplication>
#include <qfont.h>
#include <QFontDatabase>
#include <QFontDialog>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
