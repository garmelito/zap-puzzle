#include "interface.h"

#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;

bool readFromFile(string nazwa, int matrix[][3])
{
    ifstream input (nazwa);
    if (input)
    {
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                input >>matrix[i][j];
        input.close();
        return true;
    }
    return false;
}

void readFromConsole (int matrix[][3])
{
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            cin >>matrix[i][j];
}

void printSteps (Node *current)
{
    while (current != nullptr)
    {
        system("cls");
        current->board.print();
        Sleep(480);
        current = current->next;
    }
}
