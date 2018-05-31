#ifndef NODE_H
#define NODE_H

#include "point.h"

/**
 * @brief Element listy
 */
class Node
{
public:
    Node(int matrix[][3], Node *parent);
    Node(int matrix[][3]);

    Point findEmptySpace();
    Node clone(Point luka, int obok_y, int obok_x, Node *parent);

    const int *getMatrix() const;
    int getId() const;
    int getTraveledDistance() const;
    int getFullDistance() const;

    ///@note wskazniki i klasa w polach prywatnych byly zbyt klopotliwe. One zostaly publiczne
    Node *parent;   ///< element ktory wywolal ten rekord. Poprzedni ruch
                    ///@note Z niego obliczam przebyty dystans
                    ///@warning To nie musi byc poprzedni element tej listy. To nie jest lista dwukierunkowa
    Node *next;     ///nastepny element listy

private:
    void calculateId();
    void predictDistanceLeft();

    int matrix_[3][3];
    int id_;
    int predictedDistanceLeft_;

    int traveledDistance_;  ///< dlugosc sciezki
    int fullDistance_;      ///< dllugosc sciezki + optymistyczna dlugosc drogi do celu
};

#endif // NODE_H
