#ifndef NODE_H
#define NODE_H

#include "board.h"

class Node
{
public:
    Node(Board inputBoard, Node *parent);
    Node(Board inputBoard);

    int getTraveledDistance() const;
    int getFullDistance() const;

    Board board;
    Node *parent;   //element ktory wywolal ten rekord. Poprzedni ruch. To nie musi byc poprzedni element tej listy
    Node *next;

private:
    int traveledDistance_;  //dlugosc sciezki
    int fullDistance_;      //dllugosc sciezki + optymistyczna dlugosc drogi do celu
};

#endif // NODE_H
