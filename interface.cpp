#include "interface.h"

#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;

void readFromFile (int board[][3])
{
    ifstream input ("inputBoard.txt");
    if (input)
    {
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                input >>board[i][j];
        input.close();
    }
    else
        readFromConsole (board);
}

void readFromConsole (int board[][3])
{
    cout <<"Nie odnalazlem pliku lub mial bledne dane wejsciowe. Podaj PESEL \n";
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            cin >>board[i][j];
}

void printSteps (Node *current)
{
    while (current != nullptr)
    {
        system("cls");
        //cout <<endl;
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
