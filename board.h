#ifndef BOARD_H
#define BOARD_H

#include "point.h"

class Board
{
public:
    Board(int matrix[][3]);
    Board clone(Point luka, int obok_y, int obok_x);
    Point findEmptySpace();
    void print();
    int getId();
    int getPredictedDistance();
private:
    int matrix_[3][3];
    int id_;
    int predictedDistanceLeft_;

    void calculateId();
    void predictDistanceLeft();
};

#endif // BOARD_H
