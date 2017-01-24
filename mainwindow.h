#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "moj_poker.h"
#include <QLineEdit>
#include <QtCore>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QSlider>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
//Q_OBJECT to makro pozwalające na używanie slotów sygnałów w każdej klasie w której go użyliśmy.
//użycie makra powoduje wygenerowanie pliku moc_naszaNazwaPlikuWyjściowego który polecam sprawdzić po kompilacji

public:
    explicit MainWindow(QWidget *parent = 0);//linijka automatycznie wygenerowana przez IDE
    QLineEdit* imiewsk;
    QLabel* wygrywajacy;
    QLabel *kasaGracza;
    QLabel *kasaPoPostawieniu;
    QSlider *suwak;
    Krupier krupier1;
    Talia tali;
    Gracz *wskPlayer;
    Krupier *wskKrupier;
    Gracz player;
    Gracz gracz1;
    Gracz gracz2;
    Gracz gracz3;
    Gracz gracz4;
    int turaGry;



    ~MainWindow();


private slots:
//w slotach wstawiłem funkcjonalności przycisków
    void on_rozpocznij_gre_clicked();
    void on_ok_clicked();
    void czekajClicked();
    void obstawClicked();
    void pasujClicked();
    void sprawdzClicked();
    void przebijClicked();





private:
    Ui::MainWindow *ui;
    void start_gry();
    void start_okna();
    void rozdajKartyKrupierowi();
    void pierwszeRozdanie();
    void decyzjaSI();
    void uruchomPrzyciski();
    void wylaczPrzyciski();
    Gracz wylonWygranego();
    void dokonczTure();
    void sprzatanie();
};

#endif // MAINWINDOW_H
