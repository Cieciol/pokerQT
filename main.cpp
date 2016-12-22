#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QtCore>
#include <QPushButton>
#include <QTime>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
        w->setWindowTitle("Menu");

    w->show();




    return a.exec();
}


