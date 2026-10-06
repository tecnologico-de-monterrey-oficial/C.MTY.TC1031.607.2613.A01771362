#ifndef Queue_h
#define Queue_h

#include "Node.h"
#include <stdexcept>

using namespace std;

template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}

    void push(const T& data);
    T pop();
    T front();
    int size();
};


// Agrega un elemento al final del Queue
template <typename T>
void Queue<T>::push(const T& data) {

    // Creamos un nuevo nodo
    Node<T>* newNode = new Node<T>(data);

    // Si la fila esta vacia
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        // Conectamos tail con el nuevo nodo
        tail->next = newNode;

        // Actualizamos tail
        tail = newNode;
    }

    count++;
}


// Borra el primer elemento y regresa su valor
template <typename T>
T Queue<T>::pop() {

    // Validamos que no este vacio
    if (head == nullptr) {
        throw runtime_error("La fila esta vacia");
    }

    // Guardamos el nodo que vamos a eliminar
    Node<T>* aux = head;

    // Guardamos sus datos antes de eliminarlo
    T data = aux->data;

    // Movemos head al siguiente nodo
    head = head->next;

    // Si ya no quedan elementos
    if (head == nullptr) {
        tail = nullptr;
    }

    // Eliminamos el nodo anterior
    delete aux;

    count--;

    // Regresamos el valor eliminado
    return data;
}


// Regresa el primer elemento sin borrarlo
template <typename T>
T Queue<T>::front() {

    // Validamos que no este vacio
    if (head == nullptr) {
        throw runtime_error("La fila esta vacia");
    }

    return head->data;
}


// Regresa cuantos elementos hay en el Queue
template <typename T>
int Queue<T>::size() {
    return count;
}

#endif