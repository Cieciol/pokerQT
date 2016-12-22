#ifndef NADPISANE_OBIEKTY_QT_H
#define NADPISANE_OBIEKTY_QT_H

#include <QObject>
#include <QPushButton>

class nadpisane_obiekty_QT
{
public:
    nadpisane_obiekty_QT();
};

class obstawButton: public QPushButton
{
    Q_OBJECT

    int stanSuwaka;
public:
    //obstawButton();
public slots:
    void setStanSuwaka(int);

signals:
   // void clicked(int);

};

#endif // NADPISANE_OBIEKTY_QT_H
