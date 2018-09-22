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

/**
 * @brief uruchamia algorytm, wlacza timer ktory zajmie sie wyswietleniem rozwiazania
 */
void MainWindow::on_pb_initialization_clicked()
{
    Board initialBoard(initialMatrix);
    start = algorithm(initialBoard);
    current = start;

    ui->pb_initialization->setEnabled(false);
    ui->pb_zapiszDoPliku->setEnabled(true);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pb_nextMove_clicked()));
    timer->start(400);
}

/**
 * @brief wyswietla nastepne ulozenie rozwiazania
 *
 * Wywolywany przez timer
 * @bug przycisk nie istnieje. Nie jest potrzebny. Jednak timer musi wywolywac slot
 */
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
    else
        timer->stop();
}

/**
 * @brief wczytuje plik
 */
void MainWindow::on_pb_wybierzPlik_clicked()
{
    bool succes = readFromFile (ui->le_nazwaPliku->text().toStdString(), initialMatrix);

    initialMatrixToLineEdits();

    if (!succes)
    {
        ui->tb_komunikaty->setText(stringToQString("Nie znalazlem pliku \n"));
        ui->pb_initialization->setEnabled(false);
    }
    else
        dataCheck();
}

/**
 * @brief wczytuje dane z okna
 */
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

/**
 * @brief Losuje dane
 *
 * Do skutku. Do znalezienia wlasciwych
 * @warning za pierwszym razem wywoluje srand(time(NULL));
 */
void MainWindow::on_pb_losuj_clicked()
{
    if (firstDraw)
    {
        srand(time(NULL));
        firstDraw = false;
    }

    int table[9] = {0};
    do{
        draw (table);
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                initialMatrix[i][j] = table[i*3+j];
    }while (!solutionIsPosible(initialMatrix));

    initialMatrixToLineEdits();

    ui->pb_initialization->setEnabled(true);
}

/**
 * @brief Zapisuje dane do pliku
 *
 * Pozwala zapisac rozwiazanie do kilku roznych plikow, w ktorymkolwiek momencie po uruchomieniu algorytmu
 */
void MainWindow::on_pb_zapiszDoPliku_clicked()
{
    if (ui->le_nazwaPlikuOut->text() != "")
    {
        ofstream zapis(ui->le_nazwaPlikuOut->text().toStdString());
        Node* operating = start;
        while (operating != nullptr)
        {
            auto tablica = operating->board.getMatrix();
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

            operating = operating->next;
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

/**
 * @brief sprawwdza dane.
 *
 * Wypisuje komunikaty w oknie. Nie trzeba go czyscig bo nie dopisuje a zamienia tekst
 */
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

void MainWindow::initialMatrixToLineEdits()
{
    ui->lineEdit->setText(intToQstring(initialMatrix[0][0]));
    ui->lineEdit_2->setText(intToQstring(initialMatrix[0][1]));
    ui->lineEdit_3->setText(intToQstring(initialMatrix[0][2]));
    ui->lineEdit_4->setText(intToQstring(initialMatrix[1][0]));
    ui->lineEdit_5->setText(intToQstring(initialMatrix[1][1]));
    ui->lineEdit_6->setText(intToQstring(initialMatrix[1][2]));
    ui->lineEdit_7->setText(intToQstring(initialMatrix[2][0]));
    ui->lineEdit_8->setText(intToQstring(initialMatrix[2][1]));
    ui->lineEdit_9->setText(intToQstring(initialMatrix[2][2]));
    repaint();
}
