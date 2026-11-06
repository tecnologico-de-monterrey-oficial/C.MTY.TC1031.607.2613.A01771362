// Pamela Hernández Camacho
// A01771362
#include <iostream>
using namespace std;
#include "Heap.h"

int main() {

    Heap<int> heap;
    heap.push(10);
    heap.push(20);
    heap.push(5); 
    heap.push(30);
    heap.push(15);
    heap.push(25);
    heap.print();
    heap.printTree(0, 0);


    return 0;
}