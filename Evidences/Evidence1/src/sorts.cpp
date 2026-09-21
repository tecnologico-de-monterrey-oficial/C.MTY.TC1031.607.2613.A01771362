//Pamela Hernández Camacho
//A01771362
//algoritmos de ordenamiento, uno por uno

#include "sorts.h"
#include <utility>

/* es un verificador: revisa cada registro contra el anterior;
si alguno está fuera de orden, responde false. Sirve para comprobar que tu algoritmo funcionó. */
bool estaOrdenado(const std::vector<LogEntry>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        if (menorQue(v[i], v[i - 1])) return false;
    }
    return true;
}

void ordenarBurbuja(std::vector<LogEntry>& v) {
    size_t n = v.size();
    //for para cada "pasada"
    for (size_t i = 0; i + 1 < n; i++) {
        bool huboCambio = false;
        //for para comparar vecinos v[j], v[j + 1]
        for (size_t j = 0; j + 1 < n - i; j++) { //el n-i hace que cada pasada revise un elemento menos porque los grandes ya quedaron acomodados al final
            if (menorQue(v[j + 1], v[j])) {
                std::swap(v[j], v[j + 1]); //intercambia dos elementos de lugar
                huboCambio = true;
                /* es una bandera: si una pasada completa no intercambió nada, 
                ya está todo ordenado y el break sale antes. 
                Esto vuelve rapidísima a la burbuja con datos casi ordenados. */
            }
        }
        if (!huboCambio) break;
    }
}

void ordenarSeleccion(std::vector<LogEntry>& v) {
    size_t n = v.size();
    for (size_t i = 0; i + 1 < n; i++) {
        size_t minimo = i; //guarda la posición del registro más pequeño encontrado hasta ahora; empieza suponiendo que es el de la posición i
        for (size_t j = i + 1; j < n; j++) { //revisa todo lo que queda a la derecha de i. Cada vez que encuentra uno más pequeño, actualiza minimo.
            if (menorQue(v[j], v[minimo])) minimo = j;
        }
        if (minimo != i) std::swap(v[i], v[minimo]); //std::swap cambia de lugar el registro de i con el mínimo encontrado.
    }
}

long long ordenarSwap(std::vector<LogEntry>& v) {
    long long intercambios = 0;
    size_t n = v.size();
    for (size_t i = 0; i + 1 < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (menorQue(v[j], v[i])) {
                std::swap(v[i], v[j]);
                intercambios++;
            }
        }
    }
    return intercambios;
}

//Es como acomodar cartas en tu mano. Tomas la siguiente carta y la deslizas hacia la izquierda hasta que encaje
void ordenarInsercion(std::vector<LogEntry>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        LogEntry actual = std::move(v[i]); // actual es la carta que sacamos de la mano. std::move la mueve en vez de copiarla, y es más rápido.
        size_t j = i;
        while (j > 0 && menorQue(actual, v[j - 1])) {
            v[j] = std::move(v[j - 1]);
            j--;
        }
        v[j] = std::move(actual);
    }
}

void ordenarShell(std::vector<LogEntry>& v) {
    size_t n = v.size();
    size_t salto = 1;
    while (salto < n / 3) salto = 3 * salto + 1;   // 1, 4, 13, 40, 121, ...

    while (salto >= 1) {
        for (size_t i = salto; i < n; i++) {
            LogEntry actual = std::move(v[i]);
            size_t j = i;
            while (j >= salto && menorQue(actual, v[j - salto])) {
                v[j] = std::move(v[j - salto]);
                j -= salto;
            }
            v[j] = std::move(actual);
        }
        salto /= 3;
    }
}