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

void Research::measureArrayListPushBack(int size, int seriesCount, unsigned int baseSeed,
                                        int minValue, int maxValue, const string& fileName)
{
    if (size < 0 || seriesCount <= 0 || minValue > maxValue)
    {
        cout << "Niepoprawne parametry pomiaru!" << endl;
        return;
    }

    ofstream file(fileName, ios::app);
    if (!file.is_open())
    {
        cout << "Nie udalo sie otworzyc pliku!" << endl;
        return;
    }

    long long totalTime = 0;
    const int copiesPerSeries = 10;

    file << "==========================" << endl;
    file << "Struktura: ArrayList" << endl;
    file << "Operacja: pushBack" << endl;
    file << "Tryb pomiaru: pushBack z wymuszonym resize()" << endl;
    file << "Rozmiar poczatkowy zadany przez uzytkownika: " << size << endl;
    file << "Liczba serii: " << seriesCount << endl;
    file << "Seed bazowy: " << baseSeed << endl;
    file << "Zakres losowania: [" << minValue << ", " << maxValue << "]" << endl;
    file << "Liczba kopii w serii: " << copiesPerSeries << endl;
    file << endl;

    for (int i = 0; i < seriesCount; i++)
    {
        unsigned int currentSeed = baseSeed + i;

        ArrayList** lists = new ArrayList*[copiesPerSeries];
        int* preparedValues = new int[copiesPerSeries];

        for (int j = 0; j < copiesPerSeries; j++)
        {
            lists[j] = new ArrayList();

            // 1. Budujemy bazową strukturę do rozmiaru "size"
            prepareArrayList(*lists[j], size, currentSeed, minValue, maxValue);

            // 2. Dopychamy ją do pełnej pojemności, żeby następny pushBack zrobił resize()
            while (lists[j]->getSize() < lists[j]->getCapacity())
            {
                int fillValue = generateRandomNumber(minValue, maxValue);
                lists[j]->pushBack(fillValue);
            }

            // 3. Przygotowujemy wartość do jednej mierzonej operacji
            preparedValues[j] = generateRandomNumber(minValue, maxValue);
        }

        auto start = chrono::steady_clock::now();

        for (int j = 0; j < copiesPerSeries; j++)
        {
            lists[j]->pushBack(preparedValues[j]);
        }

        auto stop = chrono::steady_clock::now();

        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
        double oneOperationTime = static_cast<double>(duration) / copiesPerSeries;
        totalTime += duration;

        file << "Seria " << i + 1 << ": " << oneOperationTime << " ns/op" << endl;

        for (int j = 0; j < copiesPerSeries; j++)
        {
            delete lists[j];
        }

        delete[] lists;
        delete[] preparedValues;
    }

    double averageTime = static_cast<double>(totalTime) / (seriesCount * copiesPerSeries);

    file << endl;
    file << "Sredni czas: " << averageTime << " ns/op" << endl;
    file << "==========================" << endl << endl;

    file.close();

    cout << "Zakonczono pushBack z resize()." << endl;
    cout << "Sredni czas: " << averageTime << " ns/op" << endl;
    cout << "Wyniki zapisano do pliku: " << fileName << endl;
}