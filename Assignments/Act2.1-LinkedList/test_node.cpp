// Prueba independiente de Node<T> con apuntadores validos.
#include <iostream>
#include "Node.h"
using namespace std;

int main() {
    Node<int> node1(20);
    Node<int> node2(10, &node1);

    cout << "node2 data: " << node2.data << "\n";
    cout << "node2->next data: " << node2.next->data << "\n";
    cout << "node1 data: " << node1.data << "\n";
    return 0;
}
