#ifndef BOARD_H
#define BOARD_H

#include "point.h"

/**
  * \file board.h
  * \brief klasa Board i jej metody
  */

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

    const int *getMatrix() const;       ///< zwraca ulozenie w tablicy jednowymiarowej
    int getId() const;                  ///< zwraca id ulozenia
    int getPredictedDistance() const;   ///< zwraca przewidywana droge

private:    
    int matrix_[3][3];          ///< macierz z ulozeniem
    int id_;                    ///< charakterystyczne id
    int predictedDistanceLeft_; ///< optymistyczna pozostala ilosc ruchow

    void calculateId();
    void predictDistanceLeft();
};

#endif // BOARD_H
