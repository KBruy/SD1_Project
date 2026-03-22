#include <iostream>
#include "Menu.h"

using namespace std;

void Menu::showMainMenu()
{
    cout<< endl;
    cout << "======== Wybór Struktury ========"<<endl;
    cout << "1. Tablica dynamiczna" <<endl;
    cout << "2. Lista jednokierunkowa" <<endl;
    cout << "3. Lista dwukierunkowa" << endl;
    cout << "4. Zakoncz program" << endl;
    cout << "----> ";
}

void Menu::run()
{
    int choice;

    do
    {
        showMainMenu();
        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "Wybrano tablice dynamiczna." << endl;
                showArrayListMenu();
                break;
            case 2:
                cout << "not yet" << endl;
                break;
            case 3:
                cout << "not yet" << endl;
                break;
            case 4:
                cout << "Koniec" << endl;
                break;
            default:
                cout << "Niepoprawna opcja!" << endl;
                break;
            
        }
    } while (choice !=4);
    
}

void Menu::showArrayListMenu()
{
 cout << endl;
 cout << "==== Tablica Dynamiczna ====" << endl;
 cout << "1. Dodaj element na koniec" << endl;
 cout << "2. Dodaj element na poczatek" << endl;
 cout << "3. Dodaj element na wybrany indeks" << endl;
 cout << "4. Usun element z konca" << endl;
 cout << "5. Usun element z poczatku" << endl;
 cout << "6. Usun element z wybranego indeksu" << endl;
 cout << "7. Wyszukaj losowa wartosc" << endl;
 cout << "8. Wyswietl liste" << endl;
 cout << "9. Powrot do menu glownego" << endl;
 handleArrayListMenu();
}

void Menu::handleArrayListMenu()
{
    int choice;

    do
    {
        
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Opcja 1" << endl;
                break;

            case 2:
                cout << "Opcja 2" << endl;
                break;

            case 3:
                cout << "Opcja 3" << endl;
                break;

            case 4:
                cout << "Opcja 4" << endl;
                break;

            case 5:
                cout << "Opcja 5" << endl;
                break;

            case 6:
                cout << "Opcja 6" << endl;
                break;

            case 7:
                cout << "Opcja 7" << endl;
                break;

            case 8:
                arrayList.print();
                break;

            case 9:
                cout << "Powrot do menu glownego." << endl;
                break;

            default:
                cout << "Niepoprawna opcja!" << endl;
                break;
        }
    } while (choice != 9);
    
}