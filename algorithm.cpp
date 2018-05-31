#include "algorithm.h"
#include "engine.h"
#include "point.h"

#include <iostream>

using namespace std;

/**
 * @brief znajduje najkrotsza sciezke przy pomocy algorytmu A*
 * @param initialBoard - polozenie poczatkowe
 * @return wskaznik do pierwszego elementu listy koeljnych krokow rozwiazania
 */
Node *algorithm(Node initialNode)
{
    Node *openset = nullptr;
    Node *closedset = nullptr;

    openset = initialNode;
    openset->next = nullptr;

    const int GOAL = 123456789;   //id ulozenia ktore jest rozwiazaniem
    while (openset->getId() != GOAL)
    {
        transferToClosedset(closedset, openset);    //kopiuje element ktorym sie teraz zajmuje do listy elementow odwiedzonych
        Point luka = openset->board.findEmptySpace();
        //sprawdza czy nie stoi przy danej krawedzi, a potem, jezeli moze, wykonuje ruch
        if (luka.y != 0)
            moveMaker (openset, closedset, luka, luka.y-1, luka.x);
        if (luka.y != 2)
            moveMaker (openset, closedset, luka, luka.y+1, luka.x);
        if (luka.x != 0)
            moveMaker (openset, closedset, luka, luka.y, luka.x-1);
        if (luka.x != 2)
            moveMaker (openset, closedset, luka, luka.y, luka.x+1);

        //usuwa element ktorym sie aktualnie zajmowal. Juz przepisal go do listy elementow odwiedzonych
        Node *temporary = openset;
        openset = openset->next;
        delete temporary;
    }

    Node *start = reconstructPath(openset);
    extermination(openset);
    extermination(closedset);

    return start;
}
