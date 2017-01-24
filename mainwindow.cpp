#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QGridLayout>
#include <QtCore>
#include <QtGui>
#include <QLineEdit>
#include <QGroupBox>
#include <QButtonGroup>
#include <QDialog>
#include <QThread>
#include "moj_poker.h"
#include "moj_poker.cpp"


#define smallBid 10
#define bigBid 20
#define pulaPoczatkowa 5000

void delay(int czasWmiliSekundach)//funkcja zwłoki przeklejona z jakiegoś forum ale kod jest czytelny i wiadomo co robi
{

    QTime dieTime= QTime::currentTime().addMSecs(czasWmiliSekundach);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void przelejZetony(Gracz &wygrany, Krupier _krupier)
{
    wygrany.setIloscZetonow(wygrany.getIloscZetonow() + _krupier.getIloscZetonow());
    wygrany.kasaGracza.setNum(wygrany.getIloscZetonow());
}
void pierwszaDecyzjaGracza(QSlider *_suwak,QPushButton *_obstaw, QPushButton *_pasuj, QLabel *_kasaGracza)
{
    _suwak->setRange(smallBid,bigBid);
    _kasaGracza->setText(QString::number(bigBid));

    _obstaw->setEnabled(1);
    _obstaw->setFlat(0);
    _pasuj->setEnabled(1);
    _pasuj->setFlat(0);

}


MainWindow::MainWindow(QWidget *parent) ://funkcja wygenerowana przez IDE
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rozpocznij_gre_clicked()// funkcja odpowiadająca za małe okienko wyskakujące po kliknięciu start gry
{
    QWidget *opcje_uruchamiania = new QWidget;
    opcje_uruchamiania->setWindowTitle("rozpocznij gre");
    QGridLayout *ustawienie_elementow = new QGridLayout;

    QPushButton *ok = new QPushButton("ZACZYNAJMY!",this);
    QPushButton *cancel = new QPushButton("ANULUJ",this);
    QLineEdit *imie = new QLineEdit;
    QLabel *imieLabel = new QLabel("podaj imie:");
    imie->setText("Imie");
    imiewsk = imie; // na początku tylko obiekty wyświetlane(przyciski i pola tekstowe) były widzialne w całej aplikacji i w celu przekazania wartości między funkcjami potrzeba było wskaźnika, w obecnym układzie można od razu użyć tutaj player.imie ale postanowiłem to zatrzymać tak jak jest dla tej uwagi

    ustawienie_elementow->addWidget(ok,1,0);
    ustawienie_elementow->addWidget(cancel,1,1);
    ustawienie_elementow->addWidget(imie,0,1);
    ustawienie_elementow->addWidget(imieLabel,0,0);


    ustawienie_elementow->setColumnStretch(0,20);
    ustawienie_elementow->setColumnStretch(1,20);
    //kilka przykładów użycia technologii sygnałów i slotów
    connect(cancel,SIGNAL(clicked()),opcje_uruchamiania,SLOT(close()));

    connect(ok,SIGNAL(clicked()),SLOT(on_ok_clicked()));
    connect(ok,SIGNAL(clicked()),opcje_uruchamiania,SLOT(close()));



    opcje_uruchamiania->setLayout(ustawienie_elementow);
    opcje_uruchamiania->show();

}

void MainWindow::on_ok_clicked()
{

    gracz1.setName("Komputer1");
    gracz1.setIloscZetonow(pulaPoczatkowa);
    gracz2.setName("Komputer2");
    gracz2.setIloscZetonow(pulaPoczatkowa);
    gracz3.setName("Komputer3");
    gracz3.setIloscZetonow(pulaPoczatkowa);
    gracz4.setName("Komputer4");
    gracz4.setIloscZetonow(pulaPoczatkowa);

    start_okna();
    start_gry();


}

void MainWindow::start_okna()//przykład stworzenia rozbudowanego okna bez użycia edytora
{

    QWidget *okno_gry = new QWidget;
    QGridLayout *lay = new QGridLayout;

    QHBoxLayout *graczeLayout = new QHBoxLayout;
    QVBoxLayout *gracz1Lay = new QVBoxLayout;
    QVBoxLayout *gracz2Lay = new QVBoxLayout;
    QVBoxLayout *gracz3Lay = new QVBoxLayout;
    QVBoxLayout *gracz4Lay = new QVBoxLayout;

    QHBoxLayout *kartyGracza1 = new QHBoxLayout;
    QHBoxLayout *kartyGracza2 = new QHBoxLayout;
    QHBoxLayout *kartyGracza3 = new QHBoxLayout;
    QHBoxLayout *kartyGracza4 = new QHBoxLayout;

    kartyGracza1->addWidget(&gracz1.karta1Gracza);
    kartyGracza1->addWidget(&gracz1.karta2Gracza);
    kartyGracza2->addWidget(&gracz2.karta1Gracza);
    kartyGracza2->addWidget(&gracz2.karta2Gracza);
    kartyGracza3->addWidget(&gracz3.karta1Gracza);
    kartyGracza3->addWidget(&gracz3.karta2Gracza);
    kartyGracza4->addWidget(&gracz4.karta1Gracza);
    kartyGracza4->addWidget(&gracz4.karta2Gracza);


    gracz1Lay->addWidget(&gracz1.imieGracza);
    gracz1Lay->addWidget(&gracz1.kasaGracza);
    gracz1Lay->addLayout(kartyGracza1);
    gracz1Lay->addWidget(&gracz1.decyzja);
    gracz1Lay->setAlignment(Qt::AlignHCenter);

    gracz2Lay->addWidget(&gracz2.imieGracza);
    gracz2Lay->addWidget(&gracz2.kasaGracza);
    gracz2Lay->addLayout(kartyGracza2);
    gracz2Lay->addWidget(&gracz2.decyzja);
    gracz2Lay->setAlignment(Qt::AlignHCenter);

    gracz3Lay->addWidget(&gracz3.imieGracza);
    gracz3Lay->addWidget(&gracz3.kasaGracza);
    gracz3Lay->addLayout(kartyGracza3);
    gracz3Lay->addWidget(&gracz3.decyzja);
    gracz3Lay->setAlignment(Qt::AlignHCenter);

    gracz4Lay->addWidget(&gracz4.imieGracza);
    gracz4Lay->addWidget(&gracz4.kasaGracza);
    gracz4Lay->addLayout(kartyGracza4);
    gracz4Lay->addWidget(&gracz4.decyzja);
    gracz4Lay->setAlignment(Qt::AlignHCenter);

    graczeLayout->addLayout(gracz1Lay);
    graczeLayout->addLayout(gracz2Lay);
    graczeLayout->addLayout(gracz3Lay);
    graczeLayout->addLayout(gracz4Lay);

    QGroupBox *gracze = new QGroupBox("GRACZE");
    gracze->adjustSize();
    gracze->setLayout(graczeLayout);


    //tworzenie okna krupiera
    QVBoxLayout *krupierLay = new QVBoxLayout;
    QLabel *wPuliLabel = new QLabel("w puli");


    QHBoxLayout *kartyNaStole = new QHBoxLayout;


    kartyNaStole->addWidget(&krupier1.karta1Stol);
    kartyNaStole->addWidget(&krupier1.karta2Stol);
    kartyNaStole->addWidget(&krupier1.karta3Stol);
    kartyNaStole->addWidget(&krupier1.karta4Stol);
    kartyNaStole->addWidget(&krupier1.karta5Stol);
    krupier1.wPuli.setNum(krupier1.getIloscZetonow());


    krupierLay->addLayout(kartyNaStole);
    krupierLay->addWidget(wPuliLabel);
    krupierLay->addWidget(&krupier1.wPuli);


    QHBoxLayout *graczLayout = new QHBoxLayout;

    player.czekaj.setText("CZEKAJ");
    player.czekaj.setFlat(1);
    player.czekaj.setDisabled(1);
    player.obstaw.setText("OBSTAW");
    player.obstaw.setFlat(1);
    player.obstaw.setDisabled(1);
    player.pasuj.setText("PASUJ");
    player.pasuj.setFlat(1);
    player.pasuj.setDisabled(1);
    player.sprawdz.setText("SPRAWDZ");
    player.sprawdz.setFlat(1);
    player.sprawdz.setDisabled(1);
    player.przebij.setText("PRZEBIJ");
    player.przebij.setFlat(1);
    player.przebij.setDisabled(1);
    QLabel *kasaDoPostawienia = new QLabel("0");
    kasaGracza = new QLabel(QString::number(player.getIloscZetonow()));
    kasaPoPostawieniu = new QLabel(QString::number((player.getIloscZetonow())));
    QLabel *otworzNawias = new QLabel("(");
    QLabel *zamknijNawias = new QLabel(")");

    QHBoxLayout *kartyLay = new QHBoxLayout;
    QSpacerItem *leftSpacer = new QSpacerItem(100,2,QSizePolicy::Expanding,QSizePolicy::Maximum);
    QSpacerItem *rightSpacer = new QSpacerItem(100,2,QSizePolicy::Expanding,QSizePolicy::Maximum);
    QSpacerItem *centerSpacer = new QSpacerItem(100,1);


    kartyLay->addSpacerItem(leftSpacer);
    kartyLay->addWidget(&player.karta1Gracza,0,Qt::AlignHCenter);
    kartyLay->addSpacerItem(centerSpacer);
    kartyLay->addWidget(&player.karta2Gracza,0,Qt::AlignHCenter);
    kartyLay->addSpacerItem(rightSpacer);


    suwak = new QSlider;
    QSpacerItem *gornaPrzestrzen = new QSpacerItem(1,200,QSizePolicy::Minimum,QSizePolicy::Ignored);
    QSpacerItem *dolnaPrzestrzen = new QSpacerItem(1,27);
    suwak->setMinimumHeight(200);
    suwak->setMaximumHeight(250);



    suwak->setRange(0,player.getIloscZetonow());
    connect(suwak,SIGNAL(valueChanged(int)),kasaDoPostawienia,SLOT(setNum(int)));




    graczLayout ->addWidget(&player.czekaj);
    graczLayout ->addWidget(&player.obstaw);
    graczLayout ->addWidget(&player.pasuj);
    graczLayout ->addWidget(&player.sprawdz);
    graczLayout ->addWidget(&player.przebij);

    QHBoxLayout *postawienieLay = new QHBoxLayout;
    QVBoxLayout *bottomLay = new QVBoxLayout;
    QVBoxLayout *leftLay = new QVBoxLayout;

    postawienieLay->addWidget(kasaGracza);
    postawienieLay->addWidget(otworzNawias);
    postawienieLay->addWidget(kasaPoPostawieniu);
    postawienieLay->addWidget(zamknijNawias);

    //leftLay->addSpacing(400);
    leftLay->addItem(gornaPrzestrzen);
    leftLay->setStretch(0,2);
    leftLay->addLayout(postawienieLay);
    leftLay->addWidget(suwak,0);
    leftLay->addWidget(kasaDoPostawienia);
    leftLay->addItem(dolnaPrzestrzen);
    //leftLay->addSpacing(100);

    graczeLayout->SetMinimumSize;
    lay->addLayout(krupierLay,1,1,1,1,Qt::AlignCenter);
    lay->addLayout(leftLay,1,1,1,1,Qt::AlignLeft);
    bottomLay->addLayout(kartyLay);
    bottomLay->addLayout(graczLayout);
    lay->addWidget(gracze,1,1,1,1,Qt::AlignTop);
    lay->addLayout(bottomLay,1,1,1,1,Qt::AlignBottom);


    okno_gry->setLayout(lay);
    okno_gry->showMaximized();



}

void MainWindow::start_gry()
{
    tasuj(tali);
    turaGry = 1;

    connect(&player.czekaj,SIGNAL(clicked()),SLOT(czekajClicked()));
    connect(&player.obstaw,SIGNAL(clicked()),SLOT(obstawClicked()),Qt::DirectConnection);//liczyłem że directConnection zadziała jak ampersant w definicji funkcji
    connect(&player.pasuj,SIGNAL(clicked()),SLOT(pasujClicked()));
    connect(&player.sprawdz,SIGNAL(clicked()),SLOT(sprawdzClicked()));
    connect(&player.przebij,SIGNAL(clicked(bool)),SLOT(przebijClicked()));


    pierwszeRozdanie();
    pierwszaDecyzjaGracza(suwak,&player.obstaw,&player.pasuj,kasaGracza);
}

void MainWindow::pierwszeRozdanie()
{

    gracz1.setCard1(dajKarte(tali));
    gracz1.setCard2(dajKarte(tali));
    gracz2.setCard1(dajKarte(tali));
    gracz2.setCard2(dajKarte(tali));
    gracz3.setCard1(dajKarte(tali));
    gracz3.setCard2(dajKarte(tali));
    gracz4.setCard1(dajKarte(tali));
    gracz4.setCard2(dajKarte(tali));
    player.setCard1(dajKarte(tali));
    player.karta1Gracza.setText(player.getCard1Name());
    player.setCard2(dajKarte(tali));
    player.karta2Gracza.setText(player.getCard2Name());


}


void MainWindow::czekajClicked()
{
    dokonczTure();
}

void MainWindow::obstawClicked()
{
    int postawione = suwak->value();
    player.obstawFun(postawione);
    kasaPoPostawieniu->setNum(player.getIloscZetonow());
    krupier1.wPuli.setNum(krupier1.getIloscZetonow());
    dokonczTure();
}

void MainWindow::pasujClicked()
{
    player.wGrze = false;
    dokonczTure();
    dokonczTure();
    dokonczTure();
}

void MainWindow::sprawdzClicked()
{
    dokonczTure();
}

void MainWindow::przebijClicked()
{
    int postawione = suwak->value();
    player.obstawFun(postawione);
    kasaPoPostawieniu->setNum(player.getIloscZetonow());
    krupier1.wPuli.setNum(krupier1.getIloscZetonow());
    dokonczTure();

}


void MainWindow::rozdajKartyKrupierowi()
{
    if (turaGry == 1)
    {
        krupier1.setStol(dajKarte(tali));
        delay(600);
        krupier1.karta1Stol.setText(krupier1.getCardName());
        krupier1.setStol(dajKarte(tali));
        delay(600);
        krupier1.karta2Stol.setText(krupier1.getCardName());
        krupier1.setStol(dajKarte(tali));
        delay(600);
        krupier1.karta3Stol.setText(krupier1.getCardName());
    }
    else if(turaGry == 2)
    {
        delay(600);
        krupier1.setStol(dajKarte(tali));
        krupier1.karta4Stol.setText(krupier1.getCardName());

    }
    else if(turaGry = 3)
    {
        delay(600);
        krupier1.setStol(dajKarte(tali));
        krupier1.karta5Stol.setText(krupier1.getCardName());
    }
    else if(turaGry == 4)
    {
        wylonWygranego();
    }
}


void MainWindow::dokonczTure()
{
/* w pierwszej turze do wyboru przed rozdaniem kart krupierowi można spasować albo wejść do gry obstawiając
 * druga tura zaczekać lub zagrać(obstaw), trzy karty na stole
 * trzecia tura zaczekać lub zagrać(obstaw), cztery karty na stole
 * czwarta tura sprawdz przebij lub pasuj, pięć kart na stole

*/
    switch(turaGry)
    {
    case 1:
    {
        decyzjaSI();
        rozdajKartyKrupierowi();
        if (player.wGrze)
        {
            player.czekaj.setEnabled(true);
            player.czekaj.setFlat(false);
        }
        turaGry++;
        break;
    }
    case 2:
    {
        decyzjaSI();
        rozdajKartyKrupierowi();
        turaGry++;
        break;
    }
    case 3:
    {
        decyzjaSI();
        rozdajKartyKrupierowi();
        if (player.wGrze)
        {
        player.czekaj.setEnabled(false);
        player.czekaj.setFlat(true);
        player.obstaw.setEnabled(false);
        player.obstaw.setFlat(true);

        player.sprawdz.setEnabled(true);
        player.sprawdz.setFlat(false);
        player.przebij.setEnabled(true);
        player.przebij.setFlat(false);
        }
        turaGry++;
        break;
    }
    case 4:
    {
        decyzjaSI();
        przelejZetony(wylonWygranego(),krupier1);
        krupier1.wPuli.setNum(krupier1.getIloscZetonow());
        sprzatanie();
        start_gry();
    }

    }
}

void MainWindow::uruchomPrzyciski()
{
    player.czekaj.setEnabled(true);
    player.obstaw.setEnabled(true);
    player.pasuj.setEnabled(true);
    player.sprawdz.setEnabled(true);
    player.przebij.setEnabled(true);

    player.czekaj.setFlat(false);
    player.obstaw.setFlat(false);
    player.pasuj.setFlat(false);
    player.sprawdz.setFlat(false);
    player.przebij.setFlat(false);
}

void MainWindow::wylaczPrzyciski()
{
    player.czekaj.setEnabled(false);
    player.obstaw.setEnabled(false);
    player.pasuj.setEnabled(false);
    player.sprawdz.setEnabled(false);
    player.przebij.setEnabled(false);

    player.czekaj.setFlat(true);
    player.obstaw.setFlat(true);
    player.pasuj.setFlat(true);
    player.sprawdz.setFlat(true);
    player.przebij.setFlat(true);
}

void MainWindow::decyzjaSI()
{

    if(gracz1.wGrze) gracz1.podejmijDecyzje(turaGry);
    krupier1.wPuli.setNum(krupier1.getIloscZetonow());
    gracz1.kasaGracza.setNum(gracz1.getIloscZetonow());
    delay(800);
    if(gracz2.wGrze) gracz2.podejmijDecyzje(turaGry);
    krupier1.wPuli.setNum(krupier1.getIloscZetonow());
    gracz2.kasaGracza.setNum(gracz2.getIloscZetonow());
    delay(800);
    if(gracz3.wGrze) gracz3.podejmijDecyzje(turaGry);
    krupier1.wPuli.setNum(krupier1.getIloscZetonow());
    gracz3.kasaGracza.setNum(gracz3.getIloscZetonow());
    delay(800);
    if(gracz4.wGrze) gracz4.podejmijDecyzje(turaGry);
    krupier1.wPuli.setNum(krupier1.getIloscZetonow());
    gracz4.kasaGracza.setNum(gracz4.getIloscZetonow());
    delay(800);



}


void MainWindow::sprzatanie()
{
    wylaczPrzyciski();
    krupier1.karta1Stol.clear();
    krupier1.karta2Stol.clear();
    krupier1.karta3Stol.clear();
    krupier1.karta4Stol.clear();
    krupier1.karta5Stol.clear();
    krupier1.wyzerujZetony();
    player.wGrze = true;
    gracz1.wGrze = true;
    gracz2.wGrze = true;
    gracz3.wGrze = true;
    gracz4.wGrze = true;
    gracz1.karta1Gracza.clear();
    gracz1.karta2Gracza.clear();
    gracz2.karta1Gracza.clear();
    gracz2.karta2Gracza.clear();
    gracz3.karta1Gracza.clear();
    gracz4.karta2Gracza.clear();
    gracz1.decyzja.clear();
    gracz2.decyzja.clear();
    gracz3.decyzja.clear();
    gracz4.decyzja.clear();
    player.karta1Gracza.clear();
    player.karta2Gracza.clear();
    disconnect(&player.pasuj,0,0,0);


}

Gracz MainWindow::wylonWygranego()
{
    int wygrany = qrand() %5;
    switch(wygrany)
    {
    case 0:
    {
       //if(player.wGrze)
       {
           QDialog *oknoo = new QDialog;
           QLabel *tekstLabel  = new QLabel;
           QString tekst= QString("wygrał %1").arg(player.getName());
           tekstLabel->setText(tekst);
           QGridLayout *Lay = new QGridLayout;
           Lay->addWidget(tekstLabel);
           oknoo->setLayout(Lay);
           oknoo->show();
           return player;
       }
       //else wylonWygranego();
       break;
    }
    case 1:
    {
       //if(gracz1.wGrze)
       {
           QDialog *oknoo = new QDialog;
           QLabel *tekstLabel  = new QLabel;
           QString tekst= QString("wygrał %1").arg(gracz1.getName());
           tekstLabel->setText(tekst);
           QGridLayout *Lay = new QGridLayout;
           Lay->addWidget(tekstLabel);
           oknoo->setLayout(Lay);
           oknoo->show();
           return gracz1;
       }
       //else wylonWygranego();
       break;
    }
    case 2:
    {
       //if(gracz2.wGrze)
       {
           QDialog *oknoo = new QDialog;
           QLabel *tekstLabel  = new QLabel;
           QString tekst= QString("wygrał %1").arg(gracz2.getName());
           tekstLabel->setText(tekst);
           QGridLayout *Lay = new QGridLayout;
           Lay->addWidget(tekstLabel);
           oknoo->setLayout(Lay);
           oknoo->show();
           return gracz2;
       }
       //else wylonWygranego();
       break;
    }
    case 3:
    {
       //if(gracz3.wGrze)
       {
           QDialog *oknoo = new QDialog;
           QLabel *tekstLabel  = new QLabel;
           QString tekst= QString("wygrał %1").arg(gracz3.getName());
           tekstLabel->setText(tekst);
           QGridLayout *Lay = new QGridLayout;
           Lay->addWidget(tekstLabel);
           oknoo->setLayout(Lay);
           oknoo->show();
           return gracz3;
       }
       //else wylonWygranego();
       break;
    }
    case 4:
    {
       //if(gracz4.wGrze)
       {
           QDialog *oknoo = new QDialog;
           QLabel *tekstLabel  = new QLabel;
           QString tekst= QString("wygrał %1").arg(gracz4.getName());
           tekstLabel->setText(tekst);
           QGridLayout *Lay = new QGridLayout;
           Lay->addWidget(tekstLabel);
           oknoo->setLayout(Lay);
           oknoo->show();
           return gracz4;
        }
       //else wylonWygranego();
       break;
    }
    }

}

