//Pamela Hernández Camacho
//A01771362

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

// ==========================================
// ESTRUCTURA PARA GUARDAR ESTADÍSTICAS
// ==========================================
struct Estadisticas {
    long long comparaciones = 0;
    long long intercambios = 0;
};

// ==========================================
// SWAP SORT
// ==========================================
template <typename T>
void swapSort(vector<T>& datos, Estadisticas& estadisticas) {

    int n = datos.size();

    for (int i = 0; i < n - 1; i++) {

        for (int j = i + 1; j < n; j++) {

            estadisticas.comparaciones++;

            if (datos[i] > datos[j]) {

                swap(datos[i], datos[j]);

                estadisticas.intercambios++;
            }
        }
    }
}

// ==========================================
// BUBBLE SORT
// ==========================================
template <typename T>
void bubbleSort(vector<T>& datos, Estadisticas& estadisticas) {

    int n = datos.size();

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            estadisticas.comparaciones++;

            if (datos[j] > datos[j + 1]) {

                swap(datos[j], datos[j + 1]);

                estadisticas.intercambios++;
            }
        }
    }
}

// ==========================================
// SELECTION SORT
// ==========================================

template <typename T>
void selectionSort(vector<T>& datos, Estadisticas& estadisticas) {

    int n = datos.size();

    for (int i = 0; i < n - 1; i++) {

        int posicionMenor = i;

        for (int j = i + 1; j < n; j++) {

            estadisticas.comparaciones++;

            if (datos[j] < datos[posicionMenor]) {

                posicionMenor = j;
            }
        }

        if (posicionMenor != i) {

            swap(datos[i], datos[posicionMenor]);

            estadisticas.intercambios++;
        }
    }
}

// ==========================================
// INSERTION SORT
// ==========================================

template <typename T>
void insertionSort(vector<T>& datos, Estadisticas& estadisticas) {

    int n = datos.size();

    for (int i = 1; i < n; i++) {

        T key = datos[i];

        int j = i - 1;

        while (j >= 0) {

            estadisticas.comparaciones++;

            if (datos[j] > key) {

                datos[j + 1] = datos[j];

                estadisticas.intercambios++;

                j--;
            }
            else {
                break;
            }
        }

        datos[j + 1] = key;
    }
}

// ==========================================
// MERGE SORT
// ==========================================

template <typename T>
void merge(vector<T>& datos, int izquierda, int medio, int derecha) {

    vector<T> izquierdaVector;
    vector<T> derechaVector;

    for (int i = izquierda; i <= medio; i++) {
        izquierdaVector.push_back(datos[i]);
    }

    for (int i = medio + 1; i <= derecha; i++) {
        derechaVector.push_back(datos[i]);
    }

    int i = 0;
    int j = 0;
    int k = izquierda;

    while (i < izquierdaVector.size() &&
           j < derechaVector.size()) {

        if (izquierdaVector[i] <= derechaVector[j]) {

            datos[k] = izquierdaVector[i];
            i++;
        }
        else {

            datos[k] = derechaVector[j];
            j++;
        }

        k++;
    }

    while (i < izquierdaVector.size()) {

        datos[k] = izquierdaVector[i];

        i++;
        k++;
    }

    while (j < derechaVector.size()) {

        datos[k] = derechaVector[j];

        j++;
        k++;
    }
}

template <typename T>
void mergeSort(vector<T>& datos, int izquierda, int derecha) {

    if (izquierda < derecha) {

        int medio = izquierda + (derecha - izquierda) / 2;

        mergeSort(datos, izquierda, medio);

        mergeSort(datos, medio + 1, derecha);

        merge(datos, izquierda, medio, derecha);
    }
}

// ==========================================
// QUICK SORT
// ==========================================

template <typename T>
int particion(vector<T>& datos, int izquierda, int derecha) {

    T pivote = datos[derecha];

    int i = izquierda - 1;

    for (int j = izquierda; j < derecha; j++) {

        if (datos[j] < pivote) {

            i++;

            swap(datos[i], datos[j]);
        }
    }

    swap(datos[i + 1], datos[derecha]);

    return i + 1;
}

template <typename T>
void quickSort(vector<T>& datos, int izquierda, int derecha) {

    if (izquierda < derecha) {

        int posicionPivote =
            particion(datos, izquierda, derecha);

        quickSort(datos, izquierda, posicionPivote - 1);

        quickSort(datos, posicionPivote + 1, derecha);
    }
}

// ==========================================
// SHELL SORT
// ALGORITMO EXTRA
// ==========================================

template <typename T>
void shellSort(vector<T>& datos) {

    int n = datos.size();

    for (int salto = n / 2; salto > 0; salto /= 2) {

        for (int i = salto; i < n; i++) {

            T temporal = datos[i];

            int j;

            for (j = i;
                 j >= salto && datos[j - salto] > temporal;
                 j -= salto) {

                datos[j] = datos[j - salto];
            }

            datos[j] = temporal;
        }
    }
}

// ==========================================
// MOSTRAR VECTOR
// ==========================================

template <typename T>
void mostrarVector(const vector<T>& datos) {

    int n = datos.size();

    // Para evitar imprimir 100,000 elementos
    // mostramos los primeros y últimos 20.

    if (n <= 50) {

        for (int i = 0; i < n; i++) {

            cout << datos[i] << " ";
        }
    }
    else {

        for (int i = 0; i < 20; i++) {

            cout << datos[i] << " ";
        }

        cout << "... ";

        for (int i = n - 20; i < n; i++) {

            cout << datos[i] << " ";
        }
    }

    cout << endl;
}

// ==========================================
// MEDIR SWAP, BUBBLE, SELECTION E INSERTION
// ==========================================

template <typename T>
void ejecutarPrimerosCuatro(
    vector<T> original,
    int opcion) {

    vector<T> datos = original;

    Estadisticas estadisticas;

    auto inicio = chrono::high_resolution_clock::now();

    if (opcion == 1) {

        swapSort(datos, estadisticas);
        cout << "\n--- SWAP SORT ---\n";
    }

    else if (opcion == 2) {

        bubbleSort(datos, estadisticas);
        cout << "\n--- BUBBLE SORT ---\n";
    }

    else if (opcion == 3) {

        selectionSort(datos, estadisticas);
        cout << "\n--- SELECTION SORT ---\n";
    }

    else if (opcion == 4) {

        insertionSort(datos, estadisticas);
        cout << "\n--- INSERTION SORT ---\n";
    }

    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> tiempo = fin - inicio;

    cout << "Lista ordenada:\n";
    mostrarVector(datos);

    cout << "\nComparaciones: "
         << estadisticas.comparaciones << endl;

    cout << "Intercambios: "
         << estadisticas.intercambios << endl;

    cout << fixed << setprecision(4);

    cout << "Tiempo: "
         << tiempo.count()
         << " ms\n";
}

// ==========================================
// MERGE, QUICK Y SHELL
// ==========================================

template <typename T>
void ejecutarOtros(
    vector<T> original,
    int opcion) {

    vector<T> datos = original;

    auto inicio = chrono::high_resolution_clock::now();

    if (opcion == 5) {

        mergeSort(datos, 0, datos.size() - 1);

        cout << "\n--- MERGE SORT ---\n";
    }

    else if (opcion == 6) {

        quickSort(datos, 0, datos.size() - 1);

        cout << "\n--- QUICK SORT ---\n";
    }

    else if (opcion == 7) {

        shellSort(datos);

        cout << "\n--- SHELL SORT ---\n";
    }

    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> tiempo = fin - inicio;

    cout << "Lista ordenada:\n";

    mostrarVector(datos);

    cout << fixed << setprecision(4);

    cout << "Tiempo: "
         << tiempo.count()
         << " ms\n";
}

// ==========================================
// CREAR VECTOR DE INT
// ==========================================

vector<int> crearInt(int cantidad) {

    vector<int> datos(cantidad);

    random_device rd;
    mt19937 generador(rd());

    uniform_int_distribution<int> distribucion(1, 1000000);

    for (int i = 0; i < cantidad; i++) {

        datos[i] = distribucion(generador);
    }

    return datos;
}

// ==========================================
// CREAR VECTOR DE DOUBLE
// ==========================================

vector<double> crearDouble(int cantidad) {

    vector<double> datos(cantidad);

    random_device rd;
    mt19937 generador(rd());

    uniform_real_distribution<double> distribucion(0.0, 1000000.0);

    for (int i = 0; i < cantidad; i++) {

        datos[i] = distribucion(generador);
    }

    return datos;
}

// ==========================================
// CREAR STRING ALEATORIO
// ==========================================

string generarString(int longitud) {

    string caracteres =
        "abcdefghijklmnopqrstuvwxyz";

    random_device rd;
    mt19937 generador(rd());

    uniform_int_distribution<int>
        distribucion(0, caracteres.size() - 1);

    string resultado = "";

    for (int i = 0; i < longitud; i++) {

        resultado +=
            caracteres[distribucion(generador)];
    }

    return resultado;
}

vector<string> crearString(int cantidad) {

    vector<string> datos(cantidad);

    for (int i = 0; i < cantidad; i++) {

        datos[i] = generarString(5);
    }

    return datos;
}

// ==========================================
// MENÚ DE ORDENAMIENTO
// ==========================================

template <typename T>
void menuOrdenamiento(vector<T> datos) {

    int opcion;

    do {

        cout << "\n================================\n";
        cout << "       ALGORITMOS DE ORDENAMIENTO\n";
        cout << "================================\n";

        cout << "1. Swap Sort\n";
        cout << "2. Bubble Sort\n";
        cout << "3. Selection Sort\n";
        cout << "4. Insertion Sort\n";
        cout << "5. Merge Sort\n";
        cout << "6. Quick Sort\n";
        cout << "7. Shell Sort\n";
        cout << "8. Regresar\n";

        cout << "\nSelecciona una opcion: ";
        cin >> opcion;

        if (opcion >= 1 && opcion <= 4) {

            ejecutarPrimerosCuatro(datos, opcion);
        }

        else if (opcion >= 5 && opcion <= 7) {

            ejecutarOtros(datos, opcion);
        }

        else if (opcion != 8) {

            cout << "Opcion invalida.\n";
        }

    } while (opcion != 8);
}

// ==========================================
// MAIN
// ==========================================

int main() {

    int opcion;
    int tipo;
    int cantidad;

    do {

        cout << "\n========================================\n";
        cout << "       PROGRAMA DE ORDENAMIENTO\n";
        cout << "========================================\n";

        cout << "1. Crear lista\n";
        cout << "2. Salir\n";

        cout << "\nSelecciona una opcion: ";
        cin >> opcion;

        if (opcion == 1) {

            cout << "\n--- TIPO DE DATO ---\n";

            cout << "1. Enteros (int)\n";
            cout << "2. Decimales (double)\n";
            cout << "3. Cadenas (string)\n";

            cout << "\nSelecciona el tipo: ";
            cin >> tipo;

            cout << "\n--- CANTIDAD DE DATOS ---\n";

            cout << "1. 1,000\n";
            cout << "2. 10,000\n";
            cout << "3. 100,000\n";

            cout << "\nSelecciona la cantidad: ";
            int opcionCantidad;
            cin >> opcionCantidad;

            if (opcionCantidad == 1) {
                cantidad = 1000;
            }
            else if (opcionCantidad == 2) {
                cantidad = 10000;
            }
            else if (opcionCantidad == 3) {
                cantidad = 100000;
            }
            else {
                cout << "Cantidad invalida.\n";
                continue;
            }

            cout << "\nCreando lista de "
                 << cantidad
                 << " elementos...\n";

            if (tipo == 1) {

                vector<int> datos = crearInt(cantidad);

                cout << "Lista creada correctamente.\n";

                menuOrdenamiento(datos);
            }

            else if (tipo == 2) {

                vector<double> datos =
                    crearDouble(cantidad);

                cout << "Lista creada correctamente.\n";

                menuOrdenamiento(datos);
            }

            else if (tipo == 3) {

                vector<string> datos =
                    crearString(cantidad);

                cout << "Lista creada correctamente.\n";

                menuOrdenamiento(datos);
            }

            else {

                cout << "Tipo invalido.\n";
            }
        }

        else if (opcion != 2) {

            cout << "Opcion invalida.\n";
        }

    } while (opcion != 2);

    cout << "\nPrograma terminado.\n";

    return 0;
}