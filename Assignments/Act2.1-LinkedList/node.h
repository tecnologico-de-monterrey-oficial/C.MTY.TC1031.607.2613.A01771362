#pragma once
#include <memory>

template <typename T>
struct Node {
    T data;
    <Node<T>> next;

    Node(const T& value) : data(value), next(nullptr) {}
    Node(const T& value, <Node<T>> nextNode) : data(value), next(std::move(nextNode)) {} 
};