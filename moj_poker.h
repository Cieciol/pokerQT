#ifndef MOJ_POKER_H
#define MOJ_POKER_H
#include <QObject>
#include <QtCore>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QSlider>


class moj_poker
{
public:
    moj_poker();
};

//plik ten zawiera moje własne klasyodpowiedzialne za główny szkielet gry
//pusta klasa moj poker jest tu dlatego że wolę mieć kilka związanych ze sobą klas w jednym miejscu a IDE Qt miało problemy z namespace

class Karta
{
public:
    QString figura;
    QString kolor;
    int waga;
};


class Talia
{
    Karta t[52];//tablica kart
    int iloscKart;
public:
    Talia();
    friend void tasuj(Talia &);
    friend Karta dajKarte(Talia &);
    friend void pierwszeRozdanie(Talia &);
};


class Gracz
{


private:

    Karta card1;
    Karta card2;
    QString name;
    bool isComputer;
    int iloscZetonowGracza;



public:
    Gracz(QString = "Computer", bool = true, int = 5000);
    Gracz(const Gracz &); //funkcja przelej zetony wymagała ode mnie takiego konstuktora
    QString getCard1Name();
    QString getCard2Name();
    QString getName();
    int getIloscZetonow();
    void setCard1(Karta card);
    void setCard2(Karta card);
    void obstawFun(int);
    void podejmijDecyzje(int tura);
    void setName(QString);
    void setIloscZetonow(int);
    bool wGrze = true;

    QLabel kasaGracza;
    QLabel karta1Gracza;
    QLabel karta2Gracza;
    QLabel imieGracza;
    QLabel decyzja;
    QPushButton czekaj;
    QPushButton obstaw;
    QPushButton pasuj;
    QPushButton sprawdz;
    QPushButton przebij;


};

class Krupier
{
    Karta stol[5];
    static int iloscZetonowKrupiera;
    int iloscKartNaStole;

public:
    Krupier();
    Krupier(const Krupier &);
    int getIloscZetonow();
    friend void Gracz::obstawFun(int);//sloty można zaprzyjaziniać z innymi klasami jak funkcje
    void setStol(Karta card);
    void wyzerujZetony();
    QString getCardName();
    QLabel wPuli;
    QLabel karta1Stol;
    QLabel karta2Stol;
    QLabel karta3Stol;
    QLabel karta4Stol;
    QLabel karta5Stol;

};





#endif // MOJ_POKER_H
