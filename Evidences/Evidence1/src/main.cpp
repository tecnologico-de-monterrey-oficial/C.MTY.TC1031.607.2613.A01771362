//Pamela Hernández Camacho
//A01771362
//menu que tiene lo de archivo, algoritmo, predicción

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "LogEntry.h"
#include "Parser.h"
#include "sorts.h"

int main() {
    std::ifstream archivo("data/log607-2.txt");
    if (!archivo) {
        std::cout << "No pude abrir el archivo\n";
        return 1;
    }

        //creamos lista que crece sola
    std::vector<LogEntry> registros;
    std::string linea;
    while (std::getline(archivo, linea)) {
        long long clave;
        if (linea.size() > 20 && parsearFecha(linea.substr(0, 20), clave)) {
            LogEntry e;
            e.clave = clave;
            e.idOriginal = static_cast<int>(registros.size());
            e.linea = linea;
            registros.push_back(e);
        }
    }
    std::cout << "Registros válidos: " << registros.size() << "\n";

    std::vector<LogEntry> copia = registros; // ordenamos una copia

    /* chrono: toma la hora justo antes y justo después de ordenar, y la resta da el 
tiempo en milisegundos. Solo se cronometra el ordenamiento, no la lectura del archivo.
 */
    auto inicio = std::chrono::steady_clock::now();
    ordenarShell(copia);
    auto fin = std::chrono::steady_clock::now();
    double ms = std::chrono::duration<double, std::milli>(fin - inicio).count();

    std::cout << "Shell: " << ms << " ms\n";
    std::cout << "¿Ordenado? " << (estaOrdenado(copia) ? "sí" : "no") << "\n";
    std::cout << "Primero: " << copia.front().linea << "\n";
    std::cout << "Último:  " << copia.back().linea << "\n";
    return 0;
}