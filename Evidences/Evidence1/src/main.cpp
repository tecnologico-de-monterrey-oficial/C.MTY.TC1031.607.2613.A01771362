//Pamela Hernández Camacho
//A01771362
//menu que tiene lo de archivo, algoritmo, predicción

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "LogEntry.h"
#include "Parser.h"
#include "sorts.h"
#include "search.h"

// Lee un archivo de bitácora y llena el vector. Devuelve false si no pudo abrirlo.
bool cargarArchivo(const std::string& ruta, std::vector<LogEntry>& registros) {
    std::ifstream archivo(ruta);
    if (!archivo) return false;
    registros.clear();
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
    return true;
}

// Escribe cada registro en una línea del archivo. Devuelve false si no pudo escribir.
bool guardarArchivo(const std::string& ruta, const std::vector<LogEntry>& v) {
    std::ofstream salida(ruta);
    if (!salida) return false;
    for (size_t i = 0; i < v.size(); i++) salida << v[i].linea << "\n";
    return true;
}

// Pregunta hasta que el usuario escriba un número entre minimo y maximo.
int leerOpcion(const std::string& pregunta, int minimo, int maximo) {
    while (true) {
        std::cout << pregunta;
        std::string texto;
        if (!std::getline(std::cin, texto)) std::exit(0);   // por si se cierra la entrada
        try {
            size_t usados = 0;
            int valor = std::stoi(texto, &usados);
            if (usados == texto.size() && valor >= minimo && valor <= maximo) return valor;
        } catch (...) {}
        std::cout << "  Opción inválida. Escribe un número entre "
                  << minimo << " y " << maximo << ".\n";
    }
}

// Llama al algoritmo que eligió el usuario.
void ejecutarAlgoritmo(int alg, std::vector<LogEntry>& v) {
    switch (alg) {
        case 1: ordenarBurbuja(v);   break;
        case 2: ordenarSeleccion(v); break;
        case 3: ordenarSwap(v);      break;
        case 4: ordenarInsercion(v); break;
        case 5: ordenarShell(v);     break;
        case 6: ordenarMerge(v);     break;
        case 7: ordenarQuick(v);     break;
    }
}

// Búsqueda por rango de fechas (usa los datos ya ordenados de la última corrida).
void opcionRango(const std::vector<LogEntry>& ordenado) {
    if (ordenado.empty()) {
        std::cout << "Primero ordena un archivo (opción 1): la búsqueda necesita datos ordenados.\n";
        return;
    }

    std::string textoIni, textoFin;
    long long ini, fin;
    std::cout << "Formato de fecha: Sep 29 2024 14:37:38\n";
    std::cout << "Fecha/hora de inicio: ";
    std::getline(std::cin, textoIni);
    std::cout << "Fecha/hora de fin: ";
    std::getline(std::cin, textoFin);

    if (!parsearFecha(textoIni, ini) || !parsearFecha(textoFin, fin)) {
        std::cout << "Fecha inválida.\n";
        return;
    }
    if (ini > fin) {
        std::cout << "El inicio es posterior al fin.\n";
        return;
    }

    size_t lo = limiteInferior(ordenado, ini);
    size_t hi = limiteSuperior(ordenado, fin);

    std::cout << "Registros en el rango: " << (hi - lo) << "\n";
    if (hi == lo) std::cout << "Rango vacío: no hay registros entre esas fechas.\n";

    // Pantalla: todos si son pocos; si son muchos, los primeros 20 y los últimos 10
    size_t cantidad = hi - lo;
    if (cantidad <= 40) {
        for (size_t i = lo; i < hi; i++) std::cout << "  " << ordenado[i].linea << "\n";
    } else {
        for (size_t i = lo; i < lo + 20; i++) std::cout << "  " << ordenado[i].linea << "\n";
        std::cout << "  ... (" << cantidad - 30 << " registros más; completos en out/range607.txt) ...\n";
        for (size_t i = hi - 10; i < hi; i++) std::cout << "  " << ordenado[i].linea << "\n";
    }

    // Archivo: siempre se guardan todos
    std::ofstream salida("out/range607.txt");
    for (size_t i = lo; i < hi; i++) salida << ordenado[i].linea << "\n";
    std::cout << "Resultado guardado en out/range607.txt\n";
}

int main() {
    const std::string archivos[2] = {"data/log607-1.txt", "data/log607-2.txt"};
    const std::string nombres[7] = {"Burbuja", "Selección", "Swap Sort", "Inserción",
                                    "Shell", "Merge", "Quick"};
    const std::string mejor[7] = {"O(n)", "O(n^2)", "O(n^2)", "O(n)",
                                  "O(n log n)", "O(n log n)", "O(n log n)"};
    const std::string peor[7]  = {"O(n^2)", "O(n^2)", "O(n^2)", "O(n^2)",
                                  "O(n^2)", "O(n log n)", "O(n^2)"};
    const std::string categorias[3] = {"Rápida", "Media", "Lenta"};

    std::vector<LogEntry> ordenado;   // resultado de la última corrida (lo usa la búsqueda)

    while (true) {
        std::cout << "\n===== MENÚ =====\n  1) Ordenar un archivo\n  2) Buscar por rango de fechas\n  0) Salir\n";
        int op = leerOpcion("Opción: ", 0, 2);
        if (op == 0) break;
        if (op == 2) {
            opcionRango(ordenado);
            continue;
        }

        std::cout << "\nArchivo:\n  1) log607-1.txt (desordenado)\n  2) log607-2.txt (casi ordenado)\n";
        int arch = leerOpcion("Archivo: ", 1, 2);

        std::vector<LogEntry> registros;
        if (!cargarArchivo(archivos[arch - 1], registros)) {
            std::cout << "No pude abrir " << archivos[arch - 1] << "\n";
            continue;
        }
        std::cout << "Cargados " << registros.size() << " registros.\n";

        std::cout << "\nAlgoritmo:\n";
        for (int i = 0; i < 7; i++) std::cout << "  " << i + 1 << ") " << nombres[i] << "\n";
        int alg = leerOpcion("Algoritmo: ", 1, 7);

        std::cout << "\nTu predicción:\n  1) Rápida (menos de 5 ms)\n"
                  << "  2) Media (de 5 a 50 ms)\n  3) Lenta (más de 50 ms)\n";
        int pred = leerOpcion("¿Qué tan rápido crees que será?: ", 1, 3);
        std::cout << "¿Por qué? ";
        std::string razon;
        std::getline(std::cin, razon);

        // Se ordena una copia y solo se cronometra el ordenamiento
        std::vector<LogEntry> copia = registros;
        auto inicio = std::chrono::steady_clock::now();
        ejecutarAlgoritmo(alg, copia);
        auto fin = std::chrono::steady_clock::now();
        double ms = std::chrono::duration<double, std::milli>(fin - inicio).count();

        int real = (ms < 5) ? 1 : (ms <= 50 ? 2 : 3);

        std::string reporte;
        reporte += "\n========== RESULTADO ==========\n";
        reporte += "Algoritmo: " + nombres[alg - 1] + "\n";
        reporte += "Archivo: " + archivos[arch - 1] + "\n";
        reporte += "Tamaño de los datos: " + std::to_string(registros.size()) + " registros\n";
        reporte += "Tiempo de ordenamiento: " + std::to_string(ms) + " ms\n";
        reporte += "Complejidad teórica: mejor caso " + mejor[alg - 1]
                 + ", peor caso " + peor[alg - 1] + "\n";
        reporte += "Ordenado correctamente: " + std::string(estaOrdenado(copia) ? "sí" : "no") + "\n";
        reporte += "Tu predicción: " + categorias[pred - 1] + " (" + razon + ")\n";
        reporte += "Resultado medido: " + categorias[real - 1] + "\n";
        reporte += (pred == real) ? "=> Tu predicción COINCIDIÓ\n" : "=> Tu predicción NO coincidió\n";

        std::cout << reporte;

        std::ofstream bitacora("out/corridas607.txt", std::ios::app);   // app = agregar al final
        if (bitacora) bitacora << reporte;

        if (guardarArchivo("out/output607.txt", copia))
            std::cout << "Datos ordenados guardados en out/output607.txt\n";
        else
            std::cout << "No pude guardar out/output607.txt\n";

        ordenado = copia;
    }
    std::cout << "Hasta luego.\n";
    return 0;
}