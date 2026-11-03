// Programa principal: ADT LinkedList con menu para int y string.
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include "LinkedList.h"

using namespace std;

int readInt(const string& prompt, int minimum, int maximum) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) throw runtime_error("Fin de entrada");
        istringstream in(line);
        int value;
        char extra;
        if ((in >> value) && !(in >> extra) && value >= minimum && value <= maximum) {
            return value;
        }
        cout << "Entrada invalida. Ingresa un entero entre " << minimum
             << " y " << maximum << ".\n";
    }
}

template <typename T>
T readValue(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) throw runtime_error("Fin de entrada");
        istringstream in(line);
        T value;
        char extra;
        if ((in >> value) && !(in >> extra)) return value;
        cout << "Valor invalido. Intenta otra vez.\n";
    }
}

template <>
string readValue<string>(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) throw runtime_error("Fin de entrada");
        if (!line.empty()) return line;
        cout << "El texto no puede estar vacio.\n";
    }
}

template <typename T>
T randomValue(mt19937& generator) {
    if constexpr (is_same_v<T, int>) {
        uniform_int_distribution<int> distribution(0, 99);
        return distribution(generator);
    } else {
        static const string words[] = {
            "sol", "luna", "mar", "cielo", "rio", "flor", "nube", "arbol"
        };
        uniform_int_distribution<int> distribution(0, 7);
        return words[distribution(generator)];
    }
}

template <typename T>
void createList(LinkedList<T>& list, mt19937& generator) {
    list.clear();
    cout << "\n=== CREACION DE LISTA ===\n";
    int quantity = readInt("Cantidad de elementos (0-50): ", 0, 50);
    int mode = readInt("1. Datos aleatorios\n2. Capturar datos\nSelecciona: ", 1, 2);
    for (int i = 0; i < quantity; ++i) {
        T value = (mode == 1)
            ? randomValue<T>(generator)
            : readValue<T>("Elemento " + to_string(i) + ": ");
        list.addLast(value);
    }
    cout << "Lista creada: ";
    list.print();
}

void printMenu() {
    cout << "\n========== MENU LINKED LIST ==========\n"
         << "1. addFirst (agregar al inicio)\n"
         << "2. addLast (agregar al final)\n"
         << "3. insert (insertar despues de un indice)\n"
         << "4. deleteData (borrar un valor)\n"
         << "5. deleteAt (borrar por indice)\n"
         << "6. getData (consultar por indice)\n"
         << "7. updateData (actualizar por valor)\n"
         << "8. updateAt (actualizar por indice)\n"
         << "9. findData (buscar valor)\n"
         << "10. operador [] (leer)\n"
         << "11. operador [] (actualizar)\n"
         << "12. operador = (duplicar lista)\n"
         << "13. Mostrar lista\n"
         << "14. Mostrar copia\n"
         << "0. Crear otra lista / volver\n";
}

template <typename T>
void operate(LinkedList<T>& list) {
    LinkedList<T> copy;
    bool copyExists = false;
    while (true) {
        printMenu();
        int option = readInt("Opcion: ", 0, 14);
        if (option == 0) return;
        try {
            switch (option) {
                case 1:
                    list.addFirst(readValue<T>("Nuevo dato: "));
                    cout << "Agregado al principio.\n";
                    break;
                case 2:
                    list.addLast(readValue<T>("Nuevo dato: "));
                    cout << "Agregado al final.\n";
                    break;
                case 3: {
                    if (list.empty()) {
                        cout << "La lista esta vacia; usa addFirst para comenzar.\n";
                        break;
                    }
                    int index = readInt("Indice DESPUES del cual insertar: ", 0, list.getSize()-1);
                    T value = readValue<T>("Nuevo dato: ");
                    list.insert(index + 1, value);
                    cout << "Insertado despues del indice " << index << ".\n";
                    break;
                }
                case 4:
                    cout << (list.deleteData(readValue<T>("Dato a borrar: "))
                        ? "Elemento eliminado.\n" : "Dato no encontrado.\n");
                    break;
                case 5: {
                    int index = readInt("Indice a borrar: ", -1, 1000000);
                    cout << (list.deleteAt(index) ? "Elemento eliminado.\n"
                                                  : "Indice invalido.\n");
                    break;
                }
                case 6: {
                    int index = readInt("Indice a consultar: ", -1, 1000000);
                    cout << "getData(" << index << ") = " << list.getData(index) << "\n";
                    break;
                }
                case 7: {
                    T oldData = readValue<T>("Valor a buscar: ");
                    T newData = readValue<T>("Valor nuevo: ");
                    list.updateData(oldData, newData);
                    cout << "Elemento actualizado.\n";
                    break;
                }
                case 8: {
                    int index = readInt("Indice a modificar: ", -1, 1000000);
                    T newData = readValue<T>("Valor nuevo: ");
                    list.updateAt(index, newData);
                    cout << "Elemento actualizado.\n";
                    break;
                }
                case 9: {
                    T value = readValue<T>("Valor a buscar: ");
                    cout << "findData = " << list.findData(value) << "\n";
                    break;
                }
                case 10: {
                    int index = readInt("Indice a consultar con []: ", -1, 1000000);
                    cout << "lista[" << index << "] = " << list[index] << "\n";
                    break;
                }
                case 11: {
                    int index = readInt("Indice a modificar con []: ", -1, 1000000);
                    T newData = readValue<T>("Valor nuevo: ");
                    list[index] = newData;
                    cout << "Elemento actualizado con [].\n";
                    break;
                }
                case 12:
                    copy = list;
                    copyExists = true;
                    cout << "Lista duplicada con operador =. Copia: ";
                    copy.print();
                    break;
                case 13:
                    cout << "Lista actual: ";
                    list.print();
                    break;
                case 14:
                    if (copyExists) {
                        cout << "Copia guardada: ";
                        copy.print();
                    } else {
                        cout << "Aun no hay copia; usa la opcion 12.\n";
                    }
                    break;
            }
            if ((option >= 1 && option <= 5) || option == 7 || option == 8 || option == 11) {
                cout << "Lista actual: ";
                list.print();
            }
        } catch (const out_of_range& error) {
            cout << "Error de rango: " << error.what() << "\n";
        }
    }
}

int main() {
    try {
        random_device seed;
        mt19937 generator(seed());
        while (true) {
            cout << "\n====== CREAR LISTA ENLAZADA ======\n"
                 << "1. Lista de enteros (int)\n"
                 << "2. Lista de textos (string)\n"
                 << "0. Salir\n";
            int option = readInt("Tipo de lista: ", 0, 2);
            if (option == 0) {
                cout << "Programa finalizado.\n";
                return 0;
            }
            if (option == 1) {
                LinkedList<int> list;
                createList(list, generator);
                operate(list);
            } else {
                LinkedList<string> list;
                createList(list, generator);
                operate(list);
            }
        }
    } catch (const exception& error) {
        cerr << "Se cerro la entrada del programa: " << error.what() << "\n";
        return 1;
    }
}
