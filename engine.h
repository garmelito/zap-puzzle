#ifndef ENGINE_H
#define ENGINE_H

#include "node.h"

bool solutionIsPosible (int board[3][3]);
int id (int board[][3]);
int h (int board[][3]);

void transferToClosedset (Node *&closedset, Node *openset);
void moveMaker (Node *openset, Node *closedset, int copy[][3], int luka_y, int luka_x, int obok_y, int obok_x);

Node *reconstructPath (Node *openset);
void extermination (Node *&head);

//potrzebne tylko do dzialania funkcji
/*void newBoard (int board[][3], int copy[][3], int luka_y, int luka_x, int obok_y, int obok_x);
bool alreadyInside (Node *head, int id);
void newNode (Node *openset, Node *parent, int fRating, int board[][3], int idRating);
bool notHere (Node *fresh, Node *topic);*/

#endif // ENGINE_H
