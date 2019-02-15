#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "srcpreview.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow* w = MainWindow::instance();
    w->show();

    return a.exec();
}
