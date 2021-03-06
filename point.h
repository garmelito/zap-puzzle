#ifndef POINT_H
#define POINT_H

/**
  * \file point.h
  * \brief struktura Point
  */

/**
 *  @brief wspolrzedne punktu na plaszczyznie
 *  @note pozwala funkcjom na zwrocenie i odcietej i rzednej
 */
struct Point
{
    int x;  ///< odcieta - numer kolumny
    int y;  ///< rzedna - numer wiersza
};

#endif // POINT_H
