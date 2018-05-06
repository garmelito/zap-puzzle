#include "board.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <cmath>

using namespace std;

Board::Board(int matrix[][3])
{
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            matrix_[i][j] = matrix[i][j];
    calculateId();
    predictDistanceLeft();
}

//tworzy nowa tablice w ktorej na miejsce luki (9) wchodzi plytka obok
Board Board::clone(Point luka, int obok_y, int obok_x)
{
    int newSlab[3][3];
    for (int y=0; y<3; y++)
        for (int x=0; x<3; x++)
            newSlab[y][x] = matrix_[y][x];
    std::swap(newSlab[luka.y][luka.x], newSlab[obok_y][obok_x]);
    return Board(newSlab);
}

Point Board::findEmptySpace()
{
    for (int y=0; y<3; y++)
        for (int x=0; x<3; x++)
            if (matrix_[y][x] == 9)
                return Point{x,y};
    throw "should never reach this point";
}

void Board::print()
{
//    ui->label_1->setText(matrix_[0][0]);
//    ui->label_2->setText(matrix_[0][1]);
//    ui->label_3->setText(matrix_[0][2]);
//    ui->label_4->setText(matrix_[1][0]);
//    ui->label_5->setText(matrix_[1][1]);
//    ui->label_6->setText(matrix_[1][2]);
//    ui->label_7->setText(matrix_[2][0]);
//    ui->label_8->setText(matrix_[2][1]);
//    ui->label_9->setText(matrix_[2][2]);
}

int Board::getId() const
{
    return id_;
}

int Board::getPredictedDistance() const
{
    return predictedDistanceLeft_;
}

void Board::calculateId()
{
    int suma = 0;
    int waga = 100000000;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
        {
            suma += matrix_[i][j] * waga;
            waga /= 10;
        }
    id_ = suma;
}

void Board::predictDistanceLeft()
{
    int h = 0;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
        {
            //sumuje odleglosc kazdego elementu od swojego polozenia
            int m = (matrix_[i][j]-1)/3;  //wspolrzedna y wlasciwego polozenia
            int n = (matrix_[i][j]%3)-1;  //wspolrzedna x wlasciwego polozenia
            if (n<0)    n += 3;
            h += abs(m-i) + abs(n-j);   //odleglosc aktualnego polozenia od wlasciwego
        }
    predictedDistanceLeft_ = h;
}
