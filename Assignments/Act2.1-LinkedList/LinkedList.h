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