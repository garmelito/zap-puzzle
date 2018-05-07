#ifndef BOARD_H
#define BOARD_H

#include "point.h"

class Board
{
public:
    Board(int matrix[][3]);

    Point findEmptySpace();
    Board clone(Point luka, int obok_y, int obok_x);

    int getId() const;
    int getPredictedDistance() const;

    int matrix_[3][3];

private:
    int id_;
    int predictedDistanceLeft_;

    void calculateId();
    void predictDistanceLeft();
};

#endif // BOARD_H
