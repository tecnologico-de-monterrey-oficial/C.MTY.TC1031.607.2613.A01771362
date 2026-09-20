//Pamela Hernández Camacho
//A01771362
//se encarga principalmente de convertir cada fecha en un número comparable 
//se llama parsear porque analizar una cadena de datos o texto y traducirla a 
//una estructura organizada que una computadora o programa pueda entender y usar fácilmente

#include "Parser.h"

bool parsearFecha(const std::string& texto, long long& clave) {
    if (texto.size() != 20) return false;

    //la fecha trae el mes como palabra (Sep), pero para armar el número necesitamos un número (09)
    const std::string meses[12] = {"Jan","Feb","Mar","Apr","May","Jun",
                                   "Jul","Aug","Sep","Oct","Nov","Dec"};
    int mes = 0;
    //¿las primeras 3 letras de la fecha (texto.substr(0, 3)) son iguales al mes en la posición i?
    for (int i = 0; i < 12; i++) { 
        if (texto.substr(0, 3) == meses[i]) mes = i + 1; //ejemplo; Sep está en la posición 8, pero septiembre es el mes 9. Por eso el código hace i + 1.
    }
    if (mes == 0) return false;
    /* Antes del for, mes empieza en 0, que es la forma de decir "todavía no lo encontré".
    Si al terminar el for sigue en 0, significa que el texto no era un mes válido*/

    //STOI convierte texto en número entero de "29" -> 29
    int dia  = std::stoi(texto.substr(4, 2)); //empieza en la pos 4 y toma dos caracteres (recortamos la parte de la fecha)
    int anio = std::stoi(texto.substr(7, 4));
    int hora = std::stoi(texto.substr(12, 2));
    int min  = std::stoi(texto.substr(15, 2));
    int seg  = std::stoi(texto.substr(18, 2));

    // lo acomoda
    /* La última fórmula acomoda cada parte en su lugar del número. 
    Por ejemplo, el año se multiplica por 10000000000 para que quede a la izquierda. */
    clave = anio * 10000000000LL + mes * 100000000LL + dia * 1000000LL
          + hora * 10000LL + min * 100LL + seg;
    return true;

    /* NOTAA bool y return false permiten avisar "esto no era una fecha válida". 
    pero Más adelante se le agregará más validaciones */
}

