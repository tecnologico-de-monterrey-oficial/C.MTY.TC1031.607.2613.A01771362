#ifndef Stack_h
#define Stack_h

#include "Node.h"
#include <stdexcept>

using namespace std;

template <typename T>
class Stack {

private:

    Node<T>* head;
    int count;

public:

    // Constructor
    Stack() : head(nullptr), count(0) {}

    void push(const T& data);
    T pop();
    T top();
    int size();
};


// PUSH
// Agrega un elemento al Stack
template <typename T>
void Stack<T>::push(const T& data) {

    // Creamos un nodo nuevo
    Node<T>* newNode = new Node<T>(data);

    // El nuevo nodo apunta al antiguo head
    newNode->next = head;

    // Ahora el nuevo nodo es el head
    head = newNode;

    count++;
}


// POP
// Elimina y regresa el ultimo elemento agregado
template <typename T>
T Stack<T>::pop() {

    // Validamos que el Stack no este vacio
    if (head == nullptr) {
        throw runtime_error("El historial esta vacio");
    }

    // Guardamos el nodo que vamos a eliminar
    Node<T>* aux = head;

    // Guardamos sus datos antes de borrarlo
    T data = aux->data;

    // Movemos head al siguiente nodo
    head = head->next;

    // Eliminamos el nodo anterior
    delete aux;

    count--;

    // Regresamos el valor eliminado
    return data;
}


// TOP
// Regresa el ultimo elemento agregado sin borrarlo
template <typename T>
T Stack<T>::top() {

    // Validamos que el Stack no este vacio
    if (head == nullptr) {
        throw runtime_error("El historial esta vacio");
    }

    return head->data;
}


// SIZE
// Regresa cuantos elementos hay en el Stack
template <typename T>
int Stack<T>::size() {

    return count;
}

#endif