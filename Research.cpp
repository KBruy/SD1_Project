#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Research.h"

using namespace std;

int Research::generateRandomNumber(int minValue, int maxValue)
{
    return minValue + rand() % (maxValue - minValue + 1);
}

bool Research::validateMeasurementParameters(int size, bool requireNonEmptySize)
{
    if (requireNonEmptySize ? size <= 0 : size < 0)
    {
        cout << "Niepoprawne parametry pomiaru!" << endl;
        return false;
    }

    return true;
}

bool Research::openReportFile(ofstream& file)
{
    file.open(REPORT_FILE_NAME, ios::app);

    if (!file.is_open())
    {
        cout << "Nie udalo sie otworzyc pliku!" << endl;
        return false;
    }

    return true;
}

int Research::prepareRandomValue()
{
    return generateRandomNumber();
}

int Research::prepareRandomIndex(int minIndex, int maxIndex)
{
    return generateRandomNumber(minIndex, maxIndex);
}

void Research::prepareArrayList(ArrayList& list, int size, unsigned int seed)
{
    list.clear();
    srand(seed);

    for (int i = 0; i < size; i++)
    {
        int value = generateRandomNumber();
        list.pushBack(value);
    }
}

void Research::prepareSinglyLinkedList(SinglyLinkedList& list, int size, unsigned int seed)
{
    list.clear();
    srand(seed);

    for (int i = 0; i < size; i++)
    {
        int value = generateRandomNumber();
        list.pushBack(value);
    }
}

void Research::writeReportHeader(ofstream& file, const string& structureName, const string& operationName, int size)
{
    file << "==========================" << endl;
    file << "Struktura: " << structureName << endl;
    file << "Operacja: " << operationName << endl;
    file << "Rozmiar poczatkowy: " << size << endl;
    file << "Liczba serii: " << SERIES_COUNT << endl;
    file << "Liczba kopii w serii: " << COPIES_PER_SERIES << endl;
    file << "Seed bazowy: " << BASE_SEED << endl;
    file << "Zakres losowania: [" << MIN_RANDOM_VALUE << ", " << MAX_RANDOM_VALUE << "]" << endl;
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

void Research::printMeasurementSummary(const string& structureName, const string& operationName, double averageTime)
{
    cout << "Zakonczono pomiar " << operationName << " dla " << structureName << "." << endl;
    cout << "Sredni czas: " << averageTime << " ns/op" << endl;
    cout << "Wyniki zapisano do pliku: " << REPORT_FILE_NAME << endl;
}

ArrayList** Research::createArrayListCopies(int size, unsigned int seed)
{
    ArrayList** lists = new ArrayList*[COPIES_PER_SERIES];

    for (int i = 0; i < COPIES_PER_SERIES; i++)
    {
        lists[i] = new ArrayList();
        prepareArrayList(*lists[i], size, seed);
    }

    return lists;
}

void Research::deleteArrayListCopies(ArrayList** lists)
{
    for (int i = 0; i < COPIES_PER_SERIES; i++)
    {
        delete lists[i];
    }

    delete[] lists;
}

SinglyLinkedList** Research::createSinglyLinkedListCopies(int size, unsigned int seed)
{
    SinglyLinkedList** lists = new SinglyLinkedList*[COPIES_PER_SERIES];

    for (int i = 0; i < COPIES_PER_SERIES; i++)
    {
        lists[i] = new SinglyLinkedList();
        prepareSinglyLinkedList(*lists[i], size, seed);
    }

    return lists;
}

void Research::deleteSinglyLinkedListCopies(SinglyLinkedList** lists)
{
    for (int i = 0; i < COPIES_PER_SERIES; i++)
    {
        delete lists[i];
    }

    delete[] lists;
}

//=========================================================================================================
// Tablica dynamiczna

void Research::measureArrayListPushBack(int size)
{
    if (!validateMeasurementParameters(size, false))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "ArrayList", "pushBack", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        ArrayList** lists = createArrayListCopies(size, currentSeed);

        srand(currentSeed);
        int preparedValue = prepareRandomValue();

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->pushBack(preparedValue);
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteArrayListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("ArrayList", "pushBack", averageTime);
}

void Research::measureArrayListPushFront(int size)
{
    if (!validateMeasurementParameters(size, false))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "ArrayList", "pushFront", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        ArrayList** lists = createArrayListCopies(size, currentSeed);

        srand(currentSeed);
        int preparedValue = prepareRandomValue();

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->pushFront(preparedValue);
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteArrayListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("ArrayList", "pushFront", averageTime);
}

void Research::measureArrayListInsertAt(int size)
{
    if (!validateMeasurementParameters(size, false))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "ArrayList", "insertAt", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        ArrayList** lists = createArrayListCopies(size, currentSeed);

        srand(currentSeed);
        int preparedValue = prepareRandomValue();
        int preparedIndex = prepareRandomIndex(0, size);

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->insertAt(preparedIndex, preparedValue);
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteArrayListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("ArrayList", "insertAt", averageTime);
}

void Research::measureArrayListRemoveBack(int size)
{
    if (!validateMeasurementParameters(size, true))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "ArrayList", "removeBack", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        ArrayList** lists = createArrayListCopies(size, currentSeed);

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->removeBack();
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteArrayListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("ArrayList", "removeBack", averageTime);
}

void Research::measureArrayListRemoveFront(int size)
{
    if (!validateMeasurementParameters(size, true))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "ArrayList", "removeFront", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        ArrayList** lists = createArrayListCopies(size, currentSeed);

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->removeFront();
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteArrayListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("ArrayList", "removeFront", averageTime);
}

void Research::measureArrayListRemoveAt(int size)
{
    if (!validateMeasurementParameters(size, true))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "ArrayList", "removeAt", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        ArrayList** lists = createArrayListCopies(size, currentSeed);

        srand(currentSeed);
        int preparedIndex = prepareRandomIndex(0, size - 1);

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->removeAt(preparedIndex);
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteArrayListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("ArrayList", "removeAt", averageTime);
}

void Research::measureArrayListSearch(int size)
{
    if (!validateMeasurementParameters(size, true))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "ArrayList", "search", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        ArrayList** lists = createArrayListCopies(size, currentSeed);

        srand(currentSeed);
        int preparedIndex = prepareRandomIndex(0, size - 1);
        int preparedValue = lists[0]->getValueAt(preparedIndex);

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->searchRaw(preparedValue);
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteArrayListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("ArrayList", "search", averageTime);
}

//=========================================================================================================
// Lista jednokierunkowa

void Research::measureSinglyLinkedListPushBack(int size)
{
    if (!validateMeasurementParameters(size, false))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "SinglyLinkedList", "pushBack", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        SinglyLinkedList** lists = createSinglyLinkedListCopies(size, currentSeed);

        srand(currentSeed);
        int preparedValue = prepareRandomValue();

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->pushBack(preparedValue);
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteSinglyLinkedListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("SinglyLinkedList", "pushBack", averageTime);
}

void Research::measureSinglyLinkedListPushFront(int size)
{
    if (!validateMeasurementParameters(size, false))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "SinglyLinkedList", "pushFront", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        SinglyLinkedList** lists = createSinglyLinkedListCopies(size, currentSeed);

        srand(currentSeed);
        int preparedValue = prepareRandomValue();

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->pushFront(preparedValue);
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteSinglyLinkedListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("SinglyLinkedList", "pushFront", averageTime);
}

void Research::measureSinglyLinkedListInsertAt(int size)
{
    if (!validateMeasurementParameters(size, false))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "SinglyLinkedList", "insertAt", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        SinglyLinkedList** lists = createSinglyLinkedListCopies(size, currentSeed);

        srand(currentSeed);
        int preparedValue = prepareRandomValue();
        int preparedIndex = prepareRandomIndex(0, size);

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->insertAt(preparedIndex, preparedValue);
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteSinglyLinkedListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("SinglyLinkedList", "insertAt", averageTime);
}

void Research::measureSinglyLinkedListRemoveBack(int size)
{
    if (!validateMeasurementParameters(size, true))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "SinglyLinkedList", "removeBack", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        SinglyLinkedList** lists = createSinglyLinkedListCopies(size, currentSeed);

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->removeBack();
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteSinglyLinkedListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("SinglyLinkedList", "removeBack", averageTime);
}

void Research::measureSinglyLinkedListRemoveFront(int size)
{
    if (!validateMeasurementParameters(size, true))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "SinglyLinkedList", "removeFront", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        SinglyLinkedList** lists = createSinglyLinkedListCopies(size, currentSeed);

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->removeFront();
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteSinglyLinkedListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("SinglyLinkedList", "removeFront", averageTime);
}

void Research::measureSinglyLinkedListRemoveAt(int size)
{
    if (!validateMeasurementParameters(size, true))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "SinglyLinkedList", "removeAt", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        SinglyLinkedList** lists = createSinglyLinkedListCopies(size, currentSeed);

        srand(currentSeed);
        int preparedIndex = prepareRandomIndex(0, size - 1);

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->removeAt(preparedIndex);
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteSinglyLinkedListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("SinglyLinkedList", "removeAt", averageTime);
}

void Research::measureSinglyLinkedListSearch(int size)
{
    if (!validateMeasurementParameters(size, true))
    {
        return;
    }

    ofstream file;
    if (!openReportFile(file))
    {
        return;
    }

    long long totalTime = 0;
    writeReportHeader(file, "SinglyLinkedList", "search", size);

    for (int i = 0; i < SERIES_COUNT; i++)
    {
        unsigned int currentSeed = BASE_SEED + i;
        SinglyLinkedList** lists = createSinglyLinkedListCopies(size, currentSeed);

        srand(currentSeed);
        int preparedIndex = prepareRandomIndex(0, size - 1);
        int preparedValue = lists[0]->getValueAt(preparedIndex);

        long long duration = measureCopiesExecutionTime(COPIES_PER_SERIES, [&](int j)
        {
            lists[j]->searchRaw(preparedValue);
        });

        double oneOperationTime = static_cast<double>(duration) / COPIES_PER_SERIES;
        totalTime += duration;
        writeSeriesResult(file, i + 1, oneOperationTime);

        deleteSinglyLinkedListCopies(lists);
    }

    double averageTime = static_cast<double>(totalTime) / (SERIES_COUNT * COPIES_PER_SERIES);
    writeReportFooter(file, averageTime);
    file.close();

    printMeasurementSummary("SinglyLinkedList", "search", averageTime);
}