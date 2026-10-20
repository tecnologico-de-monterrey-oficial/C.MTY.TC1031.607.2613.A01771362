# Evidencia 2 - Analizador de eventos de red (C++17)

Aplicación que recibe líneas de log mediante una Fila, valida registros y los almacena en una lista doblemente ligada. Ordena cronológicamente con **Merge Sort estable** sin copiar los registros a arreglos, busca por día, muestra resultados descendentes mediante Pila y calcula estadísticas con empates.

## Compilación y ejecución

Situarse en `Evidences/Evidence2` (raíz de esta actividad):

```bash
mkdir -p output out
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -Iinclude src/main.cpp -o output/app
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -Iinclude src/tests.cpp -o output/tests_estructuras
./output/tests_estructuras
./output/app
```

Requisitos: compilador g++ con C++17, macOS o Linux. No se requieren bibliotecas externas.

## Entradas y salida

Los archivos proporcionados se llaman **log607-1.txt** (desordenado) y **log607-2.txt** (casi ordenado). Algunas instrucciones mencionan `608`; se conserva el nombre real de los archivos de datos. Ambos contienen 6,818 registros válidos.

- `data/log607-1.txt`: registros en orden aleatorio.
- `data/log607-2.txt`: registros casi ordenados.
- `out/output608.out`: archivo de resultados cronológicamente ordenados. Se reemplaza cada vez que se ordena otro archivo.

Formato de registro: `Mmm DD AAAA HH:MM:SS IP descripción del evento`.
Ejemplo: `Sep 29 2024 14:37:38 10.14.19.188 Unauthorized Access Attempts`.
Para consultar un día escribe: `Sep 14 2024` (mes en inglés, dos dígitos de día, cuatro de año).

## Menú

1. **Ordenar por fecha y hora** - solicita predicción de comparaciones, ejecuta Merge Sort estable sobre enlaces de nodos; muestra tiempo, comparaciones, profundidad máxima, verificación de orden y estabilidad; genera `out/output608.out`.
2. **Buscar registros de un día** - requiere datos previamente ordenados; detiene recorrido al superar la fecha buscada.
3. **Mostrar registros del día en descendente** - usa una Pila de punteros a nodos encontrados; reutiliza la última fecha consultada o pide una nueva.
4. **Estadísticas** - total de registros, día(s), evento(s) e IP(s) más frecuentes; muestra todos los empates.
5. **Salir**.

## Estructuras implementadas

- `include/LinkedList.h` y `include/Node.h`: lista simplemente ligada.
- `include/Queue.h`: Fila FIFO usada para leer y procesar líneas.
- `include/Stack.h`: Pila LIFO para invertir el resultado de una búsqueda.
- `include/DoublyLinkedList.h`: lista doble y Merge Sort estable que re-enlaza nodos sin copiarlos a arreglo.
- `src/tests.cpp`: programa de pruebas de estructuras.
- `src/main.cpp`: analizador y menú principal.

No se utilizan `std::list`, `std::forward_list`, `std::queue`, `std::stack`, `std::deque`, `std::sort` ni `std::stable_sort`. `std::map` se usa solo para contar frecuencias de las estadísticas.

## Pruebas y evidencias reproducibles

- `docs/pruebas_estructuras.txt`: lista vacía y un elemento, extremos, pila LIFO, fila FIFO, recorrido de lista doble y Merge Sort.
- `docs/ejecucion_log607-2.txt` y `docs/ejecucion_log607-2_final.txt`: resultados del segundo archivo.
- `tests/log_casos_borde.txt`: cuatro entradas correctas y cuatro incorrectas; empates de fecha/hora, eventos e IP.
- `docs/pruebas_casos_borde.txt`: validación de archivo, día, hora, IP, evento, búsqueda sin resultados y lista ordenada.
- `docs/prueba_archivo_inexistente.txt`: manejo de ruta que no existe.
- `out/output608.out`: registros ordenados (6,818 líneas tras la última corrida con el segundo archivo).
- `docs/Evidencia2.pdf`: documento de evidencia. **[Subir al finalizar las capturas y la reflexión.]**

Para ejecutar el caso de borde:

```bash
printf '3\ntests/log_casos_borde.txt\n2\n1\n1\n2\nSep 14 2024\n3\n2\nSep 99 2024\n2\nJan 01 2023\n4\n1\n5\n' | ./output/app
```

Esta prueba sobreescribe temporalmente `out/output608.out` con cuatro registros. Para restaurar la salida final:

```bash
printf '2\n1\n1\n5\n' | ./output/app
wc -l out/output608.out
```

## Uso de herramientas de IA

Se utilizó ChatGPT como apoyo para organizar los requisitos de la entrega, interpretar el estado de Git, preparar comandos de compilación y pruebas, revisar la correspondencia entre archivos y documentación, y crear borradores documentales. Las sugerencias se verificaron mediante ejecuciones en la terminal y revisión del repositorio. Una sugerencia anterior de README incluía `./ejecutar_mac.sh`, archivo que no existía; se corrigió usando los comandos manuales de compilación probados. 

## Video demostrativo (obligatorio)
https://youtu.be/GkUFwjLrNLw


El video debe mostrar la aplicación con ambos archivos y explicar Fila, lista doble, Pila y Merge Sort en 3-5 minutos, con grabación de pantalla y voz, sin cortes.
