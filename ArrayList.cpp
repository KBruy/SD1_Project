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

void ArrayList::pushBack(int value)
{
    if (size == capacity)
    {
        resize();
    }

    data[size] = value;
    size++;
}

void ArrayList::pushFront(int value)
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

void ArrayList::insertAt(int index, int value)
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