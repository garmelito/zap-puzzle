#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "algorithm.h"
#include "board.h"
#include "engine.h"

#include <fstream>
#include <QTimer>
#include <sstream>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    firstDraw = true;
}

MainWindow::~MainWindow()
{
    extermination(start);
    delete start;
    delete current;
    delete ui;
}

void MainWindow::on_pb_initialization_clicked()
{
    Board initialBoard(initialMatrix);
    start = algorithm(initialBoard);
    current = start;

    ui->pb_initialization->setEnabled(false);
    ui->pb_zapiszDoPliku->setEnabled(true);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pb_nextMove_clicked()));
    timer->start(400);
}

void MainWindow::on_pb_nextMove_clicked()
{
    if (current != nullptr)
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
        repaint();
        current = current->next;
    }
}

void MainWindow::on_pb_wybierzPlik_clicked()
{
    bool succes = readFromFile (ui->le_nazwaPliku->text().toStdString(), initialMatrix);
    if (!succes)
    {
        ui->tb_komunikaty->setText(stringToQString("Nie znalazlem pliku \n"));
        ui->pb_initialization->setEnabled(false);
    }
    else
        dataCheck();
}

void MainWindow::on_pb_wybierzDane_clicked()
{
    initialMatrix[0][0] = QStringToInt(ui->lineEdit->text());
    initialMatrix[0][1] = QStringToInt(ui->lineEdit_2->text());
    initialMatrix[0][2] = QStringToInt(ui->lineEdit_3->text());
    initialMatrix[1][0] = QStringToInt(ui->lineEdit_4->text());
    initialMatrix[1][1] = QStringToInt(ui->lineEdit_5->text());
    initialMatrix[1][2] = QStringToInt(ui->lineEdit_6->text());
    initialMatrix[2][0] = QStringToInt(ui->lineEdit_7->text());
    initialMatrix[2][1] = QStringToInt(ui->lineEdit_8->text());
    initialMatrix[2][2] = QStringToInt(ui->lineEdit_9->text());

    dataCheck();
}

void MainWindow::on_pb_losuj_clicked()
{
    int table[9] ={0};
    draw (table, firstDraw);
    if (firstDraw)
        firstDraw = false;

    ui->lineEdit->setText(intToQstring(table[0]));
    ui->lineEdit_2->setText(intToQstring(table[1]));
    ui->lineEdit_3->setText(intToQstring(table[2]));
    ui->lineEdit_4->setText(intToQstring(table[3]));
    ui->lineEdit_5->setText(intToQstring(table[4]));
    ui->lineEdit_6->setText(intToQstring(table[5]));
    ui->lineEdit_7->setText(intToQstring(table[6]));
    ui->lineEdit_8->setText(intToQstring(table[7]));
    ui->lineEdit_9->setText(intToQstring(table[8]));
    repaint();

    on_pb_wybierzDane_clicked();
}
void MainWindow::on_pb_zapiszDoPliku_clicked()
{
    if (ui->le_nazwaPlikuOut->text() != "")
    {
        ofstream zapis(ui->le_nazwaPlikuOut->text().toStdString());
        while (start != nullptr)
        {
            auto tablica = start->board.getMatrix();
            for (int i=0; i<3; i++)
            {
                for (int j=0; j<3; j++)
                {
                    if (tablica[i*3+j] != 9)
                        zapis << tablica[i*3+j] <<" ";
                    else
                        zapis <<"  ";
                }
                zapis <<endl;
            }
            zapis <<endl;

            start = start->next;
        }
        zapis.close();
        ui->tb_komunikaty->setText(stringToQString("Powodzenie \n"));
    }
    else
        ui->tb_komunikaty->setText(stringToQString("Wpisz nazwe piku \n"));
}

QString MainWindow::intToQstring(int cipher)
{
    stringstream stream;
    if (cipher != 9)    stream << cipher;
    else                stream << ' ';
    string text = stream.str();
    return text.c_str();
}

int MainWindow::QStringToInt(QString text)
{
    if (text == "" || text == " ")
        return 9;
    else
        return stoi(text.toStdString());
}

QString MainWindow::stringToQString(string text)
{
    return text.c_str();
}

void MainWindow::dataCheck()
{
    if (!inRules(initialMatrix))
    {
        ui->tb_komunikaty->setText(stringToQString("Bledne dane. Wpisz inne \n"));
        ui->pb_initialization->setEnabled(false);
    }
    else if (!(solutionIsPosible(initialMatrix)))
    {
        ui->tb_komunikaty->setText(stringToQString("Brak rozwiazania. Wpisz inne liczby \n"));
        ui->pb_initialization->setEnabled(false);
    }
    else
    {
        ui->tb_komunikaty->setText(stringToQString("Dane sa w porzadku \n"));
        ui->pb_initialization->setEnabled(true);
    }
}
