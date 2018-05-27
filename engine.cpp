#include "engine.h"

#include <fstream>
#include <cmath>

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

//kazdy ruch zmienia permutacje o parzysta ilosc. Dla ruchu w poziomie 0, a w pionie -2, 0 lub +2
//numer rzedu pustej plytki potrzebny jest tylko dla plansz 4x4 i innych parzystych. Tutaj wprowadzal bledy
bool solutionIsPosible(int matrix[][3])
{
    int permutationInversions = 0;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
        {
            if (matrix[i][j] != 9)
            {
                for (int l=j; l<3; l++)
                    if (matrix[i][l] < matrix[i][j])
                        permutationInversions ++;
                for (int k=i+1; k<3; k++)
                    for (int l=0; l<3; l++)
                        if (matrix[k][l] < matrix[i][j])
                            permutationInversions ++;
            }
        }

    if (permutationInversions % 2 == 0)
        return true;
    return false;
}

bool inRules(int matrix[][3])
{
    bool seen[9];
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            seen[matrix[i][j]-1] = true;

    for (int i=0; i<9; i++)
        if (seen[i] == false)
            return false;
    return true;
}

//kopiuje element do listy elementow odwiedzonych. Towrzy tam NOWY element ktoremu przepisuje wartosci
void transferToClosedset (Node *&closedset, Node *openset)
{
    Node *anew = new Node(openset->board, openset->goal);
    *anew = *openset;
    anew->next = closedset;
    closedset = anew;
}

//sprawdza czy element juz jest w danej liscie
bool alreadyInside (Node *head, int id)
{
    while (head != nullptr)
    {
        if (head->board.getId() == id)
            return true;
        head = head->next;
    }
    return false;
}

//wykorzystywane do tworzenia nowego wezla, gdy szukam miejsca w ktorym go umiescic sortujac po fullDistance
bool insertHere (Node *fresh, Node *looking)
{
    if (looking->next == nullptr)
        return true;
    if (fresh->getFullDistance() > looking->next->getFullDistance())
        return false;
    return true;
}

//tworzy nowy wezel do liscie dostepnych
void insertNode (Node *openset, Node *parent, Board environment)
{
    Node *fresh = new Node(environment, openset->goal, parent);
    Node *looking = openset;
    while (!insertHere(fresh, looking))
        looking = looking->next;
    fresh->next = looking->next;
    looking->next = fresh;
}

//Umieszcza nowe elementy na liscie dostepnych mozliwosci
void moveMaker(Node *openset, Node *closedset, Point luka, int obok_y, int obok_x)
{
    Board environment = openset->board.clone(luka, obok_y, obok_x);
    if (!(alreadyInside(openset, environment.getId()) || alreadyInside(closedset, environment.getId())))
        insertNode(openset, closedset, environment);
}

Node *reconstructPath (Node *openset)
{
    Node *head = new Node(openset->board, openset->goal);
    *head = *openset;
    head->next = nullptr;

    while (head->parent != nullptr)
    {
        Node *current = new Node(head->parent->board, openset->goal);
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
