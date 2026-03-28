#include <iostream>
#include "ArrayList.h"

using namespace std;


ArrayList::ArrayList() //konstruktor
{
    capacity = 4;
    size = 0;
    data = new int[capacity];
}

ArrayList::~ArrayList() //destruktor
{
    delete[] data;
}

int ArrayList::getSize() //geter zwracający liczbe elementow taba
{
    return size;
}

int ArrayList::getCapacity() //geter zwracający pojemnosc taba
{
    return capacity;
}

void ArrayList::print() //zwraca zawartość listy
{
    cout <<"Zawartość listy: ";
    for (int i = 0; i < size; i++){
        cout << data[i] << " ";
    }
    cout<<endl;

    cout << "Size: " << getSize() << endl;
    cout << "Capacity: " << getCapacity() << endl;

    cout << endl;
}

bool ArrayList::isEmpty()
{
    return size == 0;
}

void ArrayList::clear()
{
    size = 0;
}

int ArrayList::getValueAt(int index)
{
    if (index < 0 || index >= size)
    {
        cout << "Niepoprawny indeks!" << endl;
        return -1;
    }

    return data[index];
}

//==========================================
// Metody dodające

void ArrayList::resize()
{
    int newCapacity = capacity * 2;
    int* newData = new int[newCapacity];

    for (int i = 0; i < size; i++) //pętla kopiująca
    {
        newData[i] = data[i];

    }

    delete[] data;
    data = newData; //wskaźnik na tablice wskazuje na nową tablicę
    capacity = newCapacity;
}

void ArrayList::pushBack(int value) //dodawanie elementu na koniec tablicy
{
    if (size == capacity)
    {
        resize();
    }

    data[size] = value;
    size++;
}

void ArrayList::pushFront(int value) //dodawanie elemntu na początek tablicy (przesuwanie w prawo)
{
    if (size == capacity)
    {
        resize();
    }

    for (int i = size; i > 0; i--)
    {
        data[i] = data[i-1];    //dla tab o size 3 -> data[2] przesuwamy do data[3] itd.

    }

    data[0] = value;
    size++;
}

void ArrayList::insertAt(int index, int value) //dodawanie zadanej wartości na zadany index tablicy
{
    if (index < 0 || index > size){
        cout << "Niepoprawny indeks!" << endl;
        return;
    }

    if (size == capacity)
    {
        resize();
    }

    for (int i = size; i > index; i--) //przesuwamy elementy w prawo do indexu w którym chcemy dodać wartość
    {
        data[i] = data[i-1];
    }

    data[index] = value;
    size++;
}

//===================================
// Metody usuwające

void ArrayList::removeBack() //usuwa ostatni element listy
{
    if (isEmpty())
    {
        cout<< "Lista jest pusta!" << endl;
        return;
    }

    size--;
}

void ArrayList::removeFront() //usuwa pierwszy element listy
{
    if (isEmpty()){
        cout<<"Lista jest pusta!" << endl;
        return;
    }

    for (int i = 0; i < size - 1; i++){ //size - 1 żeby nie brać wartości nieistniejącego elementu
        data[i] = data[i + 1];   //każdy element bierze wartość swojego prawego sąsiada, wartość pierwszego nie jest zapamiętywana
    }

    size--; //usuwamy ostatni (zdublowany element)
}

void ArrayList::removeAt(int index)
{
    if (index < 0 || index >= size)
    {
        cout << "Niepoprawny indeks!" << endl;
        return;
    }

    for (int i = index; i < size - 1; i++){  //zaczynamy od miejsca które usuwamy
        data[i] = data[i+1];                     //wszystko na prawo od usuwanego elementu przesuwamy o 1 w lewo
    }

    size--;
}

//=============================
int ArrayList::search(int value)
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] == value)
        {
            return ArrayList::searchResult(i, value);
        }
    }

    return ArrayList::searchResult(-1, value);
}

int ArrayList::searchResult(int index, int value)
{
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

int ArrayList::searchRaw(int value)
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] == value)
        {
            return i;
        }
    }

    return -1;
}