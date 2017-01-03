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


//QDialog *oknoo = new QDialog;
//QLabel *tekst  = new QLabel;
//tekst->setNum(wskPlayer->getIloscZetonow());
//QGridLayout *Lay = new QGridLayout;
//Lay->addWidget(tekst);
//oknoo->setLayout(Lay);
//oknoo->show();
