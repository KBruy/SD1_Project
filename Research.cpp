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

//========================================================================================================================
// Formatka do pisania raportów

void Research::writeReportHeader(ofstream& file, const string& operationName,
                                 const string& measurementMode, int size, int seriesCount,
                                 unsigned int baseSeed, int minValue, int maxValue, int copiesPerSeries)
{
    file << "==========================" << endl;
    file << "Struktura: ArrayList" << endl;
    file << "Operacja: " << operationName << endl;
    file << "Tryb pomiaru: " << measurementMode << endl;
    file << "Rozmiar poczatkowy: " << size << endl;
    file << "Liczba serii: " << seriesCount << endl;
    file << "Seed bazowy: " << baseSeed << endl;
    file << "Zakres losowania: [" << minValue << ", " << maxValue << "]" << endl;
    file << "Liczba kopii w serii: " << copiesPerSeries << endl;
    file << endl;
}

void Research::writeReportFooter(ofstream& file, double averageTime)
{
    file << endl;
    file << "Sredni czas: " << averageTime << " ns/op" << endl;
    file << "==========================" << endl << endl;
}

ArrayList** Research::createArrayListCopies(int copiesPerSeries, int size, unsigned int seed,
                                            int minValue, int maxValue)
{
    ArrayList** lists = new ArrayList*[copiesPerSeries];

    for (int j = 0; j < copiesPerSeries; j++)
    {
        lists[j] = new ArrayList();
        prepareArrayList(*lists[j], size, seed, minValue, maxValue);
    }

    return lists;
}

void Research::deleteArrayListCopies(ArrayList** lists, int copiesPerSeries)
{
    for (int j = 0; j < copiesPerSeries; j++)
    {
        delete lists[j];
    }

    delete[] lists;
}

int* Research::prepareRandomValues(int count, int minValue, int maxValue)
{
    int* values = new int[count];

    for (int i = 0; i < count; i++)
    {
        values[i] = generateRandomNumber(minValue, maxValue);
    }

    return values;
}

//=========================================================================================================
// Pomiary operacji

//PushBack

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
    const int copiesPerSeries = 100;

    writeReportHeader(file, "pushBack",
                      "jedno pushBack na kazdej z identycznych kopii",
                      size, seriesCount, baseSeed, minValue, maxValue, copiesPerSeries);

    for (int i = 0; i < seriesCount; i++)
    {
        unsigned int currentSeed = baseSeed + i;

        ArrayList** lists = createArrayListCopies(copiesPerSeries, size, currentSeed, minValue, maxValue);
        int* preparedValues = prepareRandomValues(copiesPerSeries, minValue, maxValue);

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

        deleteArrayListCopies(lists, copiesPerSeries);
        delete[] preparedValues;
    }

    double averageTime = static_cast<double>(totalTime) / (seriesCount * copiesPerSeries);

    writeReportFooter(file, averageTime);
    file.close();

    cout << "Zakonczono pomiar pushBack." << endl;
    cout << "Sredni czas: " << averageTime << " ns/op" << endl;
    cout << "Wyniki zapisano do pliku: " << fileName << endl;
}

// PushFront

void Research::measureArrayListPushFront(int size, int seriesCount, unsigned int baseSeed,
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
    const int copiesPerSeries = 100;

    writeReportHeader(file, "pushFront",
                      "jedno pushFront na kazdej z identycznych kopii",
                      size, seriesCount, baseSeed, minValue, maxValue, copiesPerSeries);

    for (int i = 0; i < seriesCount; i++)
    {
        unsigned int currentSeed = baseSeed + i;

        ArrayList** lists = createArrayListCopies(copiesPerSeries, size, currentSeed, minValue, maxValue);
        int* preparedValues = prepareRandomValues(copiesPerSeries, minValue, maxValue);

        auto start = chrono::steady_clock::now();

        for (int j = 0; j < copiesPerSeries; j++)
        {
            lists[j]->pushFront(preparedValues[j]);
        }

        auto stop = chrono::steady_clock::now();

        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
        double oneOperationTime = static_cast<double>(duration) / copiesPerSeries;
        totalTime += duration;

        file << "Seria " << i + 1 << ": " << oneOperationTime << " ns/op" << endl;

        deleteArrayListCopies(lists, copiesPerSeries);
        delete[] preparedValues;
    }

    double averageTime = static_cast<double>(totalTime) / (seriesCount * copiesPerSeries);

    writeReportFooter(file, averageTime);
    file.close();

    cout << "Zakonczono pomiar pushFront." << endl;
    cout << "Sredni czas: " << averageTime << " ns/op" << endl;
    cout << "Wyniki zapisano do pliku: " << fileName << endl;
}

// InsertAt

void Research::measureArrayListInsertAt(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const string& fileName)
{
    if (size < 0 || seriesCount <= 0 || minValue > maxValue)
    {
        cout << "Niepoprawne parametry pomiaru! " << endl;
        return;
    }

    ofstream file(fileName, ios::app);
    if (!file.is_open())
    {
        cout << "Nie udalo sie otworzyc pliku" << endl;
        return;
    }

    long long totalTime = 0;
    const int copiesPerSeries = 100;

    writeReportHeader(file, "insertAt",
                      "jedno insertAt na kazdej z identycznych kopii, indeks losowy",
                      size, seriesCount, baseSeed, minValue, maxValue, copiesPerSeries);

    for (int i = 0; i < seriesCount; i++)
    {
        unsigned int currentSeed = baseSeed + i;

        ArrayList** lists = createArrayListCopies(copiesPerSeries, size, currentSeed, minValue, maxValue);
        int* preparedValues = prepareRandomValues(copiesPerSeries, minValue, maxValue);
        int* preparedIndexes = new int[copiesPerSeries];

        for (int j = 0; j < copiesPerSeries; j++)
        {
            preparedIndexes[j] = generateRandomNumber(0, size);
        }

        auto start = chrono::steady_clock::now();

        for (int j = 0; j < copiesPerSeries; j++)
        {
            lists[j]->insertAt(preparedIndexes[j], preparedValues[j]);
        }

        auto stop = chrono::steady_clock::now();

        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
        double oneOperationTime = static_cast<double>(duration) / copiesPerSeries;
        totalTime += duration;

        file << "Seria " << i + 1 << ": " << oneOperationTime << " ns/op" << endl;

        deleteArrayListCopies(lists, copiesPerSeries);
        delete[] preparedValues;
        delete[] preparedIndexes;
    }

    double averageTime = static_cast<double>(totalTime) / (seriesCount * copiesPerSeries);

    writeReportFooter(file, averageTime);
    file.close();

    cout << "Zakonczono pomiar insertAt." << endl;
    cout << "Sredni czas: " << averageTime << " ns/op" << endl;
    cout << "Wyniki zapisano do pliku: " << fileName << endl;
   }

   //RemoveBack

   void Research::measureArrayListRemoveBack(int size, int seriesCount, unsigned int baseSeed,
                                          int minValue, int maxValue, const string& fileName)
{
    if (size <= 0 || seriesCount <= 0 || minValue > maxValue)
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
    const int copiesPerSeries = 100;

    writeReportHeader(file, "removeBack",
                      "jedno removeBack na kazdej z identycznych kopii",
                      size, seriesCount, baseSeed, minValue, maxValue, copiesPerSeries);

    for (int i = 0; i < seriesCount; i++)
    {
        unsigned int currentSeed = baseSeed + i;

        ArrayList** lists = createArrayListCopies(copiesPerSeries, size, currentSeed, minValue, maxValue);

        auto start = chrono::steady_clock::now();

        for (int j = 0; j < copiesPerSeries; j++)
        {
            lists[j]->removeBack();
        }

        auto stop = chrono::steady_clock::now();

        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
        double oneOperationTime = static_cast<double>(duration) / copiesPerSeries;
        totalTime += duration;

        file << "Seria " << i + 1 << ": " << oneOperationTime << " ns/op" << endl;

        deleteArrayListCopies(lists, copiesPerSeries);
    }

    double averageTime = static_cast<double>(totalTime) / (seriesCount * copiesPerSeries);

    writeReportFooter(file, averageTime);
    file.close();

    cout << "Zakonczono pomiar removeBack." << endl;
    cout << "Sredni czas: " << averageTime << " ns/op" << endl;
    cout << "Wyniki zapisano do pliku: " << fileName << endl;
}

// RemoveFront

void Research::measureArrayListRemoveFront(int size, int seriesCount, unsigned int baseSeed,
                                           int minValue, int maxValue, const string& fileName)
{
    if (size <= 0 || seriesCount <= 0 || minValue > maxValue)
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
    const int copiesPerSeries = 100;

    writeReportHeader(file, "removeFront",
                      "jedno removeFront na kazdej z identycznych kopii",
                      size, seriesCount, baseSeed, minValue, maxValue, copiesPerSeries);

    for (int i = 0; i < seriesCount; i++)
    {
        unsigned int currentSeed = baseSeed + i;

        ArrayList** lists = createArrayListCopies(copiesPerSeries, size, currentSeed, minValue, maxValue);

        auto start = chrono::steady_clock::now();

        for (int j = 0; j < copiesPerSeries; j++)
        {
            lists[j]->removeFront();
        }

        auto stop = chrono::steady_clock::now();

        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
        double oneOperationTime = static_cast<double>(duration) / copiesPerSeries;
        totalTime += duration;

        file << "Seria " << i + 1 << ": " << oneOperationTime << " ns/op" << endl;

        deleteArrayListCopies(lists, copiesPerSeries);
    }

    double averageTime = static_cast<double>(totalTime) / (seriesCount * copiesPerSeries);

    writeReportFooter(file, averageTime);
    file.close();

    cout << "Zakonczono pomiar removeFront." << endl;
    cout << "Sredni czas: " << averageTime << " ns/op" << endl;
    cout << "Wyniki zapisano do pliku: " << fileName << endl;
}

// RemoveAt

void Research::measureArrayListRemoveAt(int size, int seriesCount, unsigned int baseSeed,
                                        int minValue, int maxValue, const string& fileName)
{
    if (size <= 0 || seriesCount <= 0 || minValue > maxValue)
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
    const int copiesPerSeries = 100;

    writeReportHeader(file, "removeAt",
                      "jedno removeAt na kazdej z identycznych kopii, indeks losowy",
                      size, seriesCount, baseSeed, minValue, maxValue, copiesPerSeries);

    for (int i = 0; i < seriesCount; i++)
    {
        unsigned int currentSeed = baseSeed + i;

        ArrayList** lists = createArrayListCopies(copiesPerSeries, size, currentSeed, minValue, maxValue);
        int* preparedIndexes = new int[copiesPerSeries];

        for (int j = 0; j < copiesPerSeries; j++)
        {
            preparedIndexes[j] = generateRandomNumber(0, size - 1);
        }

        auto start = chrono::steady_clock::now();

        for (int j = 0; j < copiesPerSeries; j++)
        {
            lists[j]->removeAt(preparedIndexes[j]);
        }

        auto stop = chrono::steady_clock::now();

        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
        double oneOperationTime = static_cast<double>(duration) / copiesPerSeries;
        totalTime += duration;

        file << "Seria " << i + 1 << ": " << oneOperationTime << " ns/op" << endl;

        deleteArrayListCopies(lists, copiesPerSeries);
        delete[] preparedIndexes;
    }

    double averageTime = static_cast<double>(totalTime) / (seriesCount * copiesPerSeries);

    writeReportFooter(file, averageTime);
    file.close();

    cout << "Zakonczono pomiar removeAt." << endl;
    cout << "Sredni czas: " << averageTime << " ns/op" << endl;
    cout << "Wyniki zapisano do pliku: " << fileName << endl;
}