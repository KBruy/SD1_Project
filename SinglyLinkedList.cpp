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

//=============================
//getValue (do wyszukiwania i wsadzania w odpowiednie miejsce)

int SinglyLinkedList::getValueAt(int index)
{
    // sprawdzamy czy indeks jest poprawny
    if (index < 0 || index >= size)
    {
        cout << "Niepoprawny indeks!" << endl;
        return -1;
    }

    Node* current = head; //pierwszy element listy

    //przechodzimy o tyle krokow i ile wynosi indeks
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current->value; //po zakonczeniu petli current wskazuje na wezel o podanym indeksie
}

//=========================================
//=========================================
//Operacje

void SinglyLinkedList::pushBack(int value)
{
    Node* newNode = new Node; // tworzymy nowy wezel dynamicznie w pamieci
    newNode->value = value;   // wpisujemy wartosc
    newNode->next = nullptr;  // nowy element bedzie ostatni, wiec nie ma nastepnego

    if (isEmpty())
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode; // stary ogon wskazuje na nowy element
        tail = newNode;       // przesuwamy tail na nowy ostatni element
    }

    size++;
}

void SinglyLinkedList::pushFront(int value)
{
    Node* newNode = new Node; //tworzymy nowy wezel dynamicznie
    newNode->value = value; // dodanie wartosci do nowego wezla

    // jesli lista jest pusta, nowy element bedzie jednoczesnie head i tail
    if (isEmpty()){
        newNode->next = nullptr;
        head = newNode;
        tail = newNode;
    }
    else
    {
        // nowy element ma wskazywac na stary poczatek listy
        newNode->next = head;

        // przesuwamy head na nowy pierwszy element
        head = newNode;
    }

    size++;
}

void SinglyLinkedList::insertAt(int index, int value)
{
    if (index < 0 || index > size)
    {
        cout << "Niepoprawny indeks!" << endl;
        return;

    }

    // jesli wstawiamy na poczatek 
    if (index == 0)
    {
        pushFront(value);
        return;
    }

    if (index == size)
    {
        pushBack(value);
        return;
    }

    Node* newNode = new Node;
    newNode->value = value;

    Node* current = head; //szukamy zadanego wezla, przed miejscem wstawienia
    for (int i = 0; i < index - 1; i++){
        current = current->next;
    }

    newNode->next = current->next; //nowy wezel ma wskazywac na element kroty byl do teraz po current
    current->next = newNode; //teraz ma wskazyac na nowy wezel

    size++;
    
}

