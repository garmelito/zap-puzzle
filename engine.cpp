#include "engine.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

/// \brief odczytuje poczatkowe polozenie z pliku tekstowego
/// \param nazwa nazwa pliku wraz z rozszerzeniem .txt
/// \param matrix[][3] tablica do ktorej ma zostac przypisane wejsciowe ulozenie
/// \return powodzenie lub niepowodzenie pobrania danych z pliku
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

/// \brief Sprawdza czy liczba pojawia sie w tablicy do indexu i
/// Wykorzystywana w funkcji draw aby sprawdzic czy element zostal juz wylosowany
bool inside (int drawn, int table[], int n)
{
    for (int i=0; i<n; i++)
    {
        if (drawn == table[i])
            return true;
    }
    return false;
}

/// \brief losuje tablice z polozeniem poczatkowym
/// \param table[] tablica do ktorej zostana wylosowane elementy
void draw(int table[])
{
    int drawn;
    for (int i=0; i<9; i++)
    {
        do{
            drawn = rand()%9+1;
        }while (inside(drawn, table, i));
        table[i] = drawn;
    }
}

/**
 * @brief solutionIsPosible sprawdza czy dane ulozenie ma rozwiazanie
 * kazde ulozenie ma charakterystyczna liczbe permutacji. Ruchy zmieniaja ja o przysta ilosc. Do rozwiazania da sie doprowadzic tylko poloze ulozen poczatkowych
 * \return ulozenie albo ma rozwiazanie albo go nie ma
 */
bool solutionIsPosible(int matrix[][3])
{
    ///liczba permutacaji to suma dla kazdej plytki ilosci mniejszych plytek wystepujacych dalej + wiersz w ktorym znajduje sie pusta
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

/// \brief sprawdzaczy zadne cyfry sie nie powtarzaja ani nie wystepuja niedozwolone znaki
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

/// \brief kopiuje element do listy elementow zamknietych. Towrzy tam NOWY element ktoremu przepisuje wartosci
void transferToClosedset (Node *&closedset, Node *openset)
{
    Node *anew = new Node(openset->board);
    *anew = *openset;
    anew->next = closedset;
    closedset = anew;
}

/// \brief sprawdza czy element juz jest w danej liscie
/// przed dodaniem do listy sprawdzam to aby nie storzyc dubla
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

/// \brief wykorzystywane do tworzenia nowego wezla, gdy szukam miejsca w ktorym go umiescic sortujac po fullDistance
bool insertHere (Node *fresh, Node *looking)
{
    if (looking->next == nullptr)
        return true;
    if (fresh->getFullDistance() > looking->next->getFullDistance())
        return false;
    return true;
}

/**
 * @brief insertNode to insert node
 * @param openset to openset
 * @param parent to parent
 * @param environment to environment
 */
void insertNode (Node *openset, Node *parent, Board environment)
{
    Node *fresh = new Node(environment, parent);
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
