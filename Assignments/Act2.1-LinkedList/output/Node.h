// Nodo generico de una lista simplemente enlazada.
#pragma once

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    explicit Node(const T& value) : data(value), next(nullptr) {}
    Node(const T& value, Node<T>* nextNode) : data(value), next(nextNode) {}
};
