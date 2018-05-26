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

    void on_pb_skipOne_pressed();

    void on_pb_nextMove_clicked();

private:
    QString intToQstring (int cipher);
    Node* start;
    Node* current;
};



#endif // MAINWINDOW_H
