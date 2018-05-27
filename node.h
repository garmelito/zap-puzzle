#ifndef NODE_H
#define NODE_H

#include "board.h"

class Node
{
public:
    Node(Board inputBoard, Board inputGoal, Node *parent);
    Node(Board inputBoard, Board inputGoal);

    int getTraveledDistance() const;
    int getFullDistance() const;

    Board board;
    Board goal;
    Node *parent;   //element ktory wywolal ten rekord. Poprzedni ruch. To nie musi byc poprzedni element tej listy
    Node *next;

private:
    void predictDistanceLeft();

    int traveledDistance_;  //dlugosc sciezki
    int fullDistance_;      //dllugosc sciezki + optymistyczna dlugosc drogi do celu
    int predictedDistanceLeft_;
};

#endif // NODE_H
