// Pamela Hernandez Camacho
// A01771362

// Pruebas del ADT Queue<T> (push, pop, front, size, copia y asignacion)

#include <iostream>
#include <string>
#include <stdexcept>
#include "Queue.h"

using namespace std;

int pruebas = 0;
int fallas = 0;

// Revisa una condicion e imprime PASS o FAIL
void revisar(bool condicion, const string& descripcion) {
    pruebas++;
    if (condicion) {
        cout << "[PASS] " << descripcion << endl;
    }
    else {
        fallas++;
        cout << "[FAIL] " << descripcion << endl;
    }
}

// Estructura de prueba (igual que la de la taquilla)
struct Cliente {
    string nombre;
    int boletos;
};

int main() {

    cout << "===== Queue<int> =====" << endl;

    Queue<int> q;

    revisar(q.empty(), "Un Queue nuevo esta vacio");
    revisar(q.size() == 0, "El tamano inicial es 0");

    q.push(10);
    q.push(5);
    q.push(7);

    revisar(q.size() == 3, "Despues de 3 push el tamano es 3");
    revisar(q.front() == 10, "front() regresa el primero que entro (10)");
    revisar(q.size() == 3, "front() no borra el elemento");
    revisar(q.pop() == 10, "pop() regresa 10 (FIFO)");
    revisar(q.pop() == 5, "pop() regresa 5");
    revisar(q.front() == 7, "front() ahora es 7");
    revisar(q.pop() == 7, "pop() regresa 7");
    revisar(q.empty(), "Despues de sacar todo, el Queue queda vacio");

    // Excepciones con el Queue vacio
    bool lanzoPop = false;
    try {
        q.pop();
    }
    catch (runtime_error&) {
        lanzoPop = true;
    }
    revisar(lanzoPop, "pop() en un Queue vacio lanza runtime_error");

    bool lanzoFront = false;
    try {
        q.front();
    }
    catch (runtime_error&) {
        lanzoFront = true;
    }
    revisar(lanzoFront, "front() en un Queue vacio lanza runtime_error");

    // El Queue se puede volver a usar despues de vaciarse
    q.push(99);
    revisar(q.front() == 99 && q.size() == 1, "Se puede volver a usar despues de vaciarse");


    cout << "\n===== Queue<string> =====" << endl;

    Queue<string> s;
    s.push("a");
    s.push("b");
    s.push("c");

    revisar(s.pop() == "a", "pop() regresa \"a\"");
    revisar(s.front() == "b", "front() regresa \"b\"");
    revisar(s.size() == 2, "El tamano es 2");


    cout << "\n===== Queue<Cliente> =====" << endl;

    Queue<Cliente> fila;
    fila.push({"Ana", 3});
    fila.push({"Luis", 1});

    Cliente c = fila.front();
    revisar(c.nombre == "Ana" && c.boletos == 3, "front() regresa a Ana con 3 boletos");

    c = fila.pop();
    revisar(c.nombre == "Ana", "pop() atiende primero a Ana (orden de llegada)");

    c = fila.pop();
    revisar(c.nombre == "Luis" && c.boletos == 1, "pop() atiende despues a Luis con 1 boleto");
    revisar(fila.empty(), "La fila queda vacia");


    cout << "\n===== Copia y asignacion =====" << endl;

    Queue<int> original;
    original.push(1);
    original.push(2);

    Queue<int> copia(original);
    copia.pop();

    revisar(original.size() == 2 && copia.size() == 1,
            "Constructor de copia: modificar la copia no cambia la original");

    Queue<int> otra;
    otra.push(100);
    otra = original;

    revisar(otra.size() == 2 && otra.front() == 1,
            "operator=: reemplaza el contenido por el de la otra fila");

    otra.pop();
    revisar(original.front() == 1, "operator=: las filas son independientes");

    otra = otra;
    revisar(otra.size() == 1, "operator=: asignarse a si misma no daña la fila");


    cout << "\n===== Resumen =====" << endl;
    cout << (pruebas - fallas) << " de " << pruebas << " pruebas pasaron." << endl;

    return fallas == 0 ? 0 : 1;
}
