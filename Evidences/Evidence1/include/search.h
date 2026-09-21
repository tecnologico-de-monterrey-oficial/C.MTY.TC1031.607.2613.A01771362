//Pamela Hernández Camacho
//A01771362
//Búsqueda binaria por rango

#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include "LogEntry.h"

// Primera posición cuya clave es >= clave (v.size() si no existe)
size_t limiteInferior(const std::vector<LogEntry>& v, long long clave);

// Primera posición cuya clave es > clave (v.size() si no existe)
size_t limiteSuperior(const std::vector<LogEntry>& v, long long clave);

#endif