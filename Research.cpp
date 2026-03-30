#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include "Research.h"

using namespace std;

namespace
{
    // Pomiar obejmuje wyłącznie jedną badaną operację wykonaną na każdej kopii.
    template <typename Operation>
    long long measureOperationOnCopies(ArrayList** lists, int copiesPerSeries, Operation operation)
    {
        auto start = chrono::steady_clock::now();

        for (int i = 0; i < copiesPerSeries; i++)
        {
            operation(*lists[i], i);
        }

        auto stop = chrono::steady_clock::now();
        return chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    }
}

int Research::generateRandomNumber(int minValue, int maxValue)
{
    return minValue + rand() % (maxValue - minValue + 1);
}

bool Research::validateMeasurementParameters(int size, int seriesCount, int minValue, int maxValue, bool requireNonEmptySize)
{
    if (seriesCount <= 0 || minValue > maxValue)
    {
        cout << "Niepoprawne parametry pomiaru!" << endl;
        return false;
    }

    if (requireNonEmptySize ? size <= 0 : size < 0)
    {
        cout << "Niepoprawne parametry pomiaru!" << endl;
        return false;
    }

    return true;
}

bool Research::openReportFile(ofstream& file, const string& fileName)
{
    file.open(fileName, ios::app);

    if (!file.is_open())
    {
        cout << "Nie udalo sie otworzyc pliku!" << endl;
        return false;
    }

    return true;
}

void Research::prepareArrayList(ArrayList& list, int size, unsigned int seed, int minValue, int maxValue)
{
    list.clear();
    srand(seed);

    for (int i = 0; i < size; i++)
    {
        int value = generateRandomNumber(minValue, maxValue);
        list.pushBack(value);
    }
}

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

void Research::writeSeriesResult(ofstream& file, int seriesNumber, double oneOperationTime)
{
    file << "Seria " << seriesNumber << ": " << oneOperationTime << " ns/op" << endl;
}

void Research::printMeasurementSummary(const string& operationName, double averageTime, const string& fileName)
{
    cout << "Zakonczono pomiar " << operationName << "." << endl;
    cout << "Sredni czas: " << averageTime << " ns/op" << endl;
    cout << "Wyniki zapisano do pliku: " << fileName << endl;
}

ArrayList** Research::createArrayListCopies(int copiesPerSeries, int size, unsigned int seed,
                                            int minValue, int maxValue)
{
    ArrayList** lists = new ArrayList*[copiesPerSeries];

    for (int j = 0; j < copiesPerSeries; j++)
    {
        lists[j] = new ArrayList();
        // Ta sama seria ma startować z identycznego stanu początkowego dla każdej kopii.
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

int* Research::prepareRandomIndexes(int count, int minIndex, int maxIndex)
{
    int* indexes = new int[count];

    for (int i = 0; i < count; i++)
    {
        indexes[i] = generateRandomNumber(minIndex, maxIndex);
    }

    return indexes;
}

int* Research::prepareSearchValues(ArrayList** lists, int copiesPerSeries, int size)
{
    int* values = new int[copiesPerSeries];

    // Losujemy indeks i pobieramy wartość z kopii, więc szukany element na pewno istnieje.
    for (int i = 0; i < copiesPerSeries; i++)
    {
        int randomIndex = generateRandomNumber(0, size - 1);
        values[i] = lists[i]->getValueAt(randomIndex);
    }

    return values;
}

void Research::runArrayListMeasurement(int size, int seriesCount, unsigned int baseSeed,
                                       int minValue, int maxValue, const string& fileName,
                                       const string& operationName, const string& measurementMode,
                                       bool requireNonEmptySize,
                                       const function<long long(unsigned int currentSeed)>& measureSeries)
{
    if (!validateMeasurementParameters(size, seriesCount, minValue, maxValue, requireNonEmptySize))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file, fileName))
    {
        return;
    }

    long long totalTime = 0;

    writeReportHeader(file, operationName, measurementMode, size, seriesCount, baseSeed,
                      minValue, maxValue, COPIES_PER_SERIES);

    for (int i = 0; i < seriesCount; i++)
    {
        unsigned int currentSeed = baseSeed + i;
        long long duration = measureSeries(currentSeed);
        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;

        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);
    }

    double averageTime = static_cast<double>(totalTime) / (seriesCount * COPIES_PER_SERIES);

    writeReportFooter(file, averageTime);
    file.close();
    printMeasurementSummary(operationName, averageTime, fileName);
}

//=========================================================================================================
//=========================================================================================================
// Pomiary operacji

//PushBack

void Research::measureArrayListPushBack(int size, int seriesCount, unsigned int baseSeed,
                                        int minValue, int maxValue, const string& fileName)
{
    runArrayListMeasurement(size, seriesCount, baseSeed, minValue, maxValue, fileName,
                            "pushBack", "jedno pushBack na kazdej z identycznych kopii", false,
                            [this, size, minValue, maxValue](unsigned int currentSeed)
                            {
                                ArrayList** lists = createArrayListCopies(COPIES_PER_SERIES, size, currentSeed, minValue, maxValue);
                                int* preparedValues = prepareRandomValues(COPIES_PER_SERIES, minValue, maxValue);

                                long long duration = measureOperationOnCopies(
                                    lists,
                                    COPIES_PER_SERIES,
                                    [preparedValues](ArrayList& list, int copyIndex)
                                    {
                                        list.pushBack(preparedValues[copyIndex]);
                                    });

                                deleteArrayListCopies(lists, COPIES_PER_SERIES);
                                delete[] preparedValues;

                                return duration;
                            });
}

// PushFront

void Research::measureArrayListPushFront(int size, int seriesCount, unsigned int baseSeed,
                                         int minValue, int maxValue, const string& fileName)
{
    runArrayListMeasurement(size, seriesCount, baseSeed, minValue, maxValue, fileName,
                            "pushFront", "jedno pushFront na kazdej z identycznych kopii", false,
                            [this, size, minValue, maxValue](unsigned int currentSeed)
                            {
                                ArrayList** lists = createArrayListCopies(COPIES_PER_SERIES, size, currentSeed, minValue, maxValue);
                                int* preparedValues = prepareRandomValues(COPIES_PER_SERIES, minValue, maxValue);

                                long long duration = measureOperationOnCopies(
                                    lists,
                                    COPIES_PER_SERIES,
                                    [preparedValues](ArrayList& list, int copyIndex)
                                    {
                                        list.pushFront(preparedValues[copyIndex]);
                                    });

                                deleteArrayListCopies(lists, COPIES_PER_SERIES);
                                delete[] preparedValues;

                                return duration;
                            });
}

// InsertAt

void Research::measureArrayListInsertAt(int size, int seriesCount, unsigned int baseSeed,
                                        int minValue, int maxValue, const string& fileName)
{
    runArrayListMeasurement(size, seriesCount, baseSeed, minValue, maxValue, fileName,
                            "insertAt", "jedno insertAt na kazdej z identycznych kopii, indeks losowy", false,
                            [this, size, minValue, maxValue](unsigned int currentSeed)
                            {
                                ArrayList** lists = createArrayListCopies(COPIES_PER_SERIES, size, currentSeed, minValue, maxValue);
                                int* preparedValues = prepareRandomValues(COPIES_PER_SERIES, minValue, maxValue);
                                int* preparedIndexes = prepareRandomIndexes(COPIES_PER_SERIES, 0, size);

                                long long duration = measureOperationOnCopies(
                                    lists,
                                    COPIES_PER_SERIES,
                                    [preparedIndexes, preparedValues](ArrayList& list, int copyIndex)
                                    {
                                        list.insertAt(preparedIndexes[copyIndex], preparedValues[copyIndex]);
                                    });

                                deleteArrayListCopies(lists, COPIES_PER_SERIES);
                                delete[] preparedValues;
                                delete[] preparedIndexes;

                                return duration;
                            });
}

//RemoveBack

void Research::measureArrayListRemoveBack(int size, int seriesCount, unsigned int baseSeed,
                                          int minValue, int maxValue, const string& fileName)
{
    runArrayListMeasurement(size, seriesCount, baseSeed, minValue, maxValue, fileName,
                            "removeBack", "jedno removeBack na kazdej z identycznych kopii", true,
                            [this, size, minValue, maxValue](unsigned int currentSeed)
                            {
                                ArrayList** lists = createArrayListCopies(COPIES_PER_SERIES, size, currentSeed, minValue, maxValue);

                                long long duration = measureOperationOnCopies(
                                    lists,
                                    COPIES_PER_SERIES,
                                    [](ArrayList& list, int)
                                    {
                                        list.removeBack();
                                    });

                                deleteArrayListCopies(lists, COPIES_PER_SERIES);

                                return duration;
                            });
}

// RemoveFront

void Research::measureArrayListRemoveFront(int size, int seriesCount, unsigned int baseSeed,
                                           int minValue, int maxValue, const string& fileName)
{
    runArrayListMeasurement(size, seriesCount, baseSeed, minValue, maxValue, fileName,
                            "removeFront", "jedno removeFront na kazdej z identycznych kopii", true,
                            [this, size, minValue, maxValue](unsigned int currentSeed)
                            {
                                ArrayList** lists = createArrayListCopies(COPIES_PER_SERIES, size, currentSeed, minValue, maxValue);

                                long long duration = measureOperationOnCopies(
                                    lists,
                                    COPIES_PER_SERIES,
                                    [](ArrayList& list, int)
                                    {
                                        list.removeFront();
                                    });

                                deleteArrayListCopies(lists, COPIES_PER_SERIES);

                                return duration;
                            });
}

// RemoveAt

void Research::measureArrayListRemoveAt(int size, int seriesCount, unsigned int baseSeed,
                                        int minValue, int maxValue, const string& fileName)
{
    runArrayListMeasurement(size, seriesCount, baseSeed, minValue, maxValue, fileName,
                            "removeAt", "jedno removeAt na kazdej z identycznych kopii, indeks losowy", true,
                            [this, size, minValue, maxValue](unsigned int currentSeed)
                            {
                                ArrayList** lists = createArrayListCopies(COPIES_PER_SERIES, size, currentSeed, minValue, maxValue);
                                int* preparedIndexes = prepareRandomIndexes(COPIES_PER_SERIES, 0, size - 1);

                                long long duration = measureOperationOnCopies(
                                    lists,
                                    COPIES_PER_SERIES,
                                    [preparedIndexes](ArrayList& list, int copyIndex)
                                    {
                                        list.removeAt(preparedIndexes[copyIndex]);
                                    });

                                deleteArrayListCopies(lists, COPIES_PER_SERIES);
                                delete[] preparedIndexes;

                                return duration;
                            });
}

void Research::measureArrayListSearch(int size, int seriesCount, unsigned int baseSeed,
                                      int minValue, int maxValue, const string& fileName)
{
    runArrayListMeasurement(size, seriesCount, baseSeed, minValue, maxValue, fileName,
                            "search", "jedno search na kopii, szukany element istnieje i ma losowa pozycje", true,
                            [this, size, minValue, maxValue](unsigned int currentSeed)
                            {
                                ArrayList** lists = createArrayListCopies(COPIES_PER_SERIES, size, currentSeed, minValue, maxValue);
                                int* preparedValues = prepareSearchValues(lists, COPIES_PER_SERIES, size);

                                long long duration = measureOperationOnCopies(
                                    lists,
                                    COPIES_PER_SERIES,
                                    [preparedValues](ArrayList& list, int copyIndex)
                                    {
                                        list.searchRaw(preparedValues[copyIndex]);
                                    });

                                deleteArrayListCopies(lists, COPIES_PER_SERIES);
                                delete[] preparedValues;

                                return duration;
                            });
}


//============================================================================================
//--------------------------------------------------------------------------------------------
//Lista jednokierunkowa

SinglyLinkedList** Research::createSinglyLinkedListCopies(int copiesPerSeries, int size, unsigned int seed, int minValue, int maxValue)
{
    SinglyLinkedList** lists = new SinglyLinkedList*[copiesPerSeries];

    for (int j = 0; j < copiesPerSeries; j++)
    {
        lists[j] = new SinglyLinkedList();

        srand(seed);
        for (int i = 0; i < size; i++){
            int value = generateRandomNumber(minValue, maxValue);
            lists[j]->pushBack(value);
        }
    }

    return lists;
}

void Research::deleteSinglyLinkedCopies(SinglyLinkedList** lists, int copiesPerSeries)
{
    for (int j = 0; j < copiesPerSeries; j++)
    {
        delete lists[j];
    }

    delete[] lists;
}

void Research::measureSinglyLinkedListPushBack(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const string& fileName)
{
    if (!validateMeasurementParameters(size, seriesCount, minValue, maxValue, false))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file, fileName)){
        return;
    }

    long long totalTime = 0;

    writeReportHeader(file, "pushBack", "jedno na kopie", size, seriesCount, baseSeed, minValue, maxValue, COPIES_PER_SERIES);

    for (int i = 0; i < seriesCount; i++)
    {
        unsigned int currentSeed = baseSeed + i;
        SinglyLinkedList** lists = createSinglyLinkedListCopies(COPIES_PER_SERIES, size, currentSeed, minValue, maxValue);
        int* preparedValues = prepareRandomValues(COPIES_PER_SERIES, minValue, maxValue);
        auto start = chrono::steady_clock::now();
        for (int j = 0; j < COPIES_PER_SERIES; j++){
            lists[j]->pushBack(preparedValues[j]);
        }

        auto stop = chrono::steady_clock::now();

        long long duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
        double oneOperationTime = static_cast<double>(duration) /  COPIES_PER_SERIES;

        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteSinglyLinkedCopies(lists, COPIES_PER_SERIES);
        delete[] preparedValues;
    }

    double averageTime = static_cast<double>(totalTime) / (seriesCount * COPIES_PER_SERIES);

    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("pushBack (SinglyLinkedList)", averageTime, fileName);
}

void Research::measureSinglyLinkedListPushFront(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const string& fileName)
{
    if (!validateMeasurementParameters(size, seriesCount, minValue, maxValue, false))
    {
        return;
    }

    ofstream file;

    if (!openReportFile(file, fileName))
    {
        return;
    }

    long long totalTime = 0;

    writeReportHeader(file, "pushFront", "jedno pushFront na kopie", size, seriesCount, baseSeed, minValue, maxValue, COPIES_PER_SERIES);

    for (int i = 0; i < seriesCount; i++)
    {
        unsigned int currentSeed = baseSeed + i;

        SinglyLinkedList** lists = createSinglyLinkedListCopies(COPIES_PER_SERIES, size, currentSeed, minValue, maxValue);
        int* preparedValues = prepareRandomValues(COPIES_PER_SERIES, minValue, maxValue);

        auto start = chrono::steady_clock::now();
        for (int j = 0; j < COPIES_PER_SERIES; j++)
        {
            lists[j]->pushFront(preparedValues[j]);
        }

        auto stop = chrono::steady_clock::now();

        long long duration = chrono::duration_cast<chrono::nanoseconds>(stop-start).count();
        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;

        totalTime += duration;
        writeSeriesResult(file, i+1, oneOperationTime);

        deleteSinglyLinkedCopies(lists, COPIES_PER_SERIES);
        delete[] preparedValues;
    }

    double averageTime = static_cast<double>(totalTime) / (seriesCount * COPIES_PER_SERIES);
    
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("pushFront (SinglyLinkedList)", averageTime, fileName);
}