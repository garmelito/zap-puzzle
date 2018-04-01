#ifndef NODE_H
#define NODE_H

#include "board.h"

struct Node
{
    Node(Board inputBoard);

    int g, f;   //dlugosc sciezki, glugosc sciezki + optymistyczna dlugosc drogi do celu
    Board board;
    Node *parent;   //element ktory wywolal ten rekord. Poprzedni ruch. To nie musi byc poprzedni element tej listy
    Node *next;
};

#endif // NODE_H
