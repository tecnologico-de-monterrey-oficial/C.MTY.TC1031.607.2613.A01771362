#include <cassert>
#include <iostream>
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "DoublyLinkedList.h"

using namespace std;
int main() {
    int value = 0;
    cout << "=== PARTE A: PRUEBAS DE ESTRUCTURAS ===\n";

    LinkedList<int> list;
    assert(list.empty() && list.size() == 0);
    if (!list.popFront(value)) cout << "Lista vacia: no se puede eliminar.\n";
    list.pushFront(2); list.pushFront(1); list.pushBack(3);
    cout << "Lista simple (1 2 3): "; list.print();
    assert(list.size() == 3);
    assert(list.popFront(value) && value == 1);
    assert(list.popFront(value) && value == 2);
    assert(list.popFront(value) && value == 3);
    assert(list.empty());
    list.pushBack(9);
    assert(list.getFront(value) && value == 9);
    cout << "Lista un elemento: "; list.print();

    Stack<int> stack;
    if (!stack.pop(value)) cout << "Pila vacia: no se puede hacer pop.\n";
    stack.push(10); stack.push(20); stack.push(30);
    assert(stack.peek(value) && value == 30);
    cout << "Pila LIFO: ";
    while (stack.pop(value)) cout << value << ' ';
    cout << "\n";
    assert(stack.isEmpty());
    stack.push(7); assert(stack.pop(value) && value == 7);

    Queue<int> queue;
    if (!queue.dequeue(value)) cout << "Fila vacia: no se puede hacer dequeue.\n";
    queue.enqueue(10); queue.enqueue(20); queue.enqueue(30);
    assert(queue.front(value) && value == 10);
    cout << "Fila FIFO: ";
    while (queue.dequeue(value)) cout << value << ' ';
    cout << "\n";
    assert(queue.isEmpty());
    queue.enqueue(8); assert(queue.dequeue(value) && value == 8);

    DoublyLinkedList<int> doubly;
    assert(doubly.empty() && doubly.size() == 0);
    if (!doubly.removeNode(nullptr)) cout << "Lista doble vacia: nodo inexistente.\n";
    auto* second = doubly.pushBack(2);
    doubly.pushFront(1);
    auto* fourth = doubly.pushBack(4);
    auto* third = doubly.insertAfter(second, 3);
    assert(third && fourth && doubly.size() == 4);
    cout << "Lista doble adelante: "; doubly.printForward();
    cout << "Lista doble atras: "; doubly.printBackward();
    assert(doubly.removeNode(third));
    assert(doubly.removeNode(doubly.head()));
    assert(doubly.removeNode(doubly.tail()));
    assert(doubly.size() == 1 && doubly.head() == second && doubly.tail() == second);
    cout << "Lista doble un elemento: "; doubly.printForward();
    assert(doubly.removeNode(doubly.head()) && doubly.empty());
    // Merge Sort debe reconectar prev/next, conservar extremos y mantener los empates.
    DoublyLinkedList<int> ordering;
    ordering.pushBack(4); ordering.pushBack(2); ordering.pushBack(2);
    ordering.pushBack(1); ordering.pushBack(3);
    SortMetrics stats = ordering.sortStable([](int a, int b) {return a < b;});
    assert(stats.comparisons > 0 && stats.maxDepth > 0);
    int expected[] = {1, 2, 2, 3, 4};
    int i = 0;
    NodeD<int>* previous = nullptr;
    for (NodeD<int>* p = ordering.head(); p; p = p->next) {
        assert(i < 5 && p->data == expected[i++]);
        assert(p->prev == previous);
        previous = p;
    }
    assert(i == 5 && previous == ordering.tail());
    cout << "Merge Sort nodos: "; ordering.printForward();
    cout << "Todas las pruebas terminaron correctamente.\n";
}
