#include <iostream>
#include <cstdlib>
#include "Menu.h"
#include <string>

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
                handleSinglyLinkedListMenu();
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

//=============================================
// Tablica dynamiczna

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
 cout << "11. Menu pomiarow" << endl;
 cout << "12. Powrot do menu glownego" << endl;
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

                cout << "Podaj minimalna wartosc (standardowo 0): ";
                cin >> minRandomValue;

                cout << "Podaj maksymalna wartosc (standardowo 16777215): ";
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
                
                randomStructureCreated = true;
                cout<< "Utworzona losowa strukture" << endl;
                break;
            }

            case 2:
            {

                if (!randomStructureCreated)
                    {
                    cout << "Najpierw utworz losowa strukture!" << endl;
                    break;
                }

                int value = generateRandomNumber(minRandomValue, maxRandomValue);
                arrayList.pushBack(value);

                cout<< "Dodano losowy element na koniec: "<< value <<endl;
                break;
            }

            case 3:
            {
                if (!randomStructureCreated)
                    {
                    cout << "Najpierw utworz losowa strukture!" << endl;
                    break;
                }
                
                int value = generateRandomNumber(minRandomValue, maxRandomValue);
                arrayList.pushFront(value);

                cout<< "Dodano losowy element na poczatek: "<< value << endl;
                break;
            }

            case 4:
            {

                if (!randomStructureCreated)
                    {
                    cout << "Najpierw utworz losowa strukture!" << endl;
                    break;
                }

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

                if (!randomStructureCreated)
                    {
                    cout << "Najpierw utworz losowa strukture!" << endl;
                    break;
                }

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

                if (!randomStructureCreated)
                    {
                    cout << "Najpierw utworz losowa strukture!" << endl;
                    break;
                }

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
                randomStructureCreated = false;
                cout << "Struktura zostala wyczyszczona." <<endl;
                break;

            case 11:
            {
                handleResearchMenu();
                break;
            }

            case 12:
                cout << "Powrot do menu glownego." << endl;
                break;

            default:
                cout << "Niepoprawna opcja!" << endl;
                break;
        }
    } while (choice != 12);
    
}

void Menu::showResearchMenu()
{
    cout << endl;
    cout << "==== Menu Pomiarow: ArrayList ====" << endl;
    cout << "1. Zmierz pushBack" << endl;
    cout << "2. Zmierz pushFront" << endl;
    cout << "3. Zmierz insertAt" << endl;
    cout << "4. Zmierz removeBack" << endl;
    cout << "5. Zmierz removeFront" << endl;
    cout << "6. Zmierz removeAt" << endl;
    cout << "7. Zmierz search" << endl;
    cout << "8. Powrot do menu tablicy dynamicznej" << endl;
    cout << "----> ";
}

void Menu::handleResearchMenu()
{
    int choice;

    do
    {
        showResearchMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int size;
            int seriesCount;
            string fileName;

            cout << "Podaj rozmiar poczatkowoy struktury: ";
            cin >> size;

            cout << "Podaj liczbe serii: ";
            cin >> seriesCount;

            cout << "Podaj nazwe pliku txt: ";
            cin >> fileName;

            if (size < 0 || seriesCount <= 0)
            {
                cout << "Niepoprawne dane!" << endl;
                break;
            }

            research.measureArrayListPushBack(size, seriesCount, seed, minRandomValue, maxRandomValue, fileName);
            break;
        }

        case 2:
        {
            int size;
            int seriesCount;
            string fileName;

            cout << "Podaj rozmiar poczatkowy struktury: ";
            cin >> size;

            cout << "Podaj liczbe serii: ";
            cin >> seriesCount;

            cout << "Podaj nazwe pliku txt: ";
            cin >> fileName;

            if (size < 0 || seriesCount <= 0)
            {
                cout << "Niepoprawne dane!" << endl;
                break;
            }

            research.measureArrayListPushFront(size, seriesCount, seed,
                                       minRandomValue, maxRandomValue, fileName);
            break;
        }

        case 3:
        {
            int size;
            int seriesCount;
            string fileName;

            cout << "Podaj rozmiar poczatkowy struktury: ";
            cin >> size;

            cout << "Podaj liczbe serii: ";
            cin >> seriesCount;

            cout << "Podaj nazwe pliku txt: ";
            cin >> fileName;

            if (size < 0 || seriesCount <= 0)
            {
                cout << "Niepoprawne dane!" << endl;
                break;
            }

            research.measureArrayListInsertAt(size, seriesCount, seed, minRandomValue, maxRandomValue, fileName);
            break;
        }
        
        case 4:
        {
            int size;
            int seriesCount;
            string fileName;

            cout << "Podaj rozmiar poczatkowy struktury: ";
            cin >> size;

            cout << "Podaj liczbe serii: ";
            cin >> seriesCount;

            cout << "Podaj nazwe pliku txt: ";
            cin >> fileName;

            if (size <= 0 || seriesCount <= 0)
            {
                cout << "Niepoprawne dane!" << endl;
                break;
            }

            research.measureArrayListRemoveBack(size, seriesCount, seed, minRandomValue, maxRandomValue, fileName);
            break;
        }
        
        case 5:
        {
            int size;
            int seriesCount;
            string fileName;

            cout << "Podaj rozmiar poczatkowy struktury: ";
            cin >> size;

            cout << "Podaj liczbe serii: ";
            cin >> seriesCount;

            cout << "Podaj nazwe pliku txt: ";
            cin >> fileName;

            if (size <= 0 || seriesCount <= 0)
            {
                cout << "Niepoprawne dane!" << endl;
                break;
            }

            research.measureArrayListRemoveFront(size, seriesCount, seed,
                                                minRandomValue, maxRandomValue, fileName);
            break;
        }
        
        case 6:
        {
            int size;
            int seriesCount;
            string fileName;

            cout << "Podaj rozmiar poczatkowy struktury: ";
            cin >> size;

            cout << "Podaj liczbe serii: ";
            cin >> seriesCount;

            cout << "Podaj nazwe pliku txt: ";
            cin >> fileName;

            if (size <= 0 || seriesCount <= 0)
            {
                cout << "Niepoprawne dane!" << endl;
                break;
            }

            research.measureArrayListRemoveAt(size, seriesCount, seed, minRandomValue, maxRandomValue, fileName);
            break;
        }
        
        case 7:
        {
            int size;
            int seriesCount;
            string fileName;

            cout << "Podaj rozmiar poczatkowy struktury: ";
            cin >> size;

            cout <<"Podaj liczbe serii: ";
            cin >> seriesCount;

            cout <<"Podaj nazwe pliku txt: ";
            cin >> fileName;

            if (size <= 0 || seriesCount <=0)
            {
                cout << "Niepoprawne dane!" << endl;
                break;
            }

            research.measureArrayListSearch(size, seriesCount, seed, minRandomValue, maxRandomValue, fileName);
            break;
        }
        
        case 8:
        {
            cout << "Powrot do menu tablicy dynamicznej." << endl;
            break;
        }          
        

        default:
        cout << "Niepoprawna opcja!" << endl;
            break;
        }
    } while (choice != 8);
    
}

//===============================================================
//Lista jednokierunkowa

void Menu::showSinglyLinkedListMenu()
{
    cout << endl;
    cout << "=== Lista Jednokierunkowa ===" << endl;
    cout << "1. Utworz losowa strukture" << endl;
    cout << "2. Dodaj element na koniec" << endl;
    cout << "3. Wyswietl liste" << endl;
    cout << "4. Wyczysc strukture" << endl;
    cout << "5. Powrot do menu glownego" << endl;
    cout << "---> ";
}

void Menu::handleSinglyLinkedListMenu()
{
    int choice;
    bool randomStructureCreated = false;
    
    do
    {
        
        showSinglyLinkedListMenu();
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
            int count;
            cout << "Podaj rozmiar struktury: ";
            cin >> count;

            cout <<"Podaj minimalna wartosc (standardowo 0): ";
            cin >> minRandomValue;

            cout << "Podaj maksymalna wartosc (standardowo 16777215): ";
            cin >> maxRandomValue;

            if (count < 0 || minRandomValue > maxRandomValue)
            {
                cout << "Niepoprawne dane!" << endl;
                break;
            }

            singlyLinkedList.clear();
            srand(seed);

            for (int i = 0; i < count; i++)
            {
                int value = generateRandomNumber(minRandomValue, maxRandomValue);
                singlyLinkedList.pushBack(value);
            }

            randomStructureCreated = true;
            cout << "Utworzono losowa strukture." << endl;
            break;
        }

        case 2:
        {
            if (!randomStructureCreated)
            {
                cout << "Najpierw utworz losowa strukture!" <<endl;
                break;
            }

            int value = generateRandomNumber(minRandomValue, maxRandomValue);
            singlyLinkedList.pushBack(value);

            cout << "Dodano losowy element na koniec: " << value << endl;
            break;
        }

        case 3:
        {
            singlyLinkedList.print();
            break;
        }

        case 4:
        {
            singlyLinkedList.clear();
            randomStructureCreated = false;
            cout << "Struktura zostala wyczyszczona" <<endl;
            break;
        }

        case 5:
        {
            cout << "Powrot do menu glownego" << endl;
            break;
        }

        default:
        {
            cout <<"Niepoprawna opcja!" << endl;
            break;
        }

        }

    } while (choice != 5);
    
}