//Pamela Hernández Camacho
//A01771362
//se enacarga principalmente de convertir cada fecha en un número comparable 

//es como solo el "anuncio" de la función
#ifndef PARSER_H
#define PARSER_H

#include <string>

// Convierte "Sep 29 2024 14:37:38" (20 caracteres) en 20240929143738.
// Devuelve true si pudo convertirla, false si no.
bool parsearFecha(const std::string& texto, long long& clave);

#endif