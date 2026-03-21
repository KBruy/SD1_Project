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

int ArrayList::getSize()
{
    return size;
}

int ArrayList::getCapacity()
{
    return capacity;
}

void ArrayList::print()
{
    cout <<"Zawartość listy: ";
    for (int i = 0; i < size; i++){
        cout << data[i] << " ";
    }

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