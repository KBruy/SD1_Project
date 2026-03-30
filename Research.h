#ifndef RESEARCH_H
#define RESEARCH_H

#include <fstream>
#include <string>
#include <chrono>
#include "ArrayList.h"
#include "SinglyLinkedList.h"

class Research
{
private:
    static const int SERIES_COUNT = 10;
    static const int COPIES_PER_SERIES = 10;
    static const unsigned int BASE_SEED = 12345;
    static const int MIN_RANDOM_VALUE = 0;
    static const int MAX_RANDOM_VALUE = 16777215;
    static constexpr const char* REPORT_FILE_NAME = "pomiary.txt";

    int generateRandomNumber(int minValue = MIN_RANDOM_VALUE, int maxValue = MAX_RANDOM_VALUE);
    bool validateMeasurementParameters(int size, bool requireNonEmptySize);
    bool openReportFile(std::ofstream& file);

    void writeReportHeader(std::ofstream& file, const std::string& structureName, const std::string& operationName,
                           int size);
    void writeReportFooter(std::ofstream& file, double averageTime);
    void writeSeriesResult(std::ofstream& file, int seriesNumber, double oneOperationTime);
    void printMeasurementSummary(const std::string& structureName, const std::string& operationName, double averageTime);

    ArrayList** createArrayListCopies(int size, unsigned int seed);
    void deleteArrayListCopies(ArrayList** lists);

    int prepareRandomValue();
    int prepareRandomIndex(int minIndex, int maxIndex);

    void prepareArrayList(ArrayList& list, int size, unsigned int seed);
    void prepareSinglyLinkedList(SinglyLinkedList& list, int size, unsigned int seed);

    SinglyLinkedList** createSinglyLinkedListCopies(int size, unsigned int seed);
    void deleteSinglyLinkedListCopies(SinglyLinkedList** lists);

    template <typename Operation>
    long long measureCopiesExecutionTime(int copiesCount, Operation operation);

public:
    // Tablica dynamiczna
    void measureArrayListPushBack(int size);
    void measureArrayListPushFront(int size);
    void measureArrayListInsertAt(int size);
    void measureArrayListRemoveBack(int size);
    void measureArrayListRemoveFront(int size);
    void measureArrayListRemoveAt(int size);
    void measureArrayListSearch(int size);

    // Lista jednokierunkowa
    void measureSinglyLinkedListPushBack(int size);
    void measureSinglyLinkedListPushFront(int size);
    void measureSinglyLinkedListInsertAt(int size);
    void measureSinglyLinkedListRemoveBack(int size);
    void measureSinglyLinkedListRemoveFront(int size);
    void measureSinglyLinkedListRemoveAt(int size);
    void measureSinglyLinkedListSearch(int size);
};

template <typename Operation>
long long Research::measureCopiesExecutionTime(int copiesCount, Operation operation)
{
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < copiesCount; i++)
    {
        operation(i);
    }

    auto stop = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
}

#endif