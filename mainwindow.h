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
    void on_pushButton_clicked();

//private:

};



#endif // MAINWINDOW_H
