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

    void showMainMenu(); //metoda pokazywania głównego menu
    void showArrayListMenu(); //metoda pokazywania opcji dla tablicy dynamicznej

    void handleArrayListMenu(); //metoda obsługująca tablice dynamiczną

    public:
    void run(); //start programu
};

#endif