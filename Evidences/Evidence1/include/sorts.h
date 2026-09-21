//Pamela Hernández Camacho
//A01771362
//algoritmos de ordenamiento, uno por uno

/* Burbuja 
recorremos como la fila comparando de DOS EN DOS, repetimos
hasta que ya no haya nada que cambiar */

#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include "LogEntry.h"

// Regla para decidir cuál registro va primero: por fecha (clave).
// Si tienen la misma fecha, va primero el que estaba antes en el archivo.
inline bool menorQue(const LogEntry& a, const LogEntry& b) {
     /* ojo
    hay registros con exactamente la misma fecha y hora (los duplicados). 
    Si solo comparáramos la fecha, no sabríamos cuál va primero y distintos algoritmos podrían dejarlos en distinto orden */
    if (a.clave != b.clave) return a.clave < b.clave;
    return a.idOriginal < b.idOriginal;
}

bool estaOrdenado(const std::vector<LogEntry>& v);
void ordenarBurbuja(std::vector<LogEntry>& v);
void ordenarSeleccion(std::vector<LogEntry>& v);
long long ordenarSwap(std::vector<LogEntry>& v);
void ordenarInsercion(std::vector<LogEntry>& v);
void ordenarShell(std::vector<LogEntry>& v);

#endif
