#include "moj_poker.h"
#define smallBid 10
#define bigBid 20

moj_poker::moj_poker()
{

}

Talia::Talia()
{
   Talia::iloscKart = 52;

    QString figury[13] = {
        "dwójka", "trójka", "czwórka", "piątka", "szóstka", "siudemka", "ósemka", "dziewiątka", "dziesiątka", "walet", "dama", "król", "as"
    };
    QString kolory[4] = { "kier", "pik", "karo", "trefl" };
    int bierzaca_Karta = 0;
    for (int i=0 ; i<13 ; i++)
    {
        for (int j = 0; j < 4; j++) {
            t[bierzaca_Karta].figura = figury[i];
            t[bierzaca_Karta].kolor = kolory[j];
            bierzaca_Karta++;
        }
    }
}

void tasuj(Talia &tal)
{
    tal.iloscKart = 52;
    Karta KartaLosowa, KartaLosowa2;
    int LiczbaLosowa, LiczbaLosowa2;

    for (int i = 0; i < 500; i++) {
        qsrand(qrand());

        LiczbaLosowa = (qrand() % 52);
        LiczbaLosowa2 = (qrand() % 52);
        KartaLosowa = tal.t[LiczbaLosowa];
        KartaLosowa2 = tal.t[LiczbaLosowa2];
        tal.t[LiczbaLosowa] = KartaLosowa2;
        tal.t[LiczbaLosowa2] = KartaLosowa;
    }
}

Karta dajKarte(Talia &tali)
{
    Karta zwracana= tali.t[tali.iloscKart - 1];
    tali.iloscKart--;
    return zwracana;
}


void Gracz::podejmijDecyzje(int tura) //w aplikacji nie zdążyłem zrobić rozsądnego modelu sztucznej inteligencji graczy a więc wszystkie decyzje są losowe
{
    int decyzja;
    if (tura == 1)
    {
        decyzja = (qrand() % 2) ;

    }
    else
    {
    decyzja = qrand() % 4;
    }
    switch ( decyzja )
    {
    case 0:
    {
        this->decyzja.setText("CZEKA");
        break;
    }
    case 1:
    {
        int kwota;
        kwota = (qrand() %(bigBid - smallBid+1)) + smallBid;
        QString obstawilText = QString("OBSTAWIŁ %1").arg(kwota);
        this->decyzja.setText(obstawilText);
        this->obstawFun(kwota);
        break;
    }
    case 2:
    {
        this->decyzja.setText("PASUJE");
        this->wGrze = false;
        break;
    }
    case 3:
    {
        this->decyzja.setText("SPRAWDZA");

        break;
    }
    }
}


Gracz::Gracz(QString imie, bool czyKomputer, int kasa)
{
    name = imie;
    isComputer = czyKomputer;
    iloscZetonowGracza = kasa;

    decyzja.setText("0");
}

Gracz::Gracz(const Gracz &_gracz)
{
    name = _gracz.name;
    isComputer = _gracz.isComputer;
    iloscZetonowGracza =_gracz.iloscZetonowGracza;


}

QString Gracz::getCard1Name()
{
    QString cardName;
    cardName = card1.figura + " " + card1.kolor;
    return cardName;
}

QString Gracz::getCard2Name()
{
    QString cardName;
    cardName = card2.figura + " " + card2.kolor;

    return cardName;
}

int Gracz::getIloscZetonow()
{
    return iloscZetonowGracza;
}

void Gracz::setCard1(Karta card)
{
    card1 = card;


}

void Gracz::setCard2(Karta card)
{
    card2 = card;


}

void Gracz::setName(QString _name)
{
    name = _name;
    imieGracza.setText(_name);

}

void Gracz::setIloscZetonow(int _iloscZetonow)
{
    iloscZetonowGracza = _iloscZetonow;
    kasaGracza.setNum(_iloscZetonow);
}

QString Gracz::getName()
{
    return name;
}

void Gracz::obstawFun(int postawione)
{
    this->iloscZetonowGracza -= postawione;
    Krupier::iloscZetonowKrupiera += postawione;

}

int Krupier::iloscZetonowKrupiera = 0;

Krupier::Krupier()
{
    iloscKartNaStole = 0;
}

Krupier::Krupier(const Krupier &)
{

}

void Krupier::setStol(Karta card)
{
    stol[iloscKartNaStole] = card;
    iloscKartNaStole++;
}

int Krupier::getIloscZetonow()
{
    return Krupier::iloscZetonowKrupiera;
}

QString Krupier::getCardName()
{
        QString cardName;
        cardName  = QString("%1 %2").arg(stol[iloscKartNaStole -1].figura) .arg(stol[iloscKartNaStole - 1].kolor);


        return cardName;
}

void Krupier::wyzerujZetony()
{
    iloscZetonowKrupiera = 0;
    iloscKartNaStole = 0;
}
