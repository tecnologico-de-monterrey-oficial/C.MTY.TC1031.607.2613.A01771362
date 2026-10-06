#include <iostream>
#include <string>
#include "Queue.h"

using namespace std;


// Estructura Cliente
struct Cliente {
    string nombre;
    int boletos;
};


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

        cout << "\nSelecciona una opcion: ";
        cin >> opcion;


        switch (opcion) {

            // NUEVO CLIENTE
            case 1: {

                Cliente nuevo;

                cout << "\nNombre del cliente: ";

                cin.ignore();

                getline(cin, nuevo.nombre);

                cout << "Cantidad de boletos: ";
                cin >> nuevo.boletos;

                // Agregamos el cliente al Queue
                fila.push(nuevo);

                cout << "\nCliente agregado correctamente." << endl;

                break;
            }


            // ATENDER CLIENTE
            case 2: {

                try {

                    // pop elimina y regresa al primer cliente
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

                    // front muestra al primero sin borrarlo
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

                cout << "\nPersonas en la fila: "
                     << fila.size()
                     << endl;

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