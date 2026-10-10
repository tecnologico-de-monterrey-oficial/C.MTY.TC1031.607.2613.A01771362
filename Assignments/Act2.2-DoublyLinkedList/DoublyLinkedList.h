// Pamela Hernández Camacho
// A01771362
#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "NodeD.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    NodeD<T>* head;
    NodeD<T>* tail;
    int size = 0;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    ~DoublyLinkedList();
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);

    int getSize() const;
    bool isEmpty() const;
    void addFirst(T data);
    void addLast(T data);
    void insert(int index, T data);
    bool deleteAt(int index);
    int findData(T data) const;
    bool deleteData(T data);
    T getData(int index) const;
    void updateData(T oldData, T newData);
    void updateAt(int index, T newData);
    T& operator[](int index);
    const T& operator[](int index) const;
    void clear();
    void sort();
    void duplicate();
    void removeDuplicates();
    void printForward(ostream& out = cout) const;
    void printBackward(ostream& out = cout) const;
};

// Constructor de copia: crea nuevos nodos con los datos de la otra lista.
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
    : head(nullptr), tail(nullptr), size(0) {
    try {
        NodeD<T>* aux = other.head;
        while (aux != nullptr) {
            addLast(aux->data);
            aux = aux->next;
        }
    } catch (...) {
        clear();
        throw;
    }
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

// Operador =: copia los datos sin compartir los nodos.
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    if (this != &other) {
        DoublyLinkedList<T> copia(other);

        NodeD<T>* auxHead = head;
        NodeD<T>* auxTail = tail;
        int auxSize = size;

        head = copia.head;
        tail = copia.tail;
        size = copia.size;

        copia.head = auxHead;
        copia.tail = auxTail;
        copia.size = auxSize;
    }
    return *this;
}

template <typename T>
int DoublyLinkedList<T>::getSize() const {
    return size;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return head == nullptr;
}

template <typename T>
void DoublyLinkedList<T>::addFirst(T data) {
    // creamos un nuevo nodo
    NodeD<T>* aux = new NodeD<T>(data);
    // apuntamos su next a head
    aux->next = head;

    if (head == nullptr) {
        // si la lista esta vacia, tail tambien apunta al nuevo nodo
        tail = aux;
    } else {
        // actualizamos el prev del primer nodo
        head->prev = aux;
    }

    head = aux;
    size++;
}

template <typename T>
void DoublyLinkedList<T>::addLast(T data) {
    // creamos un nuevo nodo
    NodeD<T>* aux = new NodeD<T>(data);
    // apuntamos su prev a tail
    aux->prev = tail;

    if (tail == nullptr) {
        // si la lista esta vacia, head tambien apunta al nuevo nodo
        head = aux;
    } else {
        // apuntamos el next del ultimo nodo al nuevo
        tail->next = aux;
    }

    tail = aux;
    size++;
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, T data) {
    // validamos que el indice exista: se inserta a su derecha
    if (index >= 0 && index < size) {
        if (index == size - 1) {
            // si es el ultimo, usamos addLast
            addLast(data);
        } else {
            int auxIndex = 0;
            NodeD<T>* aux = head;

            while (auxIndex < index) {
                aux = aux->next;
                auxIndex++;
            }

            NodeD<T>* auxNew = new NodeD<T>(data);
            auxNew->prev = aux;
            auxNew->next = aux->next;
            aux->next->prev = auxNew;
            aux->next = auxNew;
            size++;
        }
    } else {
        throw out_of_range("Indice invalido");
    }
}

template <typename T>
bool DoublyLinkedList<T>::deleteAt(int index) {
    if (index < 0 || index >= size) {
        return false;
    }

    // validamos si solo hay un elemento
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else if (index == 0) {
        // borramos el primero
        NodeD<T>* aux = head;
        head = head->next;
        head->prev = nullptr;
        delete aux;
    } else if (index == size - 1) {
        // borramos el ultimo
        NodeD<T>* aux = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete aux;
    } else {
        // buscamos desde head o tail, segun donde este mas cerca
        NodeD<T>* aux;
        int auxIndex;

        if (index <= (size - 1) / 2) {
            aux = head;
            auxIndex = 0;
            while (auxIndex < index) {
                aux = aux->next;
                auxIndex++;
            }
        } else {
            aux = tail;
            auxIndex = size - 1;
            while (auxIndex > index) {
                aux = aux->prev;
                auxIndex--;
            }
        }

        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
        delete aux;
    }

    size--;
    return true;
}

template <typename T>
int DoublyLinkedList<T>::findData(T data) const {
    NodeD<T>* aux = head;
    int auxIndex = 0;

    while (aux != nullptr) {
        if (aux->data == data) {
            return auxIndex;
        }
        aux = aux->next;
        auxIndex++;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::deleteData(T data) {
    // buscamos el primer dato igual y borramos su posicion
    int index = findData(data);
    if (index == -1) {
        return false;
    }
    return deleteAt(index);
}

template <typename T>
T DoublyLinkedList<T>::getData(int index) const {
    return (*this)[index];
}

template <typename T>
void DoublyLinkedList<T>::updateData(T oldData, T newData) {
    int index = findData(oldData);
    if (index == -1) {
        throw out_of_range("No se encontro el dato a actualizar");
    }
    updateAt(index, newData);
}

template <typename T>
void DoublyLinkedList<T>::updateAt(int index, T newData) {
    (*this)[index] = newData;
}

template <typename T>
T& DoublyLinkedList<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Indice invalido");
    }

    NodeD<T>* aux = head;
    int auxIndex = 0;
    while (auxIndex < index) {
        aux = aux->next;
        auxIndex++;
    }
    return aux->data;
}

template <typename T>
const T& DoublyLinkedList<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Indice invalido");
    }

    NodeD<T>* aux = head;
    int auxIndex = 0;
    while (auxIndex < index) {
        aux = aux->next;
        auxIndex++;
    }
    return aux->data;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    NodeD<T>* aux = head;
    while (aux != nullptr) {
        NodeD<T>* siguiente = aux->next;
        delete aux;
        aux = siguiente;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
void DoublyLinkedList<T>::sort() {
    // Bubble Sort: intercambiamos los datos de dos nodos vecinos
    if (size < 2) {
        return;
    }

    bool cambio;
    do {
        cambio = false;
        NodeD<T>* aux = head;
        while (aux->next != nullptr) {
            if (aux->data > aux->next->data) {
                T auxData = aux->data;
                aux->data = aux->next->data;
                aux->next->data = auxData;
                cambio = true;
            }
            aux = aux->next;
        }
    } while (cambio);
}

template <typename T>
void DoublyLinkedList<T>::duplicate() {
    // por ejemplo 1,2,3 pasa a 1,1,2,2,3,3
    NodeD<T>* aux = head;
    while (aux != nullptr) {
        NodeD<T>* auxNew = new NodeD<T>(aux->data);
        auxNew->prev = aux;
        auxNew->next = aux->next;

        if (aux->next != nullptr) {
            aux->next->prev = auxNew;
        } else {
            tail = auxNew;
        }

        aux->next = auxNew;
        size++;
        aux = auxNew->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::removeDuplicates() {
    // ordenamos para que los valores iguales queden juntos
    sort();
    NodeD<T>* aux = head;

    while (aux != nullptr && aux->next != nullptr) {
        if (aux->data == aux->next->data) {
            NodeD<T>* auxDelete = aux->next;
            aux->next = auxDelete->next;

            if (auxDelete->next != nullptr) {
                auxDelete->next->prev = aux;
            } else {
                tail = aux;
            }

            delete auxDelete;
            size--;
        } else {
            aux = aux->next;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::printForward(ostream& out) const {
    if (head == nullptr) {
        out << "(lista vacia)";
        return;
    }

    NodeD<T>* aux = head;
    while (aux != nullptr) {
        out << aux->data;
        if (aux->next != nullptr) {
            out << " <-> ";
        }
        aux = aux->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::printBackward(ostream& out) const {
    if (tail == nullptr) {
        out << "(lista vacia)";
        return;
    }

    NodeD<T>* aux = tail;
    while (aux != nullptr) {
        out << aux->data;
        if (aux->prev != nullptr) {
            out << " <-> ";
        }
        aux = aux->prev;
    }
}

#endif /* DoublyLinkedList_h */