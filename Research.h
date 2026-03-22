#ifndef RESEARCH_H
#define RESEARCH_H

#include <string>
#include "ArrayList.h"

class Research
{
    private:
    
    int generateRandomNumber(int minValue, int maxValue); //metoda pomocnicza, losująca liczbę z podanego zakresu, odpowiednik metody w Menu
    //metoda zwracająca formatkę raportu odnośnie wykonywania operacji
    void writeReportHeader(std::ofstream& file, const std::string& operationName, const std::string& measurementMode, int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, int copiesPerSeries);
    // również formatka
    void writeReportFooter(std::ofstream& file, double averageTime);

    ArrayList** createArrayListCopies(int copiesPerSeries, int size, unsigned int seed, int minValue, int maxValue);
    void deleteArrayListCopies(ArrayList** lists, int copiesPerSeries);

    int* prepareRandomValues(int count, int minValue, int maxValue);

    void prepareArrayList(ArrayList& list, int size, unsigned int seed, int minValue, int maxValue); //czyści strukturę, ustawia seed, generuje dane, buduje Arraylist o zadanym rozmiarze

    public:
    void measureArrayListPushBack(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const std::string& fileName); //wykonać wiele serii pomiarowych dla pushBack, zapisać wynik każdej serii do pliku, policzyć średnią
    void measureArrayListPushFront(int size, int seriesCount, unsigned int baseSeed, int minValue, int maxValue, const std::string& fileName);
};

#endif
