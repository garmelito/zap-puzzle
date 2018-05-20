#include "mainwindow.h"
#include "ui_mainwindow.h"

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
//    Node *current = start;
//    int cyfra = current->board.matrix_[0][0];
//    stringstream strumien;
//    strumien << cyfra;
//    string tekst = strumien.str();
//    QString tekst_qt = tekst.c_str();
//    ui->label_1->setText(tekst_qt);
    int tablica[3][3];
    tablica = start->board.getMatrix();
    // extermination(start);
}
