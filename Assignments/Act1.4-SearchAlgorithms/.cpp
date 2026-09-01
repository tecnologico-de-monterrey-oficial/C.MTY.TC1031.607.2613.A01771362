//Pamela Hernández Camacho
//A01771362

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Búsqueda secuencial: recorre el vector elemento por elemento
bool busquedaSecuencial(const vector<int>& v, int objetivo) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == objetivo) return true;
    }
    return false;
}

// Búsqueda binaria: requiere que el vector esté ordenado
bool busquedaBinaria(const vector<int>& v, int objetivo) {
    int izquierda = 0, derecha = static_cast<int>(v.size()) - 1;
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (v[medio] == objetivo) return true;
        else if (v[medio] < objetivo) izquierda = medio + 1;
        else derecha = medio - 1;
    }
    return false;
}

int main() {
    const int N = 10000;
    vector<int> numeros(N);

    // Generador de números aleatorios entre 1 y 1,000,000
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    for (int i = 0; i < N; i++) {
        numeros[i] = dist(gen);
    }

    // Se ordena el vector, requisito indispensable para la búsqueda binaria
    sort(numeros.begin(), numeros.end());

    cout << "Vector de " << N << " numeros generado y ordenado.\n";

    int num;
    while (true) {
        cout << "\nIngresa un numero entero entre 1 y 1,000,000 (0 para salir): ";
        if (!(cin >> num)) break; // por si la entrada no es válida
        if (num == 0) {
            cout << "Programa finalizado.\n";
            break;
        }

        // --- Búsqueda secuencial con medición de tiempo ---
        auto inicioSec = high_resolution_clock::now();
        bool encontradoSec = busquedaSecuencial(numeros, num);
        auto finSec = high_resolution_clock::now();
        auto duracionSec = duration_cast<nanoseconds>(finSec - inicioSec);

        // --- Búsqueda binaria con medición de tiempo ---
        auto inicioBin = high_resolution_clock::now();
        bool encontradoBin = busquedaBinaria(numeros, num);
        auto finBin = high_resolution_clock::now();
        auto duracionBin = duration_cast<nanoseconds>(finBin - inicioBin);

        cout << "Resultado: "
             << ((encontradoSec && encontradoBin) ? "El numero SI se encuentra en la lista.\n"
                                                    : "El numero NO se encuentra en la lista.\n");
        cout << "Tiempo busqueda secuencial: " << duracionSec.count() << " ns\n";
        cout << "Tiempo busqueda binaria:    " << duracionBin.count() << " ns\n";
    }

    return 0;
}
