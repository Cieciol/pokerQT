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
//#include "nadpisane_obiekty_qt.h"

//tltlt

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QLineEdit* imiewsk;
    QLabel* kasaGracza1;
    QLabel* kasaGracza2;
    QLabel* kasaGracza3;
    QLabel* kasaGracza4;

    QLabel* karta1Gracza1;
    QLabel* karta2Gracza1;
    QLabel* karta1Gracza2;
    QLabel* karta2Gracza2;
    QLabel* karta1Gracza3;
    QLabel* karta2Gracza3;
    QLabel* karta1Gracza4;
    QLabel* karta2Gracza4;

    QLabel* wPuli;
    QLabel* wygrywajacy;
    QLabel *karta1Stol;
    QLabel *karta2Stol;
    QLabel *karta3Stol;
    QLabel *karta4Stol;
    QLabel *karta5Stol;

    QPushButton *czekaj;
    QPushButton *obstaw;
    QPushButton *pasuj;
    QPushButton *sprawdz;
    QPushButton *przebij;
    QLabel *kasaGracza;
    QLabel *karta1Gracza;
    QLabel *karta2Gracza;
    QSlider *suwak;

    gracz *wskPlayer;
    krupier *wskKrupier;



    ~MainWindow();


private slots:

    void on_rozpocznij_gre_clicked();
    void on_ok_clicked();
    void obstawClicked();


private:
    Ui::MainWindow *ui;
    void start_gry(gracz &, gracz &, gracz &,gracz &, talia &, krupier &,gracz & );
    void start_okna(gracz &, gracz &, gracz &,gracz &, talia, krupier &,gracz &);
    //void pierwsze_rozdanie(gracz &, gracz &, gracz &,gracz &, talia &,gracz &);
};

#endif // MAINWINDOW_H
