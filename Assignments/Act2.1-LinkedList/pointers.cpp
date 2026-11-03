// Practica independiente de apuntadores (no es parte del menu LinkedList).
#include <iostream>
#include <memory>
#include "Fraction.h"
using namespace std;

int main() {
    int x = 42;
    int* p = &x;
    cout << "x: " << x << "\n";
    cout << "direccion de x: " << &x << "\n";
    cout << "valor de p: " << p << "\n";
    cout << "valor apuntado por p: " << *p << "\n";

    cout << "valores de q\n";
    int* q = new int(5);
    cout << "direccion q: " << q << "\n";
    cout << "dato q: " << *q << "\n";
    delete q;
    q = nullptr;
    cout << "q luego de delete: " << q << " (NO se desreferencia)\n";

    Fraction* f = new Fraction(2, 3);
    f->print();
    cout << "Numerador: " << f->getNumerator()
         << ", Denominador: " << f->getDenominator() << "\n";
    delete f;
    f = nullptr;

    unique_ptr<Fraction> g = make_unique<Fraction>(3, 4);
    g->print();
    cout << "Numerador: " << g->getNumerator()
         << ", Denominador: " << g->getDenominator() << "\n";
    return 0;
}
