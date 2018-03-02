#include <iostream>
#include <fstream>
using namespace std;
//sprawdzenie czy plik istnieje
//zadanie moze nie miec rozwiazania. While powinien działac dopuki openset != NULL, a wewnatrz powinien byc if porownujacy tablice z rozwiazaniem;

struct bond
{
    int g, f;
    int board[3][3];
    int id;
    bond *parent;
    bond *next;
};

int module (int number)
{
    if (number < 0)
        number = (-number);
    return number;
}

int h (int board[][3])
{
    int h = 0;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
        {
            int m = (board[i][j]-1)/3;
            int n = (board[i][j]%3)-1;
            h += (module(m-i) + module(n-j));
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

int main()
{
    bond *openset = NULL;
    bond *closedset = NULL;

    openset = new bond;
    openset->g = 0;
    openset->f = openset->g + h(openset->board);

    ifstream input ("inputBoard.txt");
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            input >>openset->board[i][j];
    input.close();

    openset->id = id(openset->board);
    openset->parent = NULL;
    openset->next = NULL;

    return 0;
}
