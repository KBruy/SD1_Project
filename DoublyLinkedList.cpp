#include <iostream>
#include "DoublyLinkedList.h"

using namespace std;

//================
// Konstruktor

DoublyLinkedList::DoublyLinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

//================
// Destruktor

DoublyLinkedList::~DoublyLinkedList()
{
    clear();
}

//================
// Gettery

int DoublyLinkedList::getSize()
{
    return size;
}

bool DoublyLinkedList::isEmpty()
{
    return size == 0;
}

//================
// Clear

void DoublyLinkedList::clear()
{
    Node* current = head;

    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}

//================
// Print

void DoublyLinkedList::print()
{
    cout << "Zawartosc listy: ";

    Node* current = head;
    while (current != nullptr)
    {
        cout << current->value << " ";
        current = current->next;
    }

    cout << endl;
    cout << "Size: " << size << endl;
    cout << endl;
}

//==========================================
//Operacje
void DoublyLinkedList::pushBack(int value)
{
    Node* newNode = new Node;     // tworzymy nowy wezel dynamicznie w pamieci
    newNode->value = value;       // wpisujemy wartosc
    newNode->next = nullptr;      // nowy element bedzie ostatni, wiec nie ma nastepnego
    newNode->prev = tail;         // poprzednim elementem nowego wezla jest stary tail

    // jesli lista jest pusta, nowy element jest jednoczesnie head i tail
    if (isEmpty())
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        // stary tail ma teraz wskazywac do przodu na nowy element
        tail->next = newNode;

        // przesuwamy tail na nowy ostatni element
        tail = newNode;
    }

    size++;
}

void DoublyLinkedList::pushFront(int value)
{
    Node* newNode = new Node;     // tworzymy nowy wezel dynamicznie w pamieci
    newNode->value = value;       // wpisujemy wartosc
    newNode->prev = nullptr;      // nowy element bedzie pierwszy, wiec nie ma poprzedniego
    newNode->next = head;         // nastepnym elementem nowego wezla jest stary head

    // jesli lista jest pusta, nowy element jest jednoczesnie head i tail
    if (isEmpty())
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        // stary head ma teraz wskazywac do tylu na nowy element
        head->prev = newNode;

        // przesuwamy head na nowy pierwszy element
        head = newNode;
    }

    size++;
}

int DoublyLinkedList::getValueAt(int index)
{
    // sprawdzamy, czy indeks jest poprawny
    if (index < 0 || index >= size)
    {
        cout << "Niepoprawny indeks!" << endl;
        return -1;
    }

    // zaczynamy od pierwszego elementu listy
    Node* current = head;

    // przechodzimy tyle krokow, ile wynosi indeks
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    // po petli current wskazuje na wezel o zadanym indeksie
    return current->value;
}

void DoublyLinkedList::insertAt(int index, int value)
{
    // sprawdzamy, czy indeks jest poprawny
    if (index < 0 || index > size)
    {
        cout << "Niepoprawny indeks!" << endl;
        return;
    }

    // jesli wstawiamy na poczatek, korzystamy z gotowej metody
    if (index == 0)
    {
        pushFront(value);
        return;
    }

    // jesli wstawiamy na koniec, korzystamy z gotowej metody
    if (index == size)
    {
        pushBack(value);
        return;
    }

    // szukamy wezla, ktory aktualnie stoi na pozycji index
    Node* current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    // tworzymy nowy wezel
    Node* newNode = new Node;
    newNode->value = value;

    // nowy wezel ma stanac pomiedzy current->prev i current
    newNode->prev = current->prev;
    newNode->next = current;

    // poprzedni element current ma teraz wskazywac do przodu na newNode
    current->prev->next = newNode;

    // current ma teraz wskazywac do tylu na newNode
    current->prev = newNode;

    size++;
}
void DoublyLinkedList::removeBack()
{
    // jesli lista jest pusta, nie ma czego usuwac
    if (isEmpty())
    {
        cout << "Lista jest pusta!" << endl;
        return;
    }

    // jesli lista ma tylko jeden element,
    // po usunieciu stanie sie pusta
    if (head == tail)
    {
        delete tail;
        head = nullptr;
        tail = nullptr;
        size = 0;
        return;
    }

    // zapamietujemy stary ostatni element
    Node* temp = tail;

    // przesuwamy tail na poprzedni element
    tail = tail->prev;

    // nowy ostatni element nie ma nastepnego
    tail->next = nullptr;

    // usuwamy stary ostatni wezel z pamieci
    delete temp;

    // zmniejszamy rozmiar listy
    size--;
}

void DoublyLinkedList::removeFront()
{
    // jesli lista jest pusta, nie ma czego usuwac
    if (isEmpty())
    {
        cout << "Lista jest pusta!" << endl;
        return;
    }

    // jesli lista ma tylko jeden element,
    // po usunieciu stanie sie pusta
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        size = 0;
        return;
    }

    // zapamietujemy stary pierwszy element
    Node* temp = head;

    // przesuwamy head na nastepny element
    head = head->next;

    // nowy pierwszy element nie ma poprzednika
    head->prev = nullptr;

    // usuwamy stary pierwszy wezel z pamieci
    delete temp;

    // zmniejszamy rozmiar listy
    size--;
}

void DoublyLinkedList::removeAt(int index)
{
    // sprawdzamy, czy indeks jest poprawny
    if (index < 0 || index >= size)
    {
        cout << "Niepoprawny indeks!" << endl;
        return;
    }

    // jesli usuwamy pierwszy element, korzystamy z gotowej metody
    if (index == 0)
    {
        removeFront();
        return;
    }

    // jesli usuwamy ostatni element, korzystamy z gotowej metody
    if (index == size - 1)
    {
        removeBack();
        return;
    }

    // szukamy wezla, ktory ma zostac usuniety
    Node* current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    // przepinamy poprzedni element tak, aby ominal current
    current->prev->next = current->next;

    // przepinamy nastepny element tak, aby ominal current
    current->next->prev = current->prev;

    // usuwamy wskazany wezel z pamieci
    delete current;

    // zmniejszamy liczbe elementow listy
    size--;
}

int DoublyLinkedList::searchRaw(int value)
{
    Node* current = head; // zaczynamy od pierwszego elementu listy
    int index = 0;        // licznik indeksu aktualnego wezla

    while (current != nullptr)
    {
        if (current->value == value)
        {
            return index; // znalezlismy wartosc, zwracamy indeks
        }

        current = current->next; // przechodzimy do nastepnego elementu
        index++;
    }

    return -1; // nie znaleziono wartosci
}

int DoublyLinkedList::search(int value)
{
    int index = searchRaw(value);

    if (index >= 0)
    {
        cout << "Znaleziono wartosc " << value << " na indeksie [" << index << "]" << endl;
    }
    else
    {
        cout << "Nie znaleziono indeksu dla wartosci " << value << endl;
    }

    return index;
}