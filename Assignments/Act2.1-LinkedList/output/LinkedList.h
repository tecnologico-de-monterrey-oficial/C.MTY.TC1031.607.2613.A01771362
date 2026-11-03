// LinkedList.h - Implementacion de ADT Lista Enlazada con templates.
// Indices basados en cero: 0, 1, 2, ...
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

    Node<T>* nodeAt(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Indice fuera de rango");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    void swap(LinkedList<T>& other) noexcept {
        std::swap(head, other.head);
        std::swap(size, other.size);
    }

public:
    LinkedList() : head(nullptr), size(0) {}

    // Constructor de copia: crea nodos independientes.
    LinkedList(const LinkedList<T>& other) : head(nullptr), size(0) {
        try {
            for (Node<T>* current = other.head; current != nullptr; current = current->next) {
                addLast(current->data);
            }
        } catch (...) {
            clear();
            throw;
        }
    }

    ~LinkedList() { clear(); }

    // Sobrecarga de =: copia profunda y maneja autoasignacion.
    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            LinkedList<T> copy(other);
            swap(copy);
        }
        return *this;
    }

    void clear() noexcept {
        while (head != nullptr) {
            Node<T>* old = head;
            head = head->next;
            delete old;
        }
        size = 0;
    }

    int getSize() const { return size; }
    bool empty() const { return size == 0; }

    // 1. Inserta al principio.
    void addFirst(const T& data) {
        head = new Node<T>(data, head);
        ++size;
    }

    // 2. Inserta al final.
    void addLast(const T& data) {
        Node<T>* node = new Node<T>(data);
        if (head == nullptr) {
            head = node;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = node;
        }
        ++size;
    }

    // 3. Inserta EN el indice indicado. Valido: 0 <= index <= size.
    void insert(int index, const T& data) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Indice de insercion fuera de rango");
        }
        if (index == 0) {
            addFirst(data);
        } else if (index == size) {
            addLast(data);
        } else {
            Node<T>* previous = nodeAt(index - 1);
            previous->next = new Node<T>(data, previous->next);
            ++size;
        }
    }

    // 4. Borra la primera aparicion del dato.
    bool deleteData(const T& data) {
        if (head == nullptr) return false;
        if (head->data == data) {
            Node<T>* old = head;
            head = head->next;
            delete old;
            --size;
            return true;
        }
        Node<T>* previous = head;
        while (previous->next != nullptr && !(previous->next->data == data)) {
            previous = previous->next;
        }
        if (previous->next == nullptr) return false;
        Node<T>* old = previous->next;
        previous->next = old->next;
        delete old;
        --size;
        return true;
    }

    // 5. Borra por posicion. Indice invalido: false.
    bool deleteAt(int index) {
        if (index < 0 || index >= size) return false;
        Node<T>* old = nullptr;
        if (index == 0) {
            old = head;
            head = head->next;
        } else {
            Node<T>* previous = nodeAt(index - 1);
            old = previous->next;
            previous->next = old->next;
        }
        delete old;
        --size;
        return true;
    }

    // 6. Lee el valor de un indice. Indice invalido: out_of_range.
    T getData(int index) const { return nodeAt(index)->data; }

    // 7. Actualiza la primera coincidencia. Si no existe: out_of_range.
    void updateData(const T& oldData, const T& newData) {
        int index = findData(oldData);
        if (index == -1) {
            throw std::out_of_range("Dato no encontrado para actualizar");
        }
        nodeAt(index)->data = newData;
    }

    // 8. Actualiza por posicion. Indice invalido: out_of_range.
    void updateAt(int index, const T& newData) { nodeAt(index)->data = newData; }

    // 9. Busca el primer indice; -1 si no existe.
    int findData(const T& data) const {
        int index = 0;
        for (Node<T>* current = head; current != nullptr; current = current->next, ++index) {
            if (current->data == data) return index;
        }
        return -1;
    }

    // 10 y 11. Lectura y escritura con [].
    T& operator[](int index) { return nodeAt(index)->data; }
    const T& operator[](int index) const { return nodeAt(index)->data; }

    // Alias para que tambien funcione tu codigo inicial.
    void push_front(const T& data) { addFirst(data); }
    void push_back(const T& data) { addLast(data); }

    void print(std::ostream& os = std::cout) const {
        os << "[";
        Node<T>* current = head;
        while (current != nullptr) {
            os << current->data;
            current = current->next;
            if (current != nullptr) os << " -> ";
        }
        os << "]\n";
    }
};

#endif  // LINKEDLIST_H
