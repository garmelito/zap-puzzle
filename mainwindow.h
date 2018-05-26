#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "algorithm.h"

#include <QMainWindow>
#include <windows.h>
#include <iostream>
#include <sstream>

namespace Ui {
class MainWindow;
}

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

private:
    QString intToQstring (int cipher);
    int QStringToInt (QString text_qt);
    QString stringToQString (string text);

    Node* start;    //chyba nie potrzebuje kopii, na razie przechowuje na wszelki wypadek
    Node* current;
    int initialMatrix[3][3];
};



#endif // MAINWINDOW_H
