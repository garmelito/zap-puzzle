#include "engine.h"

#include <cmath>

bool solutionIsPosible(int matrix[][3])
{
    int permutationInversions = 0;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
        {
            if (matrix[i][j] == 9)
                permutationInversions += i + 1;
            else
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

    if (permutationInversions % 2 != 0)
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
    Node *anew = new Node(openset->board);
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

//wykorzystywane do tworzenia nowego wezla, gdy szukam miejsca w ktorym go umiescic sortujac po f
bool notHere (Node *fresh, Node *looking)
{
    if (looking->next == nullptr)
        return false;
    if (fresh->f > looking->next->f)
        return true;
    return false;
}

//tworzy nowy wezel do liscie dostepnych
void newNode (Node *openset, Node *parent, int fRating, Board board)
{
    Node *fresh = new Node(board);
    fresh->g = parent->g+1;
    fresh->f = fRating; //chyba moglbym wyliczac z parent->g + 1 + board.predictDistanceLeft()
    fresh->parent = parent;

    Node *looking = openset;
    while (notHere(fresh, looking))
        looking = looking->next;
    fresh->next = looking->next;
    looking->next = fresh;
}

//Umieszcza nowe elementy na liscie dostepnych mozliwosci
void moveMaker(Node *openset, Node *closedset, Point luka, int obok_y, int obok_x)
{
    Board environment = openset->board.clone(luka, obok_y, obok_x);
    if (!(alreadyInside(openset, environment.getId()) || alreadyInside(closedset, environment.getId())))
    {
        int fRating = openset->g + 1 + environment.getPredictedDistance();
        newNode (openset, closedset, fRating, environment);
    }
}

Node *reconstructPath (Node *openset)
{
    Node *head = new Node(openset->board);
    *head = *openset;
    head->next = nullptr;

    while (head->parent != nullptr)
    {
        Node *current = new Node(head->parent->board);
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
