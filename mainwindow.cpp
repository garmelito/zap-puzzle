#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

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
    ui->pb_initialization->setEnabled(false);
    ui->pb_skipOne->setEnabled(true);
    ui->pb_nextMove->setEnabled(true);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pb_nextMove_clicked()));
    timer->start(400);
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
    if (current != nullptr)
        current = current->next;
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
        cout <<endl;
        repaint();
        current = current->next;
    }
}
