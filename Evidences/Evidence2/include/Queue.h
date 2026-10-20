#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include "LinkedList.h"

template <typename T>
class Queue {
private:
    LinkedList<T> data_;
public:
    void enqueue(const T& value) { data_.pushBack(value); }
    bool dequeue(T& value) { return data_.popFront(value); }
    bool front(T& value) const { return data_.getFront(value); }
    bool isEmpty() const { return data_.empty(); }
    std::size_t size() const { return data_.size(); }
};

#endif
