// Pamela Hernandez Camacho
// A01771362

#include <iostream>
#include <string>
#include <limits>

#include "BST.h"

using namespace std;


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

    // BST de enteros (funciona igual con string, double, etc.)
    BST<int> arbol;

    int opcion;

    do {

        cout << "\n===== ARBOL BINARIO DE BUSQUEDA =====" << endl;
        cout << "1. Insertar un valor" << endl;
        cout << "2. Eliminar un valor" << endl;
        cout << "3. Imprimir el arbol" << endl;
        cout << "4. Recorridos (preorder, inorder, postorder, por niveles)" << endl;
        cout << "5. Buscar un valor" << endl;
        cout << "6. Mostrar la altura del arbol" << endl;
        cout << "7. Mostrar los ancestros de un nodo" << endl;
        cout << "8. Consultar el nivel de un nodo" << endl;
        cout << "9. Salir" << endl;

        opcion = leerEntero("\nSelecciona una opcion: ");

        switch (opcion) {

            case 1: {
                int dato = leerEntero("\nValor a insertar: ");

                if (arbol.find(dato)) {
                    cout << "El valor ya existe, no se inserta." << endl;
                }
                else {
                    arbol.insert(dato);
                    cout << "Valor insertado correctamente." << endl;
                }
                break;
            }

            case 2: {
                int dato = leerEntero("\nValor a eliminar: ");

                if (arbol.find(dato)) {
                    arbol.remove(dato);
                    cout << "Valor eliminado correctamente." << endl;
                }
                else {
                    cout << "El valor no se encuentra en el arbol." << endl;
                }
                break;
            }

            case 3: {
                cout << "\n";
                arbol.print();
                break;
            }

            case 4: {
                cout << "\n1. Preorder" << endl;
                cout << "2. Inorder" << endl;
                cout << "3. Postorder" << endl;
                cout << "4. Por niveles" << endl;

                int tipo = leerEntero("Tipo de recorrido: ");

                if (tipo < 1 || tipo > 4) {
                    cout << "\nTipo de recorrido invalido." << endl;
                }
                else {
                    cout << "\nRecorrido: ";
                    arbol.visit(tipo);
                }
                break;
            }

            case 5: {
                int dato = leerEntero("\nValor a buscar: ");

                if (arbol.find(dato)) {
                    cout << "El valor " << dato << " SI se encuentra en el arbol." << endl;
                }
                else {
                    cout << "El valor " << dato << " NO se encuentra en el arbol." << endl;
                }
                break;
            }

            case 6: {
                cout << "\nAltura del arbol: " << arbol.height() << endl;
                break;
            }

            case 7: {
                int dato = leerEntero("\nValor del que quieres los ancestros: ");
                cout << "\n";
                arbol.ancestors(dato);
                break;
            }

            case 8: {
                int dato = leerEntero("\nValor a consultar: ");
                int nivel = arbol.whatLevelAml(dato);

                if (nivel == -1) {
                    cout << "El valor " << dato << " no se encuentra en el arbol." << endl;
                }
                else {
                    cout << "El valor " << dato << " esta en el nivel " << nivel << endl;
                }
                break;
            }

            case 9: {
                cout << "\nSaliendo del programa..." << endl;
                break;
            }

            default: {
                cout << "\nOpcion invalida." << endl;
            }
        }

    } while (opcion != 9);

    return 0;
}