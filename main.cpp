#include <iostream>
#include "ArrayList.h"

using namespace std;

int main() {
   ArrayList lista;

   lista.pushBack(10);
   lista.pushBack(20);
   lista.pushBack(30);
   lista.pushBack(40);

   lista.print();

   lista.pushBack(50);
   lista.print();

   lista.pushFront(1);
   lista.print();

   lista.insertAt(2, 99);
   lista.print();

   lista.insertAt(0, 5);
   lista.print();

   lista.insertAt(lista.getSize(), 77);
   lista.print();
   

   return 0;

}