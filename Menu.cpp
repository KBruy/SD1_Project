#include <iostream>
#include <cstdlib>
#include "Menu.h"

using namespace std;

int generateRandomNumber(int minValue, int maxValue)
{
    return minValue + rand() % (maxValue - minValue + 1);
}

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
                handleArrayListMenu();
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
 cout << "1. Utworz losowa strukute" <<endl;
 cout << "2. Dodaj element na koniec" << endl;
 cout << "3. Dodaj element na poczatek" << endl;
 cout << "4. Dodaj element na wybrany indeks" << endl;
 cout << "5. Usun element z konca" << endl;
 cout << "6. Usun element z poczatku" << endl;
 cout << "7. Usun element z wybranego indeksu" << endl;
 cout << "8. Wyszukaj losowa wartosc" << endl;
 cout << "9. Wyswietl liste" << endl;
 cout << "10. Wyczysc strukture" << endl;
 cout << "11. Powrot do menu glownego" << endl;
 cout << "---> ";
}

void Menu::handleArrayListMenu()
{
    int choice;

    do
    {
        showArrayListMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                int count;
                int minValue;
                int maxValue;

                cout << "Podaj rozmiar struktury: ";
                cin >> count;

                cout << "Podaj minimalna wartosc: ";
                cin >> minValue;

                cout << "Podaj maksymalna wartosc: ";
                cin >> maxValue;

                if (count < 0 || minValue > maxValue)
                {
                    cout << "Niepoprawne dane!" << endl;
                    break;
                }

                arrayList.clear();
                srand(seed);

                for (int i = 0; i < count; i++)
                {
                    int value = generateRandomNumber(minValue, maxValue);
                    arrayList.pushBack(value);
                }

                cout<< "Utworzona losowa strukture" << endl;
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
                cout << "Opcja 7" << endl;
                break;

            case 9:
                arrayList.print();
                break;

            case 10:
                arrayList.clear();
                cout << "Struktura zostala wyczyszczona." <<endl;
                break;

            case 11:
                cout << "Powrot do menu glownego." << endl;
                break;

            default:
                cout << "Niepoprawna opcja!" << endl;
                break;
        }
    } while (choice != 11);
    
}