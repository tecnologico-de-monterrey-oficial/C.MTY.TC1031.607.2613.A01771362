#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <iostream>

// Nodo doble. 'prev' y 'next' siempre deben conservarse consistentes.
template <typename T>
struct NodeD {
    T data;
    NodeD<T>* prev;
    NodeD<T>* next;
    explicit NodeD(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

struct SortMetrics {
    unsigned long long comparisons = 0;
    std::size_t maxDepth = 0;
};

template <typename T>
class DoublyLinkedList {
private:
    NodeD<T>* head_ = nullptr;
    NodeD<T>* tail_ = nullptr;
    std::size_t count_ = 0;

    // Divide una cadena, no crea ni copia nodos.
    static NodeD<T>* split(NodeD<T>* first) {
        NodeD<T>* slow = first;
        NodeD<T>* fast = first->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        NodeD<T>* second = slow->next;
        slow->next = nullptr;
        if (second) second->prev = nullptr;
        return second;
    }

    template <typename Less>
    static NodeD<T>* merge(NodeD<T>* left, NodeD<T>* right,
                            Less less, SortMetrics& metrics) {
        NodeD<T>* first = nullptr;
        NodeD<T>* last = nullptr;
        while (left || right) {
            NodeD<T>* chosen = nullptr;
            if (!right) {
                chosen = left;
                left = left->next;
            } else if (!left) {
                chosen = right;
                right = right->next;
            } else {
                ++metrics.comparisons;
                // Elegir el nodo izquierdo cuando las claves son iguales:
                // Merge Sort ESTABLE (preserva el orden original del empate).
                if (!less(right->data, left->data)) {
                    chosen = left;
                    left = left->next;
                } else {
                    chosen = right;
                    right = right->next;
                }
            }
            chosen->prev = last;
            chosen->next = nullptr;
            if (last) last->next = chosen;
            else first = chosen;
            last = chosen;
        }
        return first;
    }

    template <typename Less>
    static NodeD<T>* mergeSort(NodeD<T>* first, Less less,
                               SortMetrics& metrics, std::size_t depth) {
        if (depth > metrics.maxDepth) metrics.maxDepth = depth;
        if (!first || !first->next) return first;
        NodeD<T>* second = split(first);
        first = mergeSort(first, less, metrics, depth + 1);
        second = mergeSort(second, less, metrics, depth + 1);
        return merge(first, second, less, metrics);
    }

public:
    DoublyLinkedList() = default;
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    ~DoublyLinkedList() { clear(); }

    NodeD<T>* head() const { return head_; }
    NodeD<T>* tail() const { return tail_; }
    std::size_t size() const { return count_; }
    bool empty() const { return count_ == 0; }

    NodeD<T>* pushFront(const T& value) {
        NodeD<T>* p = new NodeD<T>(value);
        p->next = head_;
        if (head_) head_->prev = p;
        else tail_ = p;
        head_ = p;
        ++count_;
        return p;
    }
    NodeD<T>* pushBack(const T& value) {
        NodeD<T>* p = new NodeD<T>(value);
        p->prev = tail_;
        if (tail_) tail_->next = p;
        else head_ = p;
        tail_ = p;
        ++count_;
        return p;
    }
    NodeD<T>* insertAfter(NodeD<T>* current, const T& value) {
        if (!current) return nullptr;
        if (current == tail_) return pushBack(value);
        NodeD<T>* p = new NodeD<T>(value);
        p->prev = current;
        p->next = current->next;
        current->next->prev = p;
        current->next = p;
        ++count_;
        return p;
    }
    // Se debe pasar un nodo perteneciente a esta lista.
    bool removeNode(NodeD<T>* p) {
        if (!p) return false;
        if (p->prev) p->prev->next = p->next;
        else head_ = p->next;
        if (p->next) p->next->prev = p->prev;
        else tail_ = p->prev;
        delete p;
        --count_;
        return true;
    }
    void printForward(std::ostream& out = std::cout) const {
        for (NodeD<T>* p = head_; p; p = p->next) out << p->data << ' ';
        if (empty()) out << "(vacia)";
        out << '\n';
    }
    void printBackward(std::ostream& out = std::cout) const {
        for (NodeD<T>* p = tail_; p; p = p->prev) out << p->data << ' ';
        if (empty()) out << "(vacia)";
        out << '\n';
    }
    template <typename Less>
    bool isSorted(Less less) const {
        for (NodeD<T>* p = head_; p && p->next; p = p->next) {
            if (less(p->next->data, p->data)) return false;
        }
        return true;
    }
    template <typename Less>
    SortMetrics sortStable(Less less) {
        SortMetrics metrics;
        if (head_) head_ = mergeSort(head_, less, metrics, 1);
        tail_ = head_;
        while (tail_ && tail_->next) tail_ = tail_->next;
        return metrics;
    }
    void clear() {
        while (head_) {
            NodeD<T>* old = head_;
            head_ = head_->next;
            delete old;
        }
        tail_ = nullptr;
        count_ = 0;
    }
};

#endif
