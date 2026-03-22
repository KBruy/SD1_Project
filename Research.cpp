#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include "Research.h"

using namespace std;

int Research::generateRandomNumber(int minValue, int maxValue)
{
    return minValue + rand() % (maxValue - minValue + 1);
}

void Research::prepareArrayList(ArrayList& list, int size, unsigned int seed, int minValue, int maxValue)
{
    list.clear();
    srand(seed);

    for (int i = 0; i < size; i++){
        int value = generateRandomNumber(minValue, maxValue);
        list.pushBack(value);
    }
} //czyścimy strukturę przed nową serią aby startować od świeżo przygotowanej tablicy

void Research::measureArrayListPushBack(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const string& fileName)
{
    ofstream file(fileName, ios::app);
    if (!file.is_open())
    {
        cout << "Nie udalo sie otworzyc pliku!" << endl;
        return;
    }

    ArrayList list; // struktura lokalna do badań, nie chcemy mieć tej z menu
    long long totalTime = 0; //suma wszystkich czasów serii

    file << "=========================="<<endl;
    file << "Struktra: ArrayList" << endl;
    file << "Operacja: pushBack" << endl;
    file << "Rozmiar poczatkowy: " << size << endl;
    file << "Liczba serii: " << seriesCount << endl;
    file << "Seed bazowy: " << baseSeed << endl;
    file << "Zakres losowania: [" << minValue << ", " << maxValue << "]" << endl;
    file << endl;

    for (int i = 0; i < seriesCount; i++)
    {
        unsigned int currentSeed = baseSeed + i;
        prepareArrayList(list, size, currentSeed, minValue, maxValue); //budujemy bazwoą strukturę przed pomiarem
        int value = generateRandomNumber(minValue, maxValue);
        auto start = chrono::high_resolution_clock::now();
        list.pushBack(value);
        auto stop = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count(); //przeliczenie na nanosekundy
        totalTime += duration;

        file << "Seria " << i + 1 << ": " << duration << "ns" <<endl;

    }

    double averageTime = (double)totalTime / seriesCount; //srednia ze wszystkich serii

    file << endl;
    file << "Sredni czas: " << averageTime << "ns" << endl;
    file << "=============";

    cout << "Zakonczono pushBack." << endl;
    cout << "Sredni czas: " << averageTime << "ns" << endl;
    cout << "Wyniki zapisano do pliku: " << fileName << endl;


}