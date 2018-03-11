#include "node.h"
#include "engine.h"
#include "interface.h"

#include <iostream>

using namespace std;

//Gdy nie znajdzie inputBoard.txt moze poprosic uzytkownika o dane wejsciowe z konsoli
//Zadanie moze nie miec rozwiazania. Na poczatku bedzie sprawdzenie parzystosci permutacji

int main()
{
    Node *openset = nullptr;
    Node *closedset = nullptr;

    openset = new Node;

    readFromFile (openset);

    openset->id = id(openset->board);

    openset->g = 0;
    openset->f = openset->g + h(openset->board);

    openset->parent = nullptr;
    openset->next = nullptr;

    int goal = 123456789;
    int luka_y;
    int luka_x;
    int copy_up[3][3];
    int copy_down[3][3];
    int copy_left[3][3];
    int copy_right[3][3];
    int fRating, idRating;
    while (openset->id != goal)
    {
        transferToClosedset(closedset, openset);
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                if (openset->board[i][j] == 9)
                {
                    luka_y = i;
                    luka_x = j;
                    break;
                }

        if (luka_y != 0)
        {
            newBoard(openset->board, copy_up, luka_y, luka_x, luka_y-1, luka_x);
            idRating = id(copy_up);
            if (!(alreadyInside(openset, idRating) || alreadyInside(closedset, idRating)))
            {
                fRating = openset->g + 1 + h(copy_up);
                newNode (openset, closedset, fRating, copy_up, idRating);
            }
        }
        if (luka_y != 2)
        {
            newBoard(openset->board, copy_down, luka_y, luka_x, luka_y+1, luka_x);
            idRating = id(copy_down);
            if (!(alreadyInside(openset, idRating) || alreadyInside(closedset, idRating)))
            {
                fRating = openset->g + 1 + h(copy_down);
                newNode (openset, closedset, fRating, copy_down, idRating);
            }
        }
        if (luka_x != 0)
        {
            newBoard(openset->board, copy_left, luka_y, luka_x, luka_y, luka_x-1);
            idRating = id(copy_left);
            if (!(alreadyInside(openset, idRating) || alreadyInside(closedset, idRating)))
            {
                fRating = openset->g + 1 + h(copy_left);
                newNode (openset, closedset, fRating, copy_left, idRating);
            }
        }
        if (luka_x != 2)
        {
            newBoard(openset->board, copy_right, luka_y, luka_x, luka_y, luka_x+1);
            idRating = id(copy_right);
            if (!(alreadyInside(openset, idRating) || alreadyInside(closedset, idRating)))
            {
                fRating = openset->g + 1 + h(copy_right);
                newNode (openset, closedset, fRating, copy_right, idRating);
            }
        }

        Node *temporary = openset;
        openset = openset->next;
        delete temporary;
    }

    Node *start = reconstructPath(openset);
    extermination(openset);
    extermination(closedset);
    printSteps(start);
    return 0;
}
