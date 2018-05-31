#include "node.h"

/**
 * @brief konstruktor elementow listy otwartej
 * @param inputBoard - obiekt typu Board na podstawie ktorej ma zostac stworzony ten obiekt
 * @param parent - poprzedni ruch
 */
Node::Node(Board inputBoard, Node *parent)
    : board(inputBoard)     //board = input board, w ten sposob bo konstruktorowi boarda musialbym podac tablice ktorej juz nie mam
{
    this->parent = parent;
    traveledDistance_ = parent->traveledDistance_ + 1;
    fullDistance_ = traveledDistance_ + board.getPredictedDistance();
}

/**
 * @brief konstruktor dla pierwszego elementu listy otwartej i wszystkich obiektow listy elementow zamknietych
 * @param inputBoard - obiekt typu Board na podstawie ktorej ma zostac stworzony ten obiekt
 */
Node::Node(Board inputBoard)
    : board(inputBoard)
{
    parent = nullptr;
    traveledDistance_ = 0;
    fullDistance_ = board.getPredictedDistance();
}

int Node::getTraveledDistance() const
{
    return traveledDistance_;
}

int Node::getFullDistance() const
{
    return fullDistance_;
}
