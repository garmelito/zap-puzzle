#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"

#include <QTimer>
#include <stdlib.h>

using namespace std;

//moge pozostawiona we wpisywaniu pusta plytke spacje zminiac na 9

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    //ui->pb_nextMove->setEnabled(true);    //najchetneiej pozbylbym sie tego przycisku

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pb_nextMove_clicked()));
    timer->start(400);
}

//Nie umiem sie go pozbyc. Timer chce wywolywac slot
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
        cout <<endl;
        repaint();
        current = current->next;
    }
}

void MainWindow::on_pb_wybierzPlik_clicked()
{
    ui->tb_komunikaty->clear();
    bool succes = readFromFile (ui->le_nazwaPliku->text().toStdString(), initialMatrix);
    if (!succes)
        ui->tb_komunikaty->setText(stringToQString("Nie znalazlem pliku \n"));
    else
        dataCheck();

    //on_pb_nextMove_clicked();
    //musze czesc wypisujaca przerzucic do nowej funkcji. Ale problemem jest zmiana tablicy[3][3] na [9]
}

void MainWindow::on_pb_wybierzDane_clicked()
{
    ui->tb_komunikaty->clear();

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
        ui->tb_komunikaty->setText(stringToQString("Bledne dane. Wpisz inne \n"));
    else if (!(solutionIsPosible(initialMatrix)))
        ui->tb_komunikaty->setText(stringToQString("Brak rozwiazania. Wpisz inne liczby \n"));
    else
        ui->tb_komunikaty->setText(stringToQString("Dane sa w porzadku \n"));
}
