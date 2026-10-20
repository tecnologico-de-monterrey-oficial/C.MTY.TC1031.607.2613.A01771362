#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include "LinkedList.h"

template <typename T>
class Stack {
private:
    LinkedList<T> data_;
public:
    void push(const T& value) { data_.pushFront(value); }
    bool pop(T& value) { return data_.popFront(value); }
    bool peek(T& value) const { return data_.getFront(value); }
    bool isEmpty() const { return data_.empty(); }
    std::size_t size() const { return data_.size(); }
};

#endif
