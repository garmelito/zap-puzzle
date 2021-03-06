#include "board.h"
#include "engine.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

/**
 * @brief czyta poczatkowe ulozenie z pliku
 * @param nazwa - nazwa pliku tekstowego
 * @param matrix - tablica do korej zostaja wpisane dane wejsciowe
 * @return czy udalo sie pobrac dane
 */
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

/**
 * @brief Sprawdza czy liczba pojawia sie w tablicy do indexu i
 * @param drawn - porownywana liczba
 * @param table - przeszukiwana tablica
 * @param n - index do ktorego tablica jest przeszukiwana
 * @return czy znaleziono element w tablicy
 * @note wykorzystywana w funkcji draw do losowania bez powtorzen
 */
bool inside (int drawn, int table[], int n)
{
    for (int i=0; i<n; i++)
    {
        if (drawn == table[i])
            return true;
    }
    return false;
}

/**
 * @brief losuje poczatkowe polozenie
 * @param tablica z wylosowanymi elementami
 * @return tablice przez referencje
 */
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
 * @brief sprawdza czy dane ulozenie ma rozwiazanie
 * @note kazde ulozenie ma charakterystyczna liczbe permutacji. Ruchy zmieniaja ja o przysta ilosc. Rozwiazanie ma parzysta liczbe permutacji,
 * wiec polozenie poczatkowe tez musi miec. Mozna rozwiazac tylko polowe ulozen poczatkowych
 * @return czy ulozenie ma rozwiazanie
 */
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

///
/**
 * @brief sprawdza czy zadne cyfry sie nie powtarzaja ani nie wystepuja niedozwolone znaki
 * @param matrix - sprawdzana tablica
 * @return czy dane sa poprawne
 */
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

/**
 * @brief kopiuje element do listy elementow zamknietych
 *
 * Towrzy tam NOWY element ktoremu przepisuje wartosci
 * @param closedset - glowa listy elementow zamknietych
 * @param openset - glowa listy elementow otwartych
 */
void transferToClosedset (Node *&closedset, Node *openset)
{
    Node *anew = new Node(openset->board);
    *anew = *openset;
    anew->next = closedset;
    closedset = anew;
}

/**
 * @brief sprawdza czy element juz jest wpisany do listy
 * @param head - glowa listy
 * @param id - identyfikator po ktorym dane sa porownywane
 * @return czy znaleziono taki element w liscie
 * @note moze sie zdarzyc ze drugi raz innym sposobem znajde to samo ulozenie. Nie chce dodac dubla
 */
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

/**
 * @brief znajduje miejsce w liscie do umieszczenia wezla
 * @param fresh - nowy element
 * @param looking - porownywany element
 * @return wstawic nowy element za porownywany czy szukac dalej
 */
bool insertHere (Node *fresh, Node *looking)
{
    if (looking->next == nullptr)
        return true;
    if (fresh->getFullDistance() > looking->next->getFullDistance())
        return false;
    return true;
}

/**
 * @brief tworzy nowy wezel do dodania do listy elementow otwartych
 * @param openset - glowa listy elementow otwartych
 * @param parent - element z ktorego powstal aktualny
 * @param board - klasa z ulozeniem, jego id i przewidywana odlegloscia
 */
void insertNode (Node *openset, Node *parent, Board board)
{
    Node *fresh = new Node(board, parent);
    Node *looking = openset;
    while (!insertHere(fresh, looking))
        looking = looking->next;
    fresh->next = looking->next;
    looking->next = fresh;
}

/**
 * @brief Umieszcza nowy element na liscie elementow otwartych
 * @param openset - glowa listy elementow otwartych
 * @param closedset - glowa listy elementow zamknietych
 * @param luka - wspolzedne pustej plytki
 * @param obok_y - rzedna plytki obok pustej
 * @param obok_x - odcieta plytki obok pustej
 */
void moveMaker(Node *openset, Node *closedset, Point luka, int obok_y, int obok_x)
{
    Board board = openset->board.clone(luka, obok_y, obok_x);
    if (!(alreadyInside(openset, board.getId()) || alreadyInside(closedset, board.getId())))
        insertNode(openset, closedset, board);
}

/**
 * @brief tworzy liste z kolejnymi ulozeniami rozwiazania
 * @param openset - glowa listy elementow otwartych - tutaj juz ten z rozwiazaniem
 * @return glowa listy z kolejnymi krokami rozwiazania
 */
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

/**
 * @brief zwalnia pamiec zarezerwowana na liste
 * @param head - glowa listy do usuniecia
 */
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
