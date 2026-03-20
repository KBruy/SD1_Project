#ifndef ARRAYLIST_H
#define ARRAYLIST_H

class ArrayList {

    private:
        int* data;
        int size;
        int capacity;

    public:
        ArrayList();
        ~ArrayList();
};

#endif