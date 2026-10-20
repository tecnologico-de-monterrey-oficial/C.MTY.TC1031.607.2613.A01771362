#pragma once
#include <iostream>
#include <string>
// ---------- Lista ligada simple (head + tail) ----------
template <typename T>
class LinkedList {
public:
    struct Node { T data; Node* next; Node(const T& d) : data(d), next(nullptr) {} };
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~LinkedList() { while (head) popFront(); }
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;
    void pushFront(const T& d) { Node* n = new Node(d); n->next = head; head = n; if (!tail) tail = n; count++; }
    void pushBack(const T& d) { Node* n = new Node(d); if (tail) tail->next = n; else head = n; tail = n; count++; }
    bool popFront(T* out = nullptr) {
        if (!head) return false;
        Node* n = head; if (out) *out = n->data;
        head = n->next; if (!head) tail = nullptr;
        delete n; count--; return true;
    }
    T* front() { return head ? &head->data : nullptr; }
    int size() const { return count; }
    bool empty() const { return count == 0; }
    void print() const { for (Node* n = head; n; n = n->next) std::cout << n->data << " "; std::cout << "\n"; }
private:
    Node *head, *tail; int count;
};
// ---------- Pila (sobre la lista ligada) ----------
template <typename T>
class Stack {
public:
    void push(const T& d) { list.pushFront(d); }
    bool pop(T& out) { if (list.empty()) { std::cout << "[Pila] Error: pop sobre pila vacia.\n"; return false; } return list.popFront(&out); }
    bool peek(T& out) { if (list.empty()) { std::cout << "[Pila] La pila esta vacia.\n"; return false; } out = *list.front(); return true; }
    bool isEmpty() const { return list.empty(); }
    int size() const { return list.size(); }
private:
    LinkedList<T> list;
};
// ---------- Fila (sobre la lista ligada) ----------
template <typename T>
class Queue {
public:
    void enqueue(const T& d) { list.pushBack(d); }
    bool dequeue(T& out) { if (list.empty()) { std::cout << "[Fila] Error: dequeue sobre fila vacia.\n"; return false; } return list.popFront(&out); }
    bool front(T& out) { if (list.empty()) { std::cout << "[Fila] La fila esta vacia.\n"; return false; } out = *list.front(); return true; }
    bool isEmpty() const { return list.empty(); }
    int size() const { return list.size(); }
private:
    LinkedList<T> list;
};
// ---------- Lista doblemente ligada ----------
template <typename T>
class DoublyLinkedList {
public:
    struct Node { T data; Node *prev, *next; Node(const T& d) : data(d), prev(nullptr), next(nullptr) {} };
    Node *head, *tail;
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~DoublyLinkedList() { clear(); }
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    void clear() { while (head) { Node* n = head; head = head->next; delete n; } tail = nullptr; count = 0; }
    void pushFront(const T& d) { Node* n = new Node(d); n->next = head; if (head) head->prev = n; else tail = n; head = n; count++; }
    void pushBack(const T& d) { Node* n = new Node(d); n->prev = tail; if (tail) tail->next = n; else head = n; tail = n; count++; }
    void insertAfter(Node* ref, const T& d) {
        if (!ref) { pushFront(d); return; }
        if (ref == tail) { pushBack(d); return; }
        Node* n = new Node(d); n->prev = ref; n->next = ref->next;
        ref->next->prev = n; ref->next = n; count++;
    }
    void remove(Node* n) {
        if (!n) return;
        if (n->prev) n->prev->next = n->next; else head = n->next;
        if (n->next) n->next->prev = n->prev; else tail = n->prev;
        delete n; count--;
    }
    int size() const { return count; }
    // Tras reordenar usando solo 'next', reconstruye prev, tail y count.
    void relink() {
        Node* p = nullptr; int c = 0;
        for (Node* n = head; n; n = n->next) { n->prev = p; p = n; c++; }
        tail = p; count = c;
    }
private:
    int count;
};
