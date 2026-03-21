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
   cout << "Size: " << lista.getSize() << endl;
   cout << "Capacity: " << lista.getCapacity() << endl;

   lista.pushBack(50);

   lista.print();
   cout << "Size: " << lista.getSize() << endl;
   cout << "Capacity: " << lista.getCapacity() << endl;

   return 0;

}