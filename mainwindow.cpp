#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithm.h"

#include <windows.h>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Node *start = algorithm();
    Node *current = start;
    while (current != nullptr)
    {
        int cyfra = current->board.matrix_[0][0];
        stringstream strumien;
        strumien << cyfra;
        string tekst = strumien.str();
        QString tekst_qt = tekst.c_str();
        ui->label_1->setText(tekst_qt);
//        ui->label_2->setText(current->board.matrix_[0][1]);
//        ui->label_3->setText(current->board.matrix_[0][2]);
//        ui->label_4->setText(current->board.matrix_[1][0]);
//        ui->label_5->setText(current->board.matrix_[1][1]);
//        ui->label_6->setText(current->board.matrix_[1][2]);
//        ui->label_7->setText(current->board.matrix_[2][0]);
//        ui->label_8->setText(current->board.matrix_[2][1]);
//        ui->label_9->setText(current->board.matrix_[2][2]);
        Sleep(480);
        current = current->next;
    }
    //extermination(start);
}
