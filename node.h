#ifndef NODE_H
#define NODE_H

struct Node
{
    int g, f;   //dlugosc sciezki, glugosc sciezki + optymistyczna dlugosc drogi do celu
    int board[3][3];
    int id;
    Node *parent;   //element ktory wywolal ten rekord. Poprzedni ruch. To nie musi byc poprzedni element tej listy
    Node *next;
};

#endif // NODE_H
