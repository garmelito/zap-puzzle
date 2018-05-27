#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "board.h"
#include "engine.h"
#include "node.h"
#include "point.h"

#include <iostream>

using namespace std;

Node *algorithm(Board initialBoard, Board goalBoard);

#endif // ALGORITHM_H
