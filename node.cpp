#include "node.h"

#include <cmath>
#include <iostream>

Node::Node(int matrix[][3], Node *parent)
{
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            matrix_[i][j] = matrix[i][j];
    calculateId();
    predictDistanceLeft();

    this->parent = parent;
    traveledDistance_ = parent->traveledDistance_ + 1;
    fullDistance_ = traveledDistance_ + predictedDistanceLeft_;
}

Node::Node(int matrix[][])
{
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            matrix_[i][j] = matrix[i][j];
    calculateId();
    predictDistanceLeft();

    parent = nullptr;
    traveledDistance_ = 0;
    fullDistance_ = predictedDistanceLeft_;
}

Point Node::findEmptySpace()
{
    for (int y=0; y<3; y++)
        for (int x=0; x<3; x++)
            if (matrix_[y][x] == 9)
                return Point{x,y};
    throw "should never reach this point";
}

//tworzy nowa tablice w ktorej na miejsce luki (9) wchodzi plytka obok
Node Node::clone(Point luka, int obok_y, int obok_x, Node* parent)
{
    int newOne[3][3];
    for (int y=0; y<3; y++)
        for (int x=0; x<3; x++)
            newOne[y][x] = matrix_[y][x];
    std::swap(newOne[luka.y][luka.x], newOne[obok_y][obok_x]);
    return Node(newOne, parent);
}

//pierwszy constant jest potrzebny zeby typy sie zgadzaly. Matrix_ wydaje sie byc const
//drugi wystepuje w kazdej metodzie get. Chyba odpowiada za to aby nie mozna bylo zmienic wartosci prywatnego pola
const int *Node::getMatrix() const
{
    return &matrix_[0][0];
}

int Node::getId() const
{
    return id_;
}

int Node::getTraveledDistance() const
{
    return traveledDistance_;
}

int Node::getFullDistance() const
{
    return fullDistance_;
}

void Node::calculateId()
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

void Node::predictDistanceLeft()
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
