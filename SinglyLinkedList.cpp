#include <iostream>
#include "SinglyLinkedList.h"

using namespace std;

//================
//Konstruktor

SinglyLinkedList::SinglyLinkedList()
{
    head = nullptr; //lista jest pusta
    tail = nullptr;
    size = 0;
}

//================
//Destruktor

SinglyLinkedList::~SinglyLinkedList()
{
    clear();
}

//===================
//Getery

int SinglyLinkedList::getSize()
{
    return size;
}

bool SinglyLinkedList::isEmpty()
{
    return size == 0;
}

//===================
//Clear

void SinglyLinkedList::clear()
{
    Node* current = head;

    while (current != nullptr)//idziemy do końca listy
    {
        Node* next = current->next; //zapamietujemy nastepny element
        delete current; //usuwamy obecny
        current = next; //przechodzimy dalej
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}

//======================
//Print
void SinglyLinkedList::print()
{
    cout << "Zawartosc listy: ";
    Node* current = head; //pierwszy element

    while (current != nullptr)
    {
        cout << current->value << " ";
        current = current->next;
    }

    cout << endl;
    cout << "Size: " << size << endl;
    cout << endl;
}

//=========================================
//=========================================
//Operacje

void SinglyLinkedList::pushBack(int value)
{
    Node* newNode = new Node; //tworzymy nowy węzeł dynamicznie w pamięci i zwracamy adres do tego węzła
    newNode->value = value; //wpisujemy do niego wartosc
    newNode->next = nullptr; //to ostatni element listy więc nie bedzie następnego

    if (isEmpty())
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode; //ogon wskazuje na nowy ostatni element
    }

    size++;
}