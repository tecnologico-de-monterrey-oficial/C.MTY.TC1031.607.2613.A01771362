#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <iostream>
#include "Node.h"

// Implementacion propia. Inserciones/eliminacion de extremos indicados: O(1).
template <typename T>
class LinkedList {
private:
    Node<T>* head_ = nullptr;
    Node<T>* tail_ = nullptr;
    std::size_t count_ = 0;

public:
    LinkedList() = default;
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;
    ~LinkedList() { clear(); }

    void pushFront(const T& value) {
        Node<T>* node = new Node<T>(value);
        node->next = head_;
        head_ = node;
        if (tail_ == nullptr) tail_ = node;
        ++count_;
    }

    void pushBack(const T& value) {
        Node<T>* node = new Node<T>(value);
        if (tail_ != nullptr) tail_->next = node;
        else head_ = node;
        tail_ = node;
        ++count_;
    }

    // Devuelve false si no habia un primer nodo; no termina el programa.
    bool popFront(T& removed) {
        if (!head_) return false;
        Node<T>* node = head_;
        removed = node->data;
        head_ = node->next;
        if (!head_) tail_ = nullptr;
        delete node;
        --count_;
        return true;
    }

    bool getFront(T& result) const {
        if (!head_) return false;
        result = head_->data;
        return true;
    }

    bool empty() const { return count_ == 0; }
    std::size_t size() const { return count_; }

    void print(std::ostream& out = std::cout) const {
        for (Node<T>* p = head_; p != nullptr; p = p->next) {
            if (p != head_) out << " -> ";
            out << p->data;
        }
        if (empty()) out << "(vacia)";
        out << '\n';
    }

    void clear() {
        while (head_) {
            Node<T>* old = head_;
            head_ = head_->next;
            delete old;
        }
        tail_ = nullptr;
        count_ = 0;
    }
};

#endif
