#include "node.h"
#include "engine.h"
#include "interface.h"

#include <iostream>

using namespace std;

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

    int goal = 123456789;   //id ulozenia ktore jest rozwiazaniem
    int luka_y;
    int luka_x;
    int copy_up[3][3];
    int copy_down[3][3];
    int copy_left[3][3];
    int copy_right[3][3];

    while (openset->id != goal)
    {
        transferToClosedset(closedset, openset);    //kopiuje element ktorym sie teraz zajmuje do listy elementow odwiedzonych
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                if (openset->board[i][j] == 9)
                {
                    luka_y = i;
                    luka_x = j;
                    break;
                }
        //sprawdza czy nie stoi przy danej krawedzi, a potem, jezeli moze, wykonuje ruch
        if (luka_y != 0)
            moveMaker (openset, closedset, copy_up, luka_y, luka_x, luka_y-1, luka_x);
        if (luka_y != 2)
            moveMaker (openset, closedset, copy_down, luka_y, luka_x, luka_y+1, luka_x);
        if (luka_x != 0)
            moveMaker (openset, closedset, copy_left, luka_y, luka_x, luka_y, luka_x-1);
        if (luka_x != 2)
            moveMaker (openset, closedset, copy_right, luka_y, luka_x, luka_y, luka_x+1);

        //usuwa element ktorym sie aktualnie zajmowal. Juz przepisal go do listy elementow odwiedzonych
        Node *temporary = openset;
        openset = openset->next;
        delete temporary;
    }

    Node *start = reconstructPath(openset);
    extermination(openset);
    extermination(closedset);
    printSteps(start);
    extermination(start);
    return 0;
}
