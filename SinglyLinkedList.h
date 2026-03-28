#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

class SinglyLinkedList
{
    private:
        struct Node
        {
            int value;
            Node* next;
        };

        Node* head;
        Node* tail;
        int size;

    public: 
        SinglyLinkedList();
       ~SinglyLinkedList();
       
       int getSize();
       bool isEmpty();
       void print();
       void clear();
        
};

#endif