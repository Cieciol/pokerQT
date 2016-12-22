#include "moj_poker.h"

moj_poker::moj_poker()
{

}

talia::talia()
{
   talia::iloscKart = 52;

    QString figury[13] = {
        "dwójka", "trójka", "czwórka", "piątka", "szóstka", "siudemka", "ósemka", "dziewiątka", "dziesiątka", "walet", "dama", "król", "as"
    };
    QString kolory[4] = { "kier", "pik", "karo", "trefl" };
    int bierzaca_karta = 0;
    for (int i=0 ; i<13 ; i++)
    {
        for (int j = 0; j < 4; j++) {
            t[bierzaca_karta].figura = figury[i];
            t[bierzaca_karta].kolor = kolory[j];
            bierzaca_karta++;
        }
    }
};

void tasuj(talia &tal)
{

    karta KartaLosowa, KartaLosowa2;
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

karta dajKarte(talia &tali)
{
    karta zwracana= tali.t[tali.iloscKart - 1];
    tali.iloscKart--;
    return zwracana;
};

gracz::gracz(QString imie, bool czyKomputer, int kasa)
{
    name = imie;
    isComputer = czyKomputer;
    iloscZetonowGracza = kasa;

}

QString gracz::getCard1Name()
{
    QString cardName;
    cardName = card1.figura + " " + card1.kolor;
    return cardName;
}

QString gracz::getCard2Name()
{
    QString cardName;
    cardName = card2.figura + " " + card2.kolor;

    return cardName;
}

int gracz::getIloscZetonow()
{
    return iloscZetonowGracza;
}

void gracz::setCard1(karta card)
{
    card1 = card;
}

void gracz::setCard2(karta card)
{
    card2 = card;
}

QString gracz::getName()
{
    return name;
}

void gracz::obstawClicked(int postawione)
{
    QWidget *okna = new QWidget;
    okna->show();
    iloscZetonowGracza -= postawione;
    krupier::iloscZetonowKrupiera += postawione;
}

int krupier::iloscZetonowKrupiera = 0;

krupier::krupier()
{
    iloscKartNaStole = 0;
}

void krupier::setStol(karta card)
{
    stol[iloscKartNaStole] = card;
    iloscKartNaStole++;
}

int krupier::getIloscZetonow()
{
    return krupier::iloscZetonowKrupiera;
}

QString krupier::getCardName()
{
        QString cardName;
        cardName  = QString("%1 %2").arg(stol[iloscKartNaStole -1].figura) .arg(stol[iloscKartNaStole - 1].kolor);


        return cardName;
}
