
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include "DoublyLinkedList.h"

using namespace std;

// Lectura generica para int y string
template <typename T>
T pedir(const string& mensaje) {
    T valor;
    while (true) {
        cout << mensaje;

        if (cin >> valor) {
            return valor;
        }

        if (cin.eof()) {
            throw runtime_error("Fin de la entrada");
        }

        cout << "Entrada invalida. Intenta otra vez.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Generar datos aleatorios
template <typename T>
T datoAleatorio();

template <>
int datoAleatorio<int>() {
    return rand() % 21;
}

template <>
string datoAleatorio<string>() {
    const string palabras[] = {
        "sol", "luna", "mar", "casa",
        "arbol", "nube", "flor", "rio"
    };

    return palabras[rand() % 8];
}

// Crear lista
template <typename T>
void crearLista(DoublyLinkedList<T>& lista) {
    int cantidad;

    do {
        cantidad = pedir<int>("Cantidad de elementos (0 a 100): ");

        if (cantidad < 0 || cantidad > 100) {
            cout << "Usa un valor entre 0 y 100.\n";
        }

    } while (cantidad < 0 || cantidad > 100);

    int modo;

    do {
        modo = pedir<int>("1) Capturar datos  2) Aleatorios: ");

        if (modo != 1 && modo != 2) {
            cout << "Opcion invalida.\n";
        }

    } while (modo != 1 && modo != 2);

    lista.clear();

    for (int i = 0; i < cantidad; i++) {
        if (modo == 1) {
            lista.addLast(
                pedir<T>("Elemento " + to_string(i) + ": ")
            );
        } else {
            lista.addLast(datoAleatorio<T>());
        }
    }

    cout << "Lista creada: ";
    lista.printForward();
    cout << '\n';
}

// Menu de operaciones
template <typename T>
void menuLista() {
    DoublyLinkedList<T> lista;
    DoublyLinkedList<T> copia;

    int opcion;

    do {
        cout << "\n========== DOUBLY LINKED LIST ==========\n"
             << "Lista (" << lista.getSize() << " elementos): ";

        lista.printForward();

        cout << "\n"
             << " 1. Crear lista (captura o aleatoria)\n"
             << " 2. Agregar al inicio (addFirst)\n"
             << " 3. Agregar al final (addLast)\n"
             << " 4. Insertar despues de un indice (insert)\n"
             << " 5. Borrar por valor (deleteData)\n"
             << " 6. Borrar por indice (deleteAt)\n"
             << " 7. Obtener por indice (getData)\n"
             << " 8. Actualizar por valor (updateData)\n"
             << " 9. Actualizar por indice (updateAt)\n"
             << "10. Buscar valor (findData)\n"
             << "11. Leer con operador []\n"
             << "12. Modificar con operador []\n"
             << "13. Copiar con operador =\n"
             << "14. Limpiar lista (clear)\n"
             << "15. Ordenar (sort)\n"
             << "16. Duplicar cada nodo (duplicate)\n"
             << "17. Quitar repetidos (removeDuplicates)\n"
             << "18. Mostrar desde inicio y fin\n"
             << " 0. Regresar al menu de tipos\n";

        opcion = pedir<int>("Elige una opcion: ");

        int indice;

        try {
            switch (opcion) {

                case 1:
                    crearLista(lista);
                    break;

                case 2:
                    lista.addFirst(pedir<T>("Dato nuevo: "));
                    break;

                case 3:
                    lista.addLast(pedir<T>("Dato nuevo: "));
                    break;

                case 4:
                    indice = pedir<int>(
                        "Indice DESPUES del que insertar: "
                    );

                    lista.insert(
                        indice,
                        pedir<T>("Dato nuevo: ")
                    );
                    break;

                case 5:
                    cout << (
                        lista.deleteData(
                            pedir<T>("Dato a borrar: ")
                        )
                        ? "Dato borrado.\n"
                        : "No se encontro el dato.\n"
                    );
                    break;

                case 6:
                    cout << (
                        lista.deleteAt(
                            pedir<int>("Indice a borrar: ")
                        )
                        ? "Dato borrado.\n"
                        : "Indice invalido.\n"
                    );
                    break;

                case 7:
                    indice = pedir<int>("Indice a consultar: ");

                    cout << "Dato: "
                         << lista.getData(indice)
                         << '\n';
                    break;

                case 8: {
                    T anterior = pedir<T>(
                        "Valor que deseas reemplazar: "
                    );

                    T nuevo = pedir<T>("Nuevo valor: ");

                    lista.updateData(anterior, nuevo);

                    cout << "Dato actualizado.\n";
                    break;
                }

                case 9:
                    indice = pedir<int>("Indice a actualizar: ");

                    lista.updateAt(
                        indice,
                        pedir<T>("Nuevo valor: ")
                    );

                    cout << "Dato actualizado.\n";
                    break;

                case 10:
                    indice = lista.findData(
                        pedir<T>("Dato a buscar: ")
                    );

                    if (indice == -1) {
                        cout << "No encontrado.\n";
                    } else {
                        cout << "Encontrado en indice "
                             << indice << ".\n";
                    }
                    break;

                case 11:
                    indice = pedir<int>("Indice a leer: ");

                    cout << "lista[" << indice << "] = "
                         << lista[indice] << '\n';
                    break;

                case 12:
                    indice = pedir<int>("Indice a modificar: ");

                    lista[indice] = pedir<T>("Nuevo valor: ");

                    cout << "Dato actualizado mediante [].\n";
                    break;

                case 13:
                    copia = lista;

                    cout << "Copia independiente: ";
                    copia.printForward();
                    cout << '\n';
                    break;

                case 14:
                    lista.clear();
                    cout << "Lista limpiada.\n";
                    break;

                case 15:
                    lista.sort();
                    cout << "Lista ordenada.\n";
                    break;

                case 16:
                    lista.duplicate();
                    cout << "Se duplico cada elemento.\n";
                    break;

                case 17:
                    lista.removeDuplicates();

                    cout << "Lista ordenada, sin elementos repetidos.\n";
                    break;

                
                case 18:
                    cout << "\n===== MOSTRAR LISTA =====\n";

                    cout << "Adelante: ";
                    lista.printForward();

                    cout << "\nAtras: ";
                    lista.printBackward();

                    cout << "\n\nPresiona ENTER para continuar...";

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    break;


                case 0:
                    break;

                default:
                    cout << "Opcion invalida.\n";
            }

        } catch (const out_of_range& error) {
            cout << "Error: " << error.what() << '\n';
        }

    } while (opcion != 0);
}

// Programa principal
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    try {
        int tipo;

        do {
            cout << "\n====== SELECCIONA EL TIPO DE LISTA ======\n"
                 << "1. Enteros (int)\n"
                 << "2. Palabras (string, sin espacios)\n"
                 << "0. Salir\n";

            tipo = pedir<int>("Opcion: ");

            if (tipo == 1) {
                menuLista<int>();
            } else if (tipo == 2) {
                menuLista<string>();
            } else if (tipo != 0) {
                cout << "Opcion invalida.\n";
            }

        } while (tipo != 0);

    } catch (const runtime_error&) {
        cout << "\nEntrada terminada.\n";
    }

    cout << "Programa finalizado.\n";

    return 0;
}

