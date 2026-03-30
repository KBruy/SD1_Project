#ifndef RESEARCH_H
#define RESEARCH_H

#include <fstream>
#include <functional>
#include <string>
#include "ArrayList.h"
#include "SinglyLinkedList.h"


class Research
{
private:
    static const int COPIES_PER_SERIES = 100;

    int generateRandomNumber(int minValue, int maxValue);
    bool validateMeasurementParameters(int size, int seriesCount, int minValue, int maxValue, bool requireNonEmptySize);
    bool openReportFile(std::ofstream& file, const std::string& fileName);

    void writeReportHeader(std::ofstream& file, const std::string& operationName, const std::string& measurementMode,
                           int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, int copiesPerSeries);
    void writeReportFooter(std::ofstream& file, double averageTime);
    void writeSeriesResult(std::ofstream& file, int seriesNumber, double oneOperationTime);
    void printMeasurementSummary(const std::string& operationName, double averageTime, const std::string& fileName);

    ArrayList** createArrayListCopies(int copiesPerSeries, int size, unsigned int seed, int minValue, int maxValue);
    void deleteArrayListCopies(ArrayList** lists, int copiesPerSeries);

    int* prepareRandomValues(int count, int minValue, int maxValue);
    int* prepareRandomIndexes(int count, int minIndex, int maxIndex);
    int* prepareSearchValues(ArrayList** lists, int copiesPerSeries, int size);

    void prepareArrayList(ArrayList& list, int size, unsigned int seed, int minValue, int maxValue);

    void runArrayListMeasurement(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue,
                                 const std::string& fileName, const std::string& operationName,
                                 const std::string& measurementMode, bool requireNonEmptySize,
                                 const std::function<long long(unsigned int currentSeed)>& measureSeries);


    //Lista Jednokierunkowa

    //helper tworzący kopie listy jednokierunkowej
    SinglyLinkedList** createSinglyLinkedListCopies(int copiesPerSeries, int size, unsigned int seed, int minValue, int maxValue);
    //helper usuwający kopie
    void deleteSinglyLinkedCopies(SinglyLinkedList** lists, int copiesPerSeries);

public:

    //Tablica dynamiczna
    void measureArrayListPushBack(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const std::string& fileName);
    void measureArrayListPushFront(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const std::string& fileName);
    void measureArrayListInsertAt(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const std::string& fileName);
    void measureArrayListRemoveBack(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const std::string& fileName);
    void measureArrayListRemoveFront(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const std::string& fileName);
    void measureArrayListRemoveAt(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const std::string& fileName);
    void measureArrayListSearch(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const std::string& fileName);

    // Lista jednokierunkowa
    void measureSinglyLinkedListPushBack(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const std::string& fileName);
    void measureSinglyLinkedListPushFront(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const std::string& fileName);
    


};

#endif
