#ifndef MOJ_POKER_H
#define MOJ_POKER_H
#include <QObject>

class moj_poker
{
public:
    moj_poker();
};


class karta
{
public:
    QString figura;
    QString kolor;
    int waga;
};


class talia
{
    karta t[52];//tablica kart
    int iloscKart;
public:
    talia();
    friend void tasuj(talia &);
    friend karta dajKarte(talia &);
    friend void pierwszeRozdanie(talia &);
};


class gracz : public QObject
{


private:

    karta card1;
    karta card2;
    QString name;
    bool isComputer;
    int iloscZetonowGracza;



public:
    gracz(QString = "Computer", bool = true, int = 5000);
    QString getCard1Name();
    QString getCard2Name();
    QString getName();
    int getIloscZetonow();
    void setCard1(karta card);
    void setCard2(karta card);
    void obstaw(int);
    void podejmijDecyzje();



};

class krupier
{
    karta stol[5];
    static int iloscZetonowKrupiera;
    int iloscKartNaStole;

public:
    krupier();
    int getIloscZetonow();
    friend void gracz::obstaw(int);//sloty można zaprzyjaziniać z innymi klasami jak funkcje
    void setStol(karta card);
    QString getCardName();

};





#endif // MOJ_POKER_H
