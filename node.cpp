#include "node.h"

Node::Node(Board inputBoard, Board inputGoal, Node *parent)
    : board(inputBoard)     //board = input board, w ten sposob bo konstruktorowi boarda musialbym podac tablice ktorej juz nie mam
    : goal(inputGoal)
{
    this->parent = parent;
    traveledDistance_ = parent->traveledDistance_ + 1;
    predictDistanceLeft();
    fullDistance_ = traveledDistance_ + predictedDistanceLeft_;
}

Node::Node(Board inputBoard, Board inputGoal)
    : board(inputBoard)
    : goal(inputGoal)
{
    parent = nullptr;
    traveledDistance_ = 0;
    predictDistanceLeft();
    fullDistance_ = predictedDistanceLeft_;
}

int Node::getTraveledDistance() const
{
    return traveledDistance_;
}

int Node::getFullDistance() const
{
    return fullDistance_;
}

void Node::predictDistanceLeft()
{
    int h = 0;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
        {
//            //sumuje odleglosc kazdego elementu od swojego polozenia
//            int m = (matrix_[i][j]-1)/3;  //wspolrzedna y wlasciwego polozenia
//            int n = (matrix_[i][j]%3)-1;  //wspolrzedna x wlasciwego polozenia
//            if (n<0)    n += 3;
//            h += abs(m-i) + abs(n-j);   //odleglosc aktualnego polozenia od wlasciwego

//            uproszczona wersja
//            if (matrix_[i][j] != i*3+j+1)
//                h++;

            auto input = board.getMatrix();
            auto goal = goal.getMatrix();
            for (int i=0; i<9; i++)
                if (input[i] != goal[i])
                    h++;
        }
    predictedDistanceLeft_ = h;
}
