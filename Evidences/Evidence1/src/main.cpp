//Pamela Hernández Camacho
//A01771362
//menu que tiene lo de archivo, algoritmo, predicción

#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream archivo("data/log607-1.txt");
    if (!archivo) {
        std::cout << "No pude abrir el archivo\n";
        return 1;
    }

    std::string linea;
    std::string primera;
    int contador = 0;
    while (std::getline(archivo, linea)) {
        if (contador == 0) primera = linea;
        contador++;
    }

    std::cout << "Líneas leídas: " << contador << "\n";
    std::cout << "Primera línea: " << primera << "\n";
    return 0;
}