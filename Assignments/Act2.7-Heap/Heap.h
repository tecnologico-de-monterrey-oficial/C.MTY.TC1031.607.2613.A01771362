//Pamela Hernández Camacho
//A01771362

#ifndef Heap_h
#define Heap_h

template <typename T>
class Heap {
private:
    vector<T> Heap;
public:
    Heap(); //constructor
    void push(T data);
    void print();
}

template <typename T>
void Heap<T>::push(T data){
    //agregamos el elemento al final de la lista
    //determino el índice del elemento agregado 
    //
}

#endif /*Heap_h*/