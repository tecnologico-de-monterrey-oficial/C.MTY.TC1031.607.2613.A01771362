Main · CPP
// Pamela Hernandez Camacho
// A01771362
 
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include "Queue.h"
 
using namespace std;
 
// Estructura Cliente
struct Cliente {
    string nombre;
    int boletos;
};
 
// Lee un entero validando la entrada
int leerEntero(const string& mensaje) {
    int valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Intenta de nuevo: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}
 
int main() {
 
    // Queue que guarda clientes
    Queue<Cliente> fila;
 
    int opcion;
 
    do {
 
        cout << "\n===== TAQUILLA DE BOLETOS =====" << endl;
        cout << "1. Llegada de un nuevo cliente" << endl;
        cout << "2. Atender al siguiente cliente" << endl;
        cout << "3. Ver al siguiente cliente" << endl;
        cout << "4. Mostrar cuantas personas hay en la fila" << endl;
        cout << "5. Salir" << endl;
 
        opcion = leerEntero("\nSelecciona una opcion: ");
 
        switch (opcion) {
 
            // NUEVO CLIENTE
            case 1: {
                Cliente nuevo;
 
                cout << "\nNombre del cliente: ";
                getline(cin, nuevo.nombre);
 
                nuevo.boletos = leerEntero("Cantidad de boletos: ");
                while (nuevo.boletos <= 0) {
                    nuevo.boletos = leerEntero("Debe ser mayor a 0. Cantidad de boletos: ");
                }
 
                fila.push(nuevo);
 
                cout << "\nCliente agregado correctamente." << endl;
                break;
            }
 
            // ATENDER CLIENTE
            case 2: {
                try {
                    Cliente atendido = fila.pop();
 
                    cout << "\nCliente atendido:" << endl;
                    cout << "Nombre: " << atendido.nombre << endl;
                    cout << "Boletos: " << atendido.boletos << endl;
                }
                catch (runtime_error& error) {
                    cout << "\n" << error.what() << endl;
                }
                break;
            }
 
            // VER SIGUIENTE CLIENTE
            case 3: {
                try {
                    Cliente siguiente = fila.front();
 
                    cout << "\nSiguiente cliente:" << endl;
                    cout << "Nombre: " << siguiente.nombre << endl;
                    cout << "Boletos: " << siguiente.boletos << endl;
                }
                catch (runtime_error& error) {
                    cout << "\n" << error.what() << endl;
                }
                break;
            }
 
            // MOSTRAR PERSONAS
            case 4: {
                cout << "\nPersonas en la fila: " << fila.size() << endl;
                break;
            }
 
            // SALIR
            case 5: {
                cout << "\nSaliendo del programa..." << endl;
                break;
            }
 
            default: {
                cout << "\nOpcion invalida." << endl;
            }
        }
 
    } while (opcion != 5);
 
    return 0;
}