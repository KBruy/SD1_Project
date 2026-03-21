#ifndef ARRAYLIST_H
#define ARRAYLIST_H

class ArrayList {

    private:
        int* data; //wskaźnik na tabilce
        int size;  //licba obecnych elementów w tablicy [index]
        int capacity; //pojemność tablicy [value]

        void resize(); //metoda "powiększania" tablicy 

    public:
        ArrayList();
        ~ArrayList();

        //info metody
        int getSize();  //geter zwracający liczbe elementow taba
        int getCapacity(); //geter zwracający pojemnosc taba
        void print(); //zwraca zawartość listy, rozmiar i pojemność

        //metody wykonywalne
        void pushBack(int value); //dodawanie elementu na koniec tablicy
        void pushFront(int value); //dodawanie elemntu na początek tablicy (przesuwanie w prawo)
        void insertAt(int index, int value); //dodawanie zadanej wartości na zadany index tablicy

};

#endif