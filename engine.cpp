#include "engine.h"

#include <cmath>

bool solutionIsPosible (int board[][3])
{
    int permutationInversions = 0;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
        {
            if (board[i][j] == 9)
                permutationInversions += i + 1;
            else
            {
                for (int l=j; l<3; l++)
                    if (board[i][l] < board[i][j])
                        permutationInversions ++;
                for (int k=i+1; k<3; k++)
                    for (int l=0; l<3; l++)
                        if (board[k][l] < board[i][j])
                            permutationInversions ++;
            }
        }

    if (permutationInversions % 2 != 0)
        return true;
    return false;
}

bool inRules (int board[][3])
{
    bool seen[9];
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            seen[board[i][j]-1] = true;

    for (int i=0; i<9; i++)
        if (seen[i] == false)
            return false;
    return true;
}

//zwraca identyfikator
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

//zwraca optymistyczna dlugosc sciezki do celu
int h (int board[][3])
{
    int h = 0;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
        {
            //sumuje odleglosc kazdego elementu od swojego polozenia
            int m = (board[i][j]-1)/3;  //wspolrzedna y wlasciwego polozenia
            int n = (board[i][j]%3)-1;  //wspolrzedna x wlasciwego polozenia
            if (n<0)    n += 3;
            h += abs(m-i) + abs(n-j);   //odleglosc aktualnego polozenia od wlasciwego
        }
    return h;
}

//kopiuje element do listy elementow odwiedzonych. Towrzy tam NOWY element ktoremu przepisuje wartosci
void transferToClosedset (Node *&closedset, Node *openset)
{
    Node *anew = new Node;
    *anew = *openset;
    anew->next = closedset;
    closedset = anew;
}

//tworzy nowa tablice w ktorej na miejsce luki (9) wchodzi plytka obok
void newBoard (int board[][3], int copy[][3], int luka_y, int luka_x, int obok_y, int obok_x)
{
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            copy[i][j] = board[i][j];

    int bufor = copy[luka_y][luka_x];
    copy[luka_y][luka_x] = copy[obok_y][obok_x];
    copy[obok_y][obok_x] = bufor;
}

//sprawdza czy element juz jest w danej liscie
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

//wykorzystywane do tworzenia nowego wezla, gdy szukam miejsca w ktorym go umiescic sortujac po f
bool notHere (Node *fresh, Node *topic)
{
    if (topic->next == nullptr)
        return false;
    if (fresh->f > topic->next->f)
        return true;
    return false;
}

//tworzy nowy wezel do liscie dostepnych
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

//Umieszcza nowe elementy na liscie dostepnych mozliwosci
void moveMaker (Node *openset, Node *closedset, int copy[][3], int luka_y, int luka_x, int obok_y, int obok_x)
{
    newBoard(openset->board, copy, luka_y, luka_x, obok_y, obok_x);
    int idRating = id(copy);
    if (!(alreadyInside(openset, idRating) || alreadyInside(closedset, idRating)))
    {
        int fRating = openset->g + 1 + h(copy);
        newNode (openset, closedset, fRating, copy, idRating);
    }
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
