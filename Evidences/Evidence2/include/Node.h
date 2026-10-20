#ifndef NODE_H
#define NODE_H

// Nodo para una lista simplemente ligada.
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    explicit Node(const T& value) : data(value), next(nullptr) {}
};

#endif
