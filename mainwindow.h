#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "node.h"

#include <QMainWindow>

using namespace std;

/**
  * \file mainwindow.h
  * \brief glowne okno programu
  */

namespace Ui {
class MainWindow;
}

/**
 * @brief Glowne okno
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

private slots:
    void on_pb_initialization_clicked();
    void on_pb_nextMove_clicked();
    void on_pb_wybierzPlik_clicked();
    void on_pb_wybierzDane_clicked();
    void on_pb_losuj_clicked();
    void on_pb_zapiszDoPliku_clicked();

private:
    QString intToQstring (int cipher);
    int QStringToInt (QString text);
    QString stringToQString (string text);
    void dataCheck ();
    void initialMatrixToLineEdits();

    Node* start;                ///<glowa listy z rozwiazaniem
    Node* current;              ///<aktualnie wyswietlany element
    int initialMatrix[3][3];    ///<tablica na dane wejsciowe
    bool firstDraw;             ///<czy to pierwsze losowanie
    QTimer *timer;
};



#endif // MAINWINDOW_H
