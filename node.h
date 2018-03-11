#ifndef NODE_H
#define NODE_H

struct Node
{
    int g, f;
    int board[3][3];
    int id;
    Node *parent;
    Node *next;
};

#endif // NODE_H
