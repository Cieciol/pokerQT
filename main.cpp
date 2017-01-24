#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QtCore>
#include <QPushButton>
#include <QTime>

//kod wygenerowany przez QT odpowiada za start aplikacji


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
        w->setWindowTitle("Menu");//dopisana przeze mnie linijka, wiadomo co robi

    w->show();


    return a.exec();
}

//kod zostawiony aby pokazać jak sprawdzałem aktualne stany zmiennych w funkcji kiedy nie mogłem inaczej

//QDialog *oknoo = new QDialog;
//QLabel *tekst  = new QLabel;
//tekst->setNum(wskPlayer->getIloscZetonow());
//QGridLayout *Lay = new QGridLayout;
//Lay->addWidget(tekst);
//oknoo->setLayout(Lay);
//oknoo->show();
