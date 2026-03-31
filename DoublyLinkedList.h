#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

class DoublyLinkedList
{
private:
    struct Node
    {
        int value;
        Node* next;
        Node* prev;
    };

    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    int getSize();
    bool isEmpty();
    void print();
    void clear();
    int getValueAt(int index);

    void pushBack(int value);
    void pushFront(int value);
    void insertAt(int index, int value);

    void removeBack();
    void removeFront();
    void removeAt(int index);

    int searchRaw(int value);
    int search(int value);
};

#endif