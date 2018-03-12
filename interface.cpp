#include "interface.h"

#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

void readFromFile (Node *openset)
{
    ifstream input ("inputBoard.txt");
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            input >>openset->board[i][j];
    input.close();
}

void printSteps (Node *current)
{
    while (current != nullptr)
    {
        system("cls");
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<3; j++)
                if (current->board[i][j] == 9)
                    cout <<"  ";
                else
                    cout <<current->board[i][j] <<" ";
            cout <<endl;
        }
        Sleep(480);
        current = current->next;
    }
}
