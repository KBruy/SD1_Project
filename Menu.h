#ifndef MENU_H
#define MENU_H

#include "ArrayList.h"

class Menu
{
    private:
    unsigned int seed = 12345;
    int minRandomValue = 0;
    int maxRandomValue = 16777215;
    ArrayList arrayList; //obiekt tablicy dynamicznej

    bool randomStructureCreated = false; // flaga, dla false - nie utworzono jeszcze sensownej losowej struktury
                                        // dla true - struktura została już przygotowana przez opcję tworzenia losowej struktury
                                        // zabezpieczenie przed operacjami na niechcianych strukturach

    void showMainMenu(); //metoda pokazywania głównego menu
    void showArrayListMenu(); //metoda pokazywania opcji dla tablicy dynamicznej

    void handleArrayListMenu(); //metoda obsługująca tablice dynamiczną

    public:
    void run(); //start programu
};

#endif