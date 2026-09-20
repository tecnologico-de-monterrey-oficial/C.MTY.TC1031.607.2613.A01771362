//Pamela Hernández Camacho
//A01771362
//se enacarga principalmente de convertir cada fecha en un número comparable 

/* como cada línea empieza con una fecha como sep etc etc para odernarla la computadora necesita
compararla con otras y como texto no sirve ya que alfabéticamente APR iria antes que SEP aunque
fuera de otro año */

//podemos convertir cada fecha en un número donde "más grande=más tarde"

//tendríamos año, mes, día, hora, minuto y segundo pegados 
//ejemplo Sep 29 2024 14:37:38   →   20240929143738
// y así comparamos puro número

#ifndef LOGENTRY_H //evita que el archivo se cargue dos veces y así 
#define LOGENTRY_H

#include <string>

//usamos struct porque es un paquete de datos 
struct LogEntry {
    long long   clave;       // la fecha convertida a número guardando su número en CLAVE (large data type por eso long)
    int         idOriginal;  // posición del registro en el archivo (0, 1, 2...)
    std::string linea;       // la línea completa, tal cual venía
};

#endif