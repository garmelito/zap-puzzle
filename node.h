#ifndef NODE_H
#define NODE_H

#include "board.h"

/**
  * \file node.h
  * \brief klasa Node i jej metody
  */

/**
 * @brief Poza informacjami o ulozeniu zawiera dane o przebytej odleglosci i daje sie ulozyc w liste
 * @note Wydawaloby sie ze prosciej byloby przeniesc pola i metody boarda do noda ale wcale nie. Wtedy jest ogromny klopot miedzy innymi z tworzeniem
 * nowych elementow
 */
class Node
{
public:
    Node(Board inputBoard, Node *parent);
    Node(Board inputBoard);

    int getTraveledDistance() const;        ///< zwraca przebyta droge
    int getFullDistance() const;            ///< zwraca przebyta + przewidywana droge

    ///@note wskazniki i klasa w polach prywatnych byly zbyt klopotliwe. One zostaly publiczne
    Board board;    ///< informacje mozliwe do wyliczenia z ulozenia
    Node *parent;   ///< element ktory wywolal ten rekord. Poprzedni ruch
                    /// @note Z niego obliczam przebyty dystans
                    /// @warning To nie musi byc poprzedni element tej listy. To nie jest lista dwukierunkowa
                    ///
    Node *next;     ///<nastepny element listy

private:
    int traveledDistance_;  ///< dlugosc sciezki
    int fullDistance_;      ///< dllugosc sciezki + optymistyczna dlugosc drogi do celu
};

#endif // NODE_H
