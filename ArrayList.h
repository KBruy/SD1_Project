#ifndef ARRAYLIST_H
#define ARRAYLIST_H

class ArrayList {

    private:
        int* data;
        int size;
        int capacity;

        void resize(); //metoda "powiększania" tablicy 

    public:
        ArrayList();
        ~ArrayList();
        int getSize();  //geter zwracający liczbe elementow taba
        int getCapacity(); //geter zwracający pojemnosc taba
        void print();
};

#endif