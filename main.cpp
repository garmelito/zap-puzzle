#include <iostream>
#include <fstream>
using namespace std;

//Potem dodam sprawdzanie czy inputBoard.txt dziala czy moze go nie ma
//Zadanie moze nie miec rozwiazania. While powinien działac dopuki openset != NULL, a wewnatrz bedzie if porownujacy tablice z rozwiazaniem
//Będę musiał jakoś podzielić program na moduły
//Na koniec musi znajdować droge

struct bond
{
    int g, f;
    int board[3][3];
    int id;
    bond *parent;
    bond *next;
};

int h (int board[][3]);
int module (int number);
int id (int board[][3]);
void newBoard (int board[][3], int copy[][3], int luka_y, int luka_x, int obok_y, int obok_x);
void newBond (bond *openset, int fRating, int board[][3], int idRating);
bool notHere (bond *fresh, bond *topic);
void transferToClosedset (bond *&closedset, bond *openset);
bool alreadyInside (bond *head, int id);
bond *reconstructPath (bond *openset);
void extermination (bond *&head);

int main()
{
    bond *openset = NULL;
    bond *closedset = NULL;

    openset = new bond;

    ifstream input ("inputBoard.txt");
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            input >>openset->board[i][j];
    input.close();
    openset->id = id(openset->board);

    openset->g = 0;
    openset->f = openset->g + h(openset->board);

    openset->parent = NULL;
    openset->next = NULL;

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
                    newBond (openset, fRating, copy_up, idRating);
            }
        }
        if (luka_y != 2)
        {
            newBoard(openset->board, copy_down, luka_y, luka_x, luka_y+1, luka_x);
            idRating = id(copy_down);
            if (!(alreadyInside(openset, idRating) || alreadyInside(closedset, idRating)))
            {
                fRating = openset->g + 1 + h(copy_down);
                newBond (openset, fRating, copy_down, idRating);
            }
        }
        if (luka_x != 0)
        {
            newBoard(openset->board, copy_left, luka_y, luka_x, luka_y, luka_x-1);
            idRating = id(copy_left);
            if (!(alreadyInside(openset, idRating) || alreadyInside(closedset, idRating)))
            {
                fRating = openset->g + 1 + h(copy_left);
                newBond (openset, fRating, copy_left, idRating);
            }
        }
        if (luka_x != 2)
        {
            newBoard(openset->board, copy_right, luka_y, luka_x, luka_y, luka_x+1);
            idRating = id(copy_right);
            if (!(alreadyInside(openset, idRating) || alreadyInside(closedset, idRating)))
            {
                fRating = openset->g + 1 + h(copy_right);
                newBond (openset, fRating, copy_right, idRating);
            }
        }

        transferToClosedset(closedset, openset);
        bond *temporary = openset;
        openset = openset->next;
        delete temporary;
    }

    //bond *start = reconstructPath(openset);
    extermination(openset);
    extermination(closedset);

    return 0;
}


//________________________________________________________________________________________
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
            h += (module(m-i) + module(n-j));
        }
    return h;
}

int module (int number)
{
    if (number < 0)
        number = (-number);
    return number;
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

void newBond (bond *openset, int fRating, int board[][3], int idRating)
{
    bond *fresh = new bond;
    fresh->g = openset->g+1;
    fresh->f = fRating;

    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            fresh->board[i][j] = board[i][j];
    fresh->id = idRating;
    fresh->parent = openset;

    bond *topic = openset;
    while (notHere(fresh, topic))
        topic = topic->next;
    fresh->next = topic->next;
    topic->next = fresh;
}

bool notHere (bond *fresh, bond *topic)
{
    if (topic->next == NULL)
        return false;
    if (fresh->f > topic->next->f)
        return true;
    return false;
}

void transferToClosedset (bond *&closedset, bond *openset)
{
    bond *anew = new bond;
    *anew = *openset;
    anew->next = closedset;
    closedset = anew;
}

bool alreadyInside (bond *head, int id)
{
    while (head != NULL)
    {
        if (head->id == id)
            return true;
        head = head->next;
    }
    return false;
}

bond *reconstructPath (bond *openset)
{
    bond *head = new bond;
    *head = *openset;
    head->next = NULL;

    while (head->parent != NULL)
    {
        bond *current = new bond;
        *current = *(head->parent);
        current ->next = head;
        head = current;
    }
    return head;
}

void extermination (bond *&head)
{
    bond *topic = head;
    while (topic != NULL)
    {
        bond *temporary = topic;
        topic = topic->next;
        delete temporary;
    }
    head = NULL;
}
