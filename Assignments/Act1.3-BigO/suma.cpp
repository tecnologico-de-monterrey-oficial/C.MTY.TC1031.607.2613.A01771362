#include <iostream>
#include <vector>
using namespace std;

/*
 * Función ITERATIVA
 * Recorre una sola vez el vector (un ciclo "for" de tamaño n).
 * Orden (notación asintótica): O(n)
 *   - Operación básica: la comparación/verificación v[i] % 2 != 0
 *   - Se realiza exactamente n veces (una por cada elemento del vector)
 */
int sumaImparesIterativo(const vector<int>& v) {
    int suma = 0;
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] % 2 != 0) {
            suma += v[i];
        }
    }
    return suma;
}

/*
 * Función RECURSIVA (con función auxiliar que recibe el índice actual)
 * Cada llamada procesa un elemento y se llama a sí misma con índice+1,
 * hasta llegar al caso base (índice == tamaño del vector).
 * Fórmula recursiva de tiempo de ejecución: T(n) = T(n-1) + O(1), T(0) = O(1)
 * Resolviendo la recurrencia: T(n) = O(n)
 * Orden (notación asintótica): O(n)
 */
int sumaImparesRecursivoAux(const vector<int>& v, size_t indice) {
    // Caso base: ya no quedan elementos por revisar
    if (indice == v.size()) {
        return 0;
    }

    int restoSuma = sumaImparesRecursivoAux(v, indice + 1); // llamada recursiva

    if (v[indice] % 2 != 0) {
        return v[indice] + restoSuma;
    }
    return restoSuma;
}

// Función "envoltura" para llamar la recursión de forma más limpia
int sumaImparesRecursivo(const vector<int>& v) {
    return sumaImparesRecursivoAux(v, 0);
}

int main() {
    vector<int> numeros = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "Vector: ";
    for (int n : numeros) cout << n << " ";
    cout << endl;

    cout << "Suma de impares (iterativo): "
         << sumaImparesIterativo(numeros) << " -> Orden: O(n)" << endl;

    cout << "Suma de impares (recursivo): "
         << sumaImparesRecursivo(numeros) << " -> Orden: O(n)" << endl;

    return 0;
}
