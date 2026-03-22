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
            {
                int count;

                cout << "Podaj rozmiar struktury: ";
                cin >> count;

                cout << "Podaj minimalna wartosc (standardowo 1): ";
                cin >> minRandomValue;

                cout << "Podaj maksymalna wartosc (standardowo 1000): ";
                cin >> maxRandomValue;

                if (count < 0 || minRandomValue > maxRandomValue)
                {
                    cout << "Niepoprawne dane!" << endl;
                    break;
                }

                arrayList.clear();
                srand(seed);

                for (int i = 0; i < count; i++)
                {
                    int value = generateRandomNumber(minRandomValue, maxRandomValue);
                    arrayList.pushBack(value);
                }

                cout<< "Utworzona losowa strukture" << endl;
                break;
            }

            case 2:
            {
                int value = generateRandomNumber(minRandomValue, maxRandomValue);
                arrayList.pushBack(value);

                cout<< "Dodano losowy element na koniec: "<< value <<endl;
                break;
            }

            case 3:
            {
                int value = generateRandomNumber(minRandomValue, maxRandomValue);
                arrayList.pushFront(value);

                cout<< "Dodano losowy element na poczatek: "<< value << endl;
                break;
            }

            case 4:
            {
                int value = generateRandomNumber(minRandomValue, maxRandomValue);
                int index = generateRandomNumber(0, arrayList.getSize());

                arrayList.insertAt(index, value);

                cout << "Dodano losowy element " << value << " na index " << index << endl;
                break;
            }

            case 5:
            {
                arrayList.removeBack();
                break;
            }
            case 6:
            {
                arrayList.removeFront();
                break;
            }

            case 7:
            {
                if (arrayList.isEmpty()){
                    cout << "Lista jest pusta!" << endl;
                    break;
                }

                int index = generateRandomNumber(0, arrayList.getSize() - 1);
                arrayList.removeAt(index);

                cout << "Usunieto element z losowego indeksu: " << index << endl;
                break;
            }

            case 8:
            {
                if (arrayList.isEmpty())
                {
                    cout << "Lista jest pusta!" << endl;
                    break;
                }

                int randomIndex = generateRandomNumber(0, arrayList.getSize() - 1);
                int value = arrayList.getValueAt(randomIndex);

                cout << "Losowo wybrano indeks: " << randomIndex
                     << ", wartosc do wyszukania: " << value << endl;
                int foundIndex = arrayList.search(value);
                cout << "Wynik wyszukiwania (indeks): " << foundIndex << endl;

                break;
            }

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