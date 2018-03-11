#ifndef ENGINE_H
#define ENGINE_H

#include "node.h"

int h (int board[][3]);
int id (int board[][3]);
void newBoard (int board[][3], int copy[][3], int luka_y, int luka_x, int obok_y, int obok_x);
void newNode (Node *openset, Node *parent, int fRating, int board[][3], int idRating);
bool notHere (Node *fresh, Node *topic);
void transferToClosedset (Node *&closedset, Node *openset);
bool alreadyInside (Node *head, int id);
Node *reconstructPath (Node *openset);
void extermination (Node *&head);

#endif // ENGINE_H
