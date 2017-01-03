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
#include "moj_poker.h"
#include "moj_poker.cpp"


#define smallBid 10
#define bigBid 20

void delay(int czasWSekundach)
{
    QTime dieTime= QTime::currentTime().addSecs(czasWSekundach);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("Opuść Grę");
    ui->rozpocznij_gre->setText("Nowa Gra");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ok_clicked()
{

    gracz gracz1("KOMPUTER1");
    gracz gracz2("KOMPUTER2");
    gracz gracz3("KOMPUTER3");
    gracz gracz4("KOMPUTER4");
    //talia tali;
    tasuj(tali);
    //krupier krupier;
    //gracz player(imiewsk->text(),false); //nie działa, sloty szaleją konstruktor przeniesiony do mainwindow.h
    wskPlayer = &player;
    wskKrupier = &krupier1;
    wskTalia = &tali;


    start_okna(gracz1,gracz2,gracz3,gracz4,tali,krupier1,player);
    start_gry(gracz1,gracz2,gracz3,gracz4,tali,krupier1,player);


}

void MainWindow::on_rozpocznij_gre_clicked()
{
    QWidget *opcje_uruchamiania = new QWidget;
    opcje_uruchamiania->setWindowTitle("rozpocznij gre");
    QGridLayout *ustawienie_elementow = new QGridLayout;

    QPushButton *ok = new QPushButton("ZACZYNAJMY!",this);
    QPushButton *cancel = new QPushButton("ANULUJ",this);
    QLineEdit *imie = new QLineEdit;
    QLabel *imieLabel = new QLabel("podaj imie:");
    imie->setText("Imie");
    imiewsk = imie;

    ustawienie_elementow->addWidget(ok,1,0);
    ustawienie_elementow->addWidget(cancel,1,1);
    ustawienie_elementow->addWidget(imie,0,1);
    ustawienie_elementow->addWidget(imieLabel,0,0);


    ustawienie_elementow->setColumnStretch(0,20);
    ustawienie_elementow->setColumnStretch(1,20);

    connect(cancel,SIGNAL(clicked()),opcje_uruchamiania,SLOT(close()));

    connect(ok,SIGNAL(clicked()),SLOT(on_ok_clicked()));
    connect(ok,SIGNAL(clicked()),opcje_uruchamiania,SLOT(close()));



    opcje_uruchamiania->setLayout(ustawienie_elementow);
    opcje_uruchamiania->show();

}

void MainWindow::czekajClicked()
{

}

void MainWindow::obstawClicked()
{
    int postawione = suwak->value();
    wskPlayer->obstaw(postawione);//nie rusz tej linijki bo QT mądrzejsze
    wPuli->setNum(wskKrupier->getIloscZetonow());
    kasaPoPostawieniu->setNum(wskPlayer->getIloscZetonow());
    rozdaj3KartyKrupierowi(*wskKrupier,*wskTalia);

}

void MainWindow::pasujClicked()
{
    QDialog *oknoo = new QDialog;
    QLabel *tekst  = new QLabel;
    tekst->setNum(wskPlayer->getIloscZetonow());
    QGridLayout *Lay = new QGridLayout;
    Lay->addWidget(tekst);
    oknoo->setLayout(Lay);
    oknoo->show();

}

void MainWindow::sprawdzClicked()
{

}

void MainWindow::przebijClicked()
{

}


void MainWindow::rozdaj3KartyKrupierowi(krupier _krupier, talia _tal)
{
    _krupier.setStol(dajKarte(_tal));
    delay(1);
    karta1Stol->setText(_krupier.getCardName());
    _krupier.setStol(dajKarte(_tal));
    delay(1);
    karta2Stol->setText(_krupier.getCardName());
    _krupier.setStol(dajKarte(_tal));
    delay(1);
    karta3Stol->setText(_krupier.getCardName());
}

void MainWindow::start_okna(gracz &gracz1, gracz &gracz2, gracz &gracz3, gracz &gracz4, talia talia, krupier &krupier,gracz &player)
{

    QWidget *okno_gry = new QWidget;
    QGridLayout *lay = new QGridLayout;

    QHBoxLayout *graczeLayout = new QHBoxLayout;
    QVBoxLayout *gracz1Lay = new QVBoxLayout;
    QVBoxLayout *gracz2Lay = new QVBoxLayout;
    QVBoxLayout *gracz3Lay = new QVBoxLayout;
    QVBoxLayout *gracz4Lay = new QVBoxLayout;

    QLabel *imieGracza1 = new QLabel(gracz1.getName());
    imieGracza1->setAlignment(Qt::AlignHCenter);
    QLabel *imieGracza2 = new QLabel(gracz2.getName());
    imieGracza2->setAlignment(Qt::AlignHCenter);
    QLabel *imieGracza3 = new QLabel(gracz3.getName());
    imieGracza3->setAlignment(Qt::AlignHCenter);
    QLabel *imieGracza4 = new QLabel(gracz4.getName());
    imieGracza4->setAlignment(Qt::AlignHCenter);

    kasaGracza1 = new QLabel(QString::number(gracz1.getIloscZetonow()));
    kasaGracza1->setAlignment(Qt::AlignHCenter);
    kasaGracza2 = new QLabel(QString::number(gracz2.getIloscZetonow()));
    kasaGracza2->setAlignment(Qt::AlignHCenter);
    kasaGracza3 = new QLabel(QString::number(gracz3.getIloscZetonow()));
    kasaGracza3->setAlignment(Qt::AlignHCenter);
    kasaGracza4 = new QLabel(QString::number(gracz4.getIloscZetonow()));
    kasaGracza4->setAlignment(Qt::AlignHCenter);


    karta1Gracza1 = new QLabel(gracz1.getCard1Name());
    karta2Gracza1 = new QLabel(gracz1.getCard2Name());
    karta1Gracza2 = new QLabel(gracz2.getCard1Name());
    karta2Gracza2 = new QLabel(gracz2.getCard2Name());
    karta1Gracza3 = new QLabel(gracz3.getCard1Name());
    karta2Gracza3 = new QLabel(gracz3.getCard2Name());
    karta1Gracza4 = new QLabel(gracz4.getCard1Name());
    karta2Gracza4 = new QLabel(gracz4.getCard2Name());

    QHBoxLayout *kartyGracza1 = new QHBoxLayout;
    QHBoxLayout *kartyGracza2 = new QHBoxLayout;
    QHBoxLayout *kartyGracza3 = new QHBoxLayout;
    QHBoxLayout *kartyGracza4 = new QHBoxLayout;

    kartyGracza1->addWidget(karta1Gracza1);
    kartyGracza1->addWidget(karta2Gracza1);
    kartyGracza2->addWidget(karta1Gracza2);
    kartyGracza2->addWidget(karta2Gracza2);
    kartyGracza3->addWidget(karta1Gracza3);
    kartyGracza3->addWidget(karta2Gracza3);
    kartyGracza4->addWidget(karta1Gracza4);
    kartyGracza4->addWidget(karta2Gracza4);

    gracz1Lay->addWidget(imieGracza1);
    gracz1Lay->addWidget(kasaGracza1);
    gracz1Lay->addLayout(kartyGracza1);
    gracz1Lay->setAlignment(Qt::AlignHCenter);



    gracz2Lay->addWidget(imieGracza2);
    gracz2Lay->addWidget(kasaGracza2);
    gracz2Lay->addLayout(kartyGracza2);
    gracz2Lay->setAlignment(Qt::AlignHCenter);

    gracz3Lay->addWidget(imieGracza3);
    gracz3Lay->addWidget(kasaGracza3);
    gracz3Lay->addLayout(kartyGracza3);
    gracz3Lay->setAlignment(Qt::AlignHCenter);

    gracz4Lay->addWidget(imieGracza4);
    gracz4Lay->addWidget(kasaGracza4);
    gracz4Lay->addLayout(kartyGracza4);
    gracz4Lay->setAlignment(Qt::AlignHCenter);


    graczeLayout->addLayout(gracz1Lay);
    graczeLayout->addLayout(gracz2Lay);
    graczeLayout->addLayout(gracz3Lay);
    graczeLayout->addLayout(gracz4Lay);
    graczeLayout->setAlignment(Qt::AlignHCenter);




    QGroupBox *gracze = new QGroupBox("GRACZE");
    gracze->adjustSize();
    gracze->setLayout(graczeLayout);

    //tworzenie okna krupiera
    QVBoxLayout *krupierLay = new QVBoxLayout;
    QLabel *wPuliLabel = new QLabel("w puli");
    wPuli = new QLabel(QString::number(krupier.getIloscZetonow()));
    QLabel *wygrywajacyLabel = new QLabel;
    wygrywajacy = new QLabel;

    QHBoxLayout *kartyNaStole = new QHBoxLayout;
    karta1Stol = new QLabel;
    karta2Stol = new QLabel;
    karta3Stol = new QLabel;
    karta4Stol = new QLabel;
    karta5Stol = new QLabel;

    kartyNaStole->addWidget(karta1Stol);
    kartyNaStole->addWidget(karta2Stol);
    kartyNaStole->addWidget(karta3Stol);
    kartyNaStole->addWidget(karta4Stol);
    kartyNaStole->addWidget(karta5Stol);


    krupierLay->addLayout(kartyNaStole);



    krupierLay->addWidget(wPuliLabel);
    krupierLay->addWidget(wPuli);
    krupierLay->addWidget(wygrywajacyLabel);
    krupierLay->addWidget(wygrywajacy);

    QHBoxLayout *graczLayout = new QHBoxLayout;

    czekaj = new QPushButton("CZEKAJ");
    czekaj->setFlat(1);
    czekaj->setDisabled(1);
    obstaw = new QPushButton();
    obstaw->setText("OBSTAW");
    obstaw->setFlat(1);
    obstaw->setDisabled(1);
    pasuj = new QPushButton("PASUJ");
    pasuj->setFlat(1);
    pasuj->setDisabled(1);
    sprawdz = new QPushButton("SPRAWDZ");
    sprawdz->setFlat(1);
    sprawdz->setDisabled(1);
    przebij = new QPushButton("PRZEBIJ");
    przebij->setFlat(1);
    przebij->setDisabled(1);
    QLabel *kasaDoPostawienia = new QLabel("0");
    kasaGracza = new QLabel(QString::number(player.getIloscZetonow()));
    kasaPoPostawieniu = new QLabel(QString::number((wskPlayer->getIloscZetonow())));
    QLabel *otworzNawias = new QLabel("(");
    QLabel *zamknijNawias = new QLabel(")");
    
    karta1Gracza = new QLabel;
    karta2Gracza = new QLabel;
    QHBoxLayout *kartyLay = new QHBoxLayout;
    QSpacerItem *leftSpacer = new QSpacerItem(100,2,QSizePolicy::Expanding,QSizePolicy::Maximum);
    QSpacerItem *rightSpacer = new QSpacerItem(100,2,QSizePolicy::Expanding,QSizePolicy::Maximum);
    QSpacerItem *centerSpacer = new QSpacerItem(100,1);


    kartyLay->addSpacerItem(leftSpacer);
    kartyLay->addWidget(karta1Gracza,0,Qt::AlignHCenter);
    kartyLay->addSpacerItem(centerSpacer);
    kartyLay->addWidget(karta2Gracza,0,Qt::AlignHCenter);
    kartyLay->addSpacerItem(rightSpacer);
    
    
    suwak = new QSlider;
    QSpacerItem *gornaPrzestrzen = new QSpacerItem(1,200,QSizePolicy::Minimum,QSizePolicy::Ignored);
    QSpacerItem *dolnaPrzestrzen = new QSpacerItem(1,27);
    suwak->setMinimumHeight(200);
    suwak->setMaximumHeight(250);
    
    

    //suwak->setRange(0,player.getIloscZetonow());
    connect(suwak,SIGNAL(valueChanged(int)),kasaDoPostawienia,SLOT(setNum(int)));




    graczLayout ->addWidget(czekaj);
    graczLayout ->addWidget(obstaw);
    graczLayout ->addWidget(pasuj);
    graczLayout ->addWidget(sprawdz);
    graczLayout ->addWidget(przebij);

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

void pierwsze_rozdanie(gracz &gracz1, gracz &gracz2, gracz &gracz3, gracz &gracz4, talia &tal,gracz &player)
{

    gracz1.setCard1(dajKarte(tal));
    gracz1.setCard2(dajKarte(tal));
    gracz2.setCard1(dajKarte(tal));
    gracz2.setCard2(dajKarte(tal));
    gracz3.setCard1(dajKarte(tal));
    gracz3.setCard2(dajKarte(tal));
    gracz4.setCard1(dajKarte(tal));
    gracz4.setCard2(dajKarte(tal));
    player.setCard1(dajKarte(tal));
    player.setCard2(dajKarte(tal));


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


void MainWindow::start_gry(gracz &gracz1, gracz &gracz2, gracz &gracz3, gracz &gracz4, talia &tal, krupier &_krupier,gracz &player)
{

    connect(czekaj,SIGNAL(clicked()),SLOT(czekajClicked()));
    connect(obstaw,SIGNAL(clicked()),SLOT(obstawClicked()),Qt::DirectConnection);
    connect(pasuj,SIGNAL(clicked()),SLOT(pasujClicked()));
    connect(sprawdz,SIGNAL(clicked()),SLOT(sprawdzClicked()));
    connect(przebij,SIGNAL(clicked(bool)),SLOT(przebijClicked()));
//krupier.setStol(dajKarte(tal));karta1Stol->setText(krupier.getCardName());






//    connect(obstaw,SIGNAL(clicked()),wPuli,SLOT(setNum(krupier.getIloscZetonow())));

    pierwsze_rozdanie(gracz1,gracz2,gracz3, gracz4, tal, player);

    karta1Gracza->setText(player.getCard1Name());
    karta2Gracza->setText(player.getCard2Name());

    pierwszaDecyzjaGracza(suwak,obstaw,pasuj,kasaGracza);


}


