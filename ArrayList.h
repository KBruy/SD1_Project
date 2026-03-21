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
        bool isEmpty(); //zwraca true jeżeli tablica jest pusta

        //metody dodające do tablicy
        void pushBack(int value); //dodawanie elementu na koniec tablicy
        void pushFront(int value); //dodawanie elemntu na początek tablicy (przesuwanie w prawo)
        void insertAt(int index, int value); //dodawanie zadanej wartości na zadany index tablicy

        //metody usuwające z tablicy 
        void removeBack(); //usuwa ostatni element z tablicy
        void removeFront(); //usuwa pierwszy element z tablicy (przesuwanie w lewo)
        void removeAt(int index); //usuwa element z zadanego indexu


        int search(int value); //szuka zadaną wartość, przy znalezieniu zwraca index, przy jej braku w strukturze zwraca -1
        int searchResult(int index, int value);


};

#endif