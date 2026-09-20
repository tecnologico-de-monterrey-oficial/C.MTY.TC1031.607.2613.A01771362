//Pamela Hernández Camacho
//A01771362
//menu que tiene lo de archivo, algoritmo, predicción
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "LogEntry.h"
#include "Parser.h"

int main() {
    std::ifstream archivo("data/log607-1.txt");
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
            registros.push_back(e); //agrega uno al final
        }
    }

    std::cout << "Registros válidos: " << registros.size() << "\n";
    std::cout << "Primera línea: " << registros[0].linea << "\n";
    std::cout << "Su clave: " << registros[0].clave << "\n";
    return 0;
}