#ifndef MENU_H
#define MENU_H

#include "ArrayList.h"
#include "Research.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

class Menu
{
    private:
    unsigned int seed = 12345;
    int minRandomValue = 0;
    int maxRandomValue = 16777215;
    ArrayList arrayList; //obiekt tablicy dynamicznej
    Research research; //obiekt badan

    //Lista dwukierunkowa
    DoublyLinkedList doublyLinkedList;
    bool randomDoublyStructureCreated = false;

    SinglyLinkedList singlyLinkedList; //obiekt listy jednokierunkowej

    void showMainMenu(); //metoda pokazywania głównego menu

    //===============================
    //Tablica dynamiczna
    void showArrayListMenu(); //metoda pokazywania opcji dla tablicy dynamicznej
    void handleArrayListMenu(); //metoda obsługująca tablice dynamiczną

    //================================
    //Lista jednokierunkowa
    bool randomSinglyStructureCreated = false;
    void showSinglyLinkedListMenu();
    void handleSinglyLinkedListMenu();

    //=================================
    //Lista dwukierunkowa
    void showDoublyLinkedListMenu();
    void handleDoublyLinkedListMenu();
    bool randomStructureCreated = false;

     //badania
    void showResearchMenu();
    void handleResearchMenu();

    void showSinglyResearchMenu();
    void handleSinglyResearchMenu();

    public:
    void run(); //start programu
};

#endif