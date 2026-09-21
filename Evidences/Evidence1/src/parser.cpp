//Pamela Hernández Camacho
//A01771362
//se encarga principalmente de convertir cada fecha en un número comparable 
//se llama parsear porque analizar una cadena de datos o texto y traducirla a 
//una estructura organizada que una computadora o programa pueda entender y usar fácilmente

#include "Parser.h"
#include <cctype>
#include <string>

// ¿Los n caracteres desde pos son todos dígitos?
static bool soloDigitos(const std::string& s, size_t pos, size_t n) {
    for (size_t i = pos; i < pos + n; i++) {
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    return true;
}

static bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}

static int diasDelMes(int anio, int mes) {
    const int dias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && esBisiesto(anio)) return 29;
    return dias[mes - 1];
}

bool parsearFecha(const std::string& texto, long long& clave) {
    if (texto.size() != 20) return false;

    // Forma exacta: "Mon DD YYYY HH:MM:SS"
    if (texto[3] != ' ' || texto[6] != ' ' || texto[11] != ' ' ||
        texto[14] != ':' || texto[17] != ':') return false;
    if (!soloDigitos(texto, 4, 2) || !soloDigitos(texto, 7, 4) ||
        !soloDigitos(texto, 12, 2) || !soloDigitos(texto, 15, 2) ||
        !soloDigitos(texto, 18, 2)) return false;

    const std::string meses[12] = {"Jan","Feb","Mar","Apr","May","Jun",
                                   "Jul","Aug","Sep","Oct","Nov","Dec"};
    int mes = 0;
    for (int i = 0; i < 12; i++) {
        if (texto.substr(0, 3) == meses[i]) mes = i + 1;
    }
    if (mes == 0) return false;

    int dia  = std::stoi(texto.substr(4, 2));
    int anio = std::stoi(texto.substr(7, 4));
    int hora = std::stoi(texto.substr(12, 2));
    int min  = std::stoi(texto.substr(15, 2));
    int seg  = std::stoi(texto.substr(18, 2));

    if (anio < 1970) return false;
    if (dia < 1 || dia > diasDelMes(anio, mes)) return false;
    if (hora > 23 || min > 59 || seg > 59) return false;

    clave = anio * 10000000000LL + mes * 100000000LL + dia * 1000000LL
          + hora * 10000LL + min * 100LL + seg;
    return true;
}

    /* NOTAA bool y return false permiten avisar "esto no era una fecha válida". 
    pero Más adelante se le agregará más validaciones */

