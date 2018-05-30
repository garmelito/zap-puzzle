#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "node.h"

#include <QMainWindow>

using namespace std;

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
    void on_pb_losuj_clicked();

    void on_pb_zapiszDoPliku_clicked();

private:
    QString intToQstring (int cipher);
    int QStringToInt (QString text);
    QString stringToQString (string text);
    void dataCheck ();

    Node* start;
    Node* current;
    int initialMatrix[3][3];
    bool firstDraw;
};



#endif // MAINWINDOW_H
