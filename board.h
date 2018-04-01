#ifndef BOARD_H
#define BOARD_H

#include "point.h"

class Board
{
public:
    Board(int matrix[][3]);

    Point findEmptySpace();
    Board clone(Point luka, int obok_y, int obok_x);
    void print();

    int getId() const;
    int getPredictedDistance() const;

private:
    int matrix_[3][3];
    int id_;
    int predictedDistanceLeft_;

    void calculateId();
    void predictDistanceLeft();
};

#endif // BOARD_H
