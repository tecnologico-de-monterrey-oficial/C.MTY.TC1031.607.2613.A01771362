//Pamela Hernández Camacho
//A01771362
//búsqueda binaria por rango 


#include "search.h"

size_t limiteInferior(const std::vector<LogEntry>& v, long long clave) {
    size_t lo = 0, hi = v.size();
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (v[mid].clave < clave) lo = mid + 1;   // v[mid] es muy chico: buscar a la derecha
        else                      hi = mid;       // v[mid] sirve: buscar a la izquierda (o es él)
    }
    return lo;
}

size_t limiteSuperior(const std::vector<LogEntry>& v, long long clave) {
    size_t lo = 0, hi = v.size();
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (v[mid].clave <= clave) lo = mid + 1;  // los iguales todavía "entran": seguir a la derecha
        else                       hi = mid;
    }
    return lo;
}

