//Pamela Hernández Camacho
//A01771362

#include <vector>
#include <iostream>
using namespace std;

#ifndef Heap_h
#define Heap_h

template <typename T>
class Heap {
private:
    vector<T> heap;
    void swap(int a, int b);
public:
    Heap(); //constructor
    void push(T data);
    void print();
};

// swap function to swap two elements in the heap
template <typename T>
void Heap<T>::swap(int a, int b) {
    T temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

template <typename T>
void Heap<T>::push(T data) {
    // agrego el elemento al final de lista
    heap.push_back(data);
    // determino el índice del elemento agregado
    int index = heap.size()-1;
    // encuentro el indice del padre
    int father = (index - 1) / 2;
    // itero mientras el índice del padre sea mayor o igual a 0
    while (father >= 0) {
        // comparo si el valor del indice es mayor al valor del padre
        if (heap[index] > heap[father]) {
            // si es mayor
            // intercambio los valores
            swap(index, father);
            // hago que el indice sea igual al padre
            index = father;
            // calculo el nuevo padre
            father = (index - 1) / 2;
        } else {
            // no es mayor
            // me salgo de la función
            return;
        }
    }
}

// print function to print the elements of the heap
template <typename T>
void Heap<T>::print() {
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

// print del tree
template <typename T>
void Heap<T>::printTree(int index, int space) {
    if (index >= heap.size()) {
        return;
    }
    space += 5;
    printTree(2 * index + 2, space);
    cout << endl;
    for (int i = 5; i < space; i++) {
        cout << " ";
    }
    cout << heap[index] << "\n";
    printTree(2 * index + 1, space);
}



#endif /* Heap_h */