#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    extermination(start);
    delete ui;
}

void MainWindow::on_pb_initialization_clicked()
{
    start = algorithm();
    current = start;
    ui->pb_skipOne->setEnabled(true);
    while (current != nullptr)
    {
        auto tablica = current->board.getMatrix();
        ui->label_1->setText(intToQstring(tablica[0]));
        ui->label_2->setText(intToQstring(tablica[1]));
        ui->label_3->setText(intToQstring(tablica[2]));
        ui->label_4->setText(intToQstring(tablica[3]));
        ui->label_5->setText(intToQstring(tablica[4]));
        ui->label_6->setText(intToQstring(tablica[5]));
        ui->label_7->setText(intToQstring(tablica[6]));
        ui->label_8->setText(intToQstring(tablica[7]));
        ui->label_9->setText(intToQstring(tablica[8]));
        cout <<endl;
        repaint();
        Sleep(300);
        current = current->next;
    }
}

QString MainWindow::intToQstring(int cipher)
{
    stringstream stream;
    if (cipher != 9)    stream << cipher;
    else                stream << ' ';
    string text = stream.str();
    QString text_qt = text.c_str();
    return text_qt;
}

void MainWindow::on_pb_skipOne_pressed()
{
    current = current->next;
}
