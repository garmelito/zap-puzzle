#include "engine.h"

#include <cmath>

int h (int board[][3])
{
    int h = 0;
    //chyba nie powiniennem liczyc plytki numer 9. Kiedys to sprawdze
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
        {
            int m = (board[i][j]-1)/3;
            int n = (board[i][j]%3)-1;
            if (n<0)    n += 3;
            h += abs(m-i) + abs(n-j);
        }
    return h;
}

int id (int board[][3])
{
    int suma = 0;
    int waga = 100000000;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
        {
            suma += board[i][j] * waga;
            waga /= 10;
        }
    return suma;
}

void newBoard (int board[][3], int copy[][3], int luka_y, int luka_x, int obok_y, int obok_x)
{
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            copy[i][j] = board[i][j];

    int bufor = copy[luka_y][luka_x];
    copy[luka_y][luka_x] = copy[obok_y][obok_x];
    copy[obok_y][obok_x] = bufor;
}

void newNode (Node *openset, Node *parent, int fRating, int board[][3], int idRating)
{
    Node *fresh = new Node;
    fresh->g = parent->g+1;
    fresh->f = fRating;

    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            fresh->board[i][j] = board[i][j];
    fresh->id = idRating;
    fresh->parent = parent;

    Node *topic = openset;
    while (notHere(fresh, topic))
        topic = topic->next;
    fresh->next = topic->next;
    topic->next = fresh;
}

bool notHere (Node *fresh, Node *topic)
{
    if (topic->next == nullptr)
        return false;
    if (fresh->f > topic->next->f)
        return true;
    return false;
}

void transferToClosedset (Node *&closedset, Node *openset)
{
    Node *anew = new Node;
    *anew = *openset;
    anew->next = closedset;
    closedset = anew;
}

bool alreadyInside (Node *head, int id)
{
    while (head != nullptr)
    {
        if (head->id == id)
            return true;
        head = head->next;
    }
    return false;
}

Node *reconstructPath (Node *openset)
{
    Node *head = new Node;
    *head = *openset;
    head->next = nullptr;

    while (head->parent != nullptr)
    {
        Node *current = new Node;
        *current = *(head->parent);
        current ->next = head;
        head = current;
    }
    return head;
}

void extermination (Node *&head)
{
    Node *topic = head;
    while (topic != nullptr)
    {
        Node *temporary = topic;
        topic = topic->next;
        delete temporary;
    }
    head = nullptr;
}
