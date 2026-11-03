// Pamela Hernandez Camacho
// A01771362

#ifndef Queue_h
#define Queue_h

#include "Node.h"
#include <stdexcept>

// ADT Queue (FIFO) implementado con lista ligada
template <typename T>
class Queue {
private:
    Node<T>* head;   // primer elemento (el que sale)
    Node<T>* tail;   // ultimo elemento (el que acaba de entrar)
    int count;

public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);
    ~Queue();

    void push(const T& data);
    T pop();
    T front() const;
    int size() const;
    bool empty() const;
};


// Constructor de copia (copia profunda)
template <typename T>
Queue<T>::Queue(const Queue& other) : head(nullptr), tail(nullptr), count(0) {
    Node<T>* curr = other.head;
    while (curr != nullptr) {
        push(curr->data);
        curr = curr->next;
    }
}


// Operador de asignacion
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        while (head != nullptr) {
            pop();
        }
        Node<T>* curr = other.head;
        while (curr != nullptr) {
            push(curr->data);
            curr = curr->next;
        }
    }
    return *this;
}


// Destructor: libera todos los nodos
template <typename T>
Queue<T>::~Queue() {
    while (head != nullptr) {
        Node<T>* aux = head;
        head = head->next;
        delete aux;
    }
    tail = nullptr;
    count = 0;
}


// Agrega un elemento al final del Queue
// Complejidad: O(1)
template <typename T>
void Queue<T>::push(const T& data) {
    Node<T>* newNode = new Node<T>(data);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    count++;
}


// Borra el primer elemento y regresa su valor
// Lanza runtime_error si esta vacio. Complejidad: O(1)
template <typename T>
T Queue<T>::pop() {
    if (head == nullptr) {
        throw std::runtime_error("La fila esta vacia");
    }

    Node<T>* aux = head;
    T data = aux->data;

    head = head->next;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete aux;
    count--;

    return data;
}


// Regresa el primer elemento sin borrarlo
// Lanza runtime_error si esta vacio. Complejidad: O(1)
template <typename T>
T Queue<T>::front() const {
    if (head == nullptr) {
        throw std::runtime_error("La fila esta vacia");
    }

    return head->data;
}


// Regresa cuantos elementos hay en el Queue
template <typename T>
int Queue<T>::size() const {
    return count;
}


// Indica si el Queue esta vacio
template <typename T>
bool Queue<T>::empty() const {
    return count == 0;
}

#endif