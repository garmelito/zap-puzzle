#ifndef BOARD_H
#define BOARD_H

#include "point.h"

/**
 * @brief klasa zawierajaca ulozenie i informacje mozliwe do wyliczenia z niego
 * @note jest polem klasy Node
 */
class Board
{
public:
    Board(int matrix[][3]);

    Point findEmptySpace();
    Board clone(Point luka, int obok_y, int obok_x);
    const int *getMatrix() const;

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
