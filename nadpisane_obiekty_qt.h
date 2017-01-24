#ifndef NADPISANE_OBIEKTY_QT_H
#define NADPISANE_OBIEKTY_QT_H

#include <QObject>
#include <QPushButton>

/*
 * pierwotnie w aplikacji problem przesyłania zmiennych do funkcji
 * chciałem rozwiązać pisząc własne klasy z przyciskami i wewnątrz tych
 * klas dodać odpowiednie pola tak jak widać w poniższej próbie
 * ale problemy z kompilacją mnie przerosły i porzuciłem ten pomysł
 *
*/

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
