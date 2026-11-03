#pragma once

// Nodo de un arbol binario, generico con template
template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
};