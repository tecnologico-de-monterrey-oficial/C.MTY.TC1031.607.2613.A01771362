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

// Mezcla dos mitades ya ordenadas: [lo, mid) y [mid, hi)
static void mezclar(std::vector<LogEntry>& v, std::vector<LogEntry>& aux,
                    size_t lo, size_t mid, size_t hi) { //mezclar usa tres "dedos": i en la mitad izquierda, j en la derecha, k donde va escribiendo en aux. Compara v[j] con v[i] y se lleva el menor. Los dos while siguientes copian lo que sobró en alguna mitad.
    size_t i = lo, j = mid, k = lo;
    while (i < mid && j < hi) {
        if (menorQue(v[j], v[i])) aux[k++] = std::move(v[j++]);
        else                      aux[k++] = std::move(v[i++]);
    }
    while (i < mid) aux[k++] = std::move(v[i++]);
    while (j < hi)  aux[k++] = std::move(v[j++]);
    for (size_t p = lo; p < hi; p++) v[p] = std::move(aux[p]); //El último for regresa el resultado de aux al vector original.
}

// Ordena la parte [lo, hi) del vector: divide, ordena cada mitad y mezcla
//es decir, [lo, hi) significa "desde lo incluido hasta hi sin incluir". Es una convención muy común que evita errores de "uno de más".
static void mergeRec(std::vector<LogEntry>& v, std::vector<LogEntry>& aux,
                     size_t lo, size_t hi) {
    if (hi - lo < 2) return;              // 0 o 1 elemento: ya está ordenado
    size_t mid = lo + (hi - lo) / 2;
    mergeRec(v, aux, lo, mid); //mergeRec tiene dos partes: el caso base (if (hi - lo < 2) return;, con 0 o 1 elemento no hay nada que hacer, y es lo que detiene la recursión) y el paso recursivo (se llama a sí misma con cada mitad).
    mergeRec(v, aux, mid, hi);
    mezclar(v, aux, lo, mid, hi);
}

void ordenarMerge(std::vector<LogEntry>& v) {
    std::vector<LogEntry> aux(v.size());  // espacio de trabajo para mezclar
    mergeRec(v, aux, 0, v.size());
}

static void quickRec(std::vector<LogEntry>& v, long long lo, long long hi) {
    if (lo >= hi) return;              // 0 o 1 elemento: ya está ordenado

    long long i = lo;                  // aquí termina la zona de los "menores"
    for (long long j = lo; j < hi; j++) {
        if (menorQue(v[j], v[hi])) {   // v[hi] es el pivote
            std::swap(v[i], v[j]);
            i++;
        }
    }
    std::swap(v[i], v[hi]);            // el pivote queda en su lugar final

    quickRec(v, lo, i - 1);            // ordenar los menores
    quickRec(v, i + 1, hi);            // ordenar los mayores
}

void ordenarQuick(std::vector<LogEntry>& v) {
    if (v.size() > 1) quickRec(v, 0, static_cast<long long>(v.size()) - 1);
}