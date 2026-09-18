//Pamela Hernández Camacho
//A011771362
#include <iostream>

cout<< "Valores de q"<< endl;
int* q = new int(5);
cout<< q<< endl;
cout<< *q<< endl;


delete q; //le asigno espacio de memoria a un progrmaa es exclusivo del programa 
cout<< q <<endl;
cout<< *q <<endl; //

//investigar fracción

//direccion de memoria hay un objeto de tipo fracción

#include <iostream>
#include <memory>
using namespace std;

#include "Fraction.h"

int main() {

    int x = 42;
    int* p = &x;
    
    cout << x << endl;
    cout << &x << endl;
    cout << p << endl;
    cout << *p << endl;

    cout << "valores de q" << endl;
    int* q = new int(5);
    cout << q << endl;
    cout << *q << endl;

    delete q;
    cout << q << endl;
    cout << *q << endl;

    Fraction* f = new Fraction(2, 3);

    f->print();
    cout << f->getDenominator() << "/" << f->getNumerator() << endl;
    delete f;
    f = nullptr;

    auto g = std::make_unique<Fraction>(3, 4);
    g->print();
    cout << g->getDenominator() << "/" << g->getNumerator() << endl;


    return 0;
}