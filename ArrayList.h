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
        int getSize();  //geter zwracający liczbe elementow taba
        int getCapacity(); //geter zwracający pojemnosc taba
        void print(); //zwraca zawartość listy
        void pushBack(int value);
};

#endif