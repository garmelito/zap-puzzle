#ifndef ENGINE_H
#define ENGINE_H

#include "node.h"
#include "point.h"

#include <string>

using namespace std;

bool readFromFile (string nazwa, int matrix[][3]);
void draw (int table[]);

bool solutionIsPosible(int matrix[][3]);
bool inRules(int matrix[][3]);

void transferToClosedset (Node *&closedset, Node *openset);
void moveMaker (Node *openset, Node *closedset, Point luka, int obok_y, int obok_x);

Node *reconstructPath (Node *openset);
void extermination (Node *&head);

#endif // ENGINE_H
