#include <iostream>
#include "ArrayList.h"

using namespace std;

int main() {
   ArrayList lista;
   cout << "Liczba elemenów: " << lista.getSize() << endl;
   cout << "Pojemnosc: "<< lista.getCapacity() << endl;

   lista.print();

   return 0;

}