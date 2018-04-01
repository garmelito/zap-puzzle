#include "board.h"  //zawiera "point.h"
#include "engine.h" //engine.h i interface.h zawieraja "node.h"
#include "interface.h"
#include "node.h"

#include <iostream>
//#include <ctime>

using namespace std;

//board aka environment
//matrix is filled with numbers

int main()
{
    //clock_t beginning = clock();
    Node *openset = nullptr;
    Node *closedset = nullptr;

    int initialMatrix[3][3];
    readFromFile (initialMatrix);

    while (!(solutionIsPosible(initialMatrix) && inRules(initialMatrix)))
        readFromConsole(initialMatrix);

    Board initialBoard(initialMatrix);
    openset = new Node(initialBoard);

    openset->g = 0;
    openset->f = openset->g + initialBoard.getPredictedDistance();

    openset->parent = nullptr;
    openset->next = nullptr;

    const int GOAL = 123456789;   //id ulozenia ktore jest rozwiazaniem
    int copy_up[3][3];
    int copy_down[3][3];
    int copy_left[3][3];
    int copy_right[3][3];

    while (openset->board.getId() != GOAL)
    {
        transferToClosedset(closedset, openset);    //kopiuje element ktorym sie teraz zajmuje do listy elementow odwiedzonych
        Point luka = openset->board.findEmptySpace();
        //sprawdza czy nie stoi przy danej krawedzi, a potem, jezeli moze, wykonuje ruch
        if (luka.y != 0)
            moveMaker (openset, closedset, luka, luka.y-1, luka.x);
        if (luka.y != 2)
            moveMaker (openset, closedset, luka, luka.y+1, luka.x);
        if (luka.x != 0)
            moveMaker (openset, closedset, luka, luka.y, luka.x-1);
        if (luka.x != 2)
            moveMaker (openset, closedset, luka, luka.y, luka.x+1);

        //usuwa element ktorym sie aktualnie zajmowal. Juz przepisal go do listy elementow odwiedzonych
        Node *temporary = openset;
        openset = openset->next;
        delete temporary;
    }

    Node *start = reconstructPath(openset);
    extermination(openset);
    extermination(closedset);

    /*clock_t finish = clock();
    double duration = double(finish - beginning)/CLOCKS_PER_SEC;
    cout <<duration;
    system("pause");*/

    printSteps(start);
    extermination(start);
    return 0;
}
