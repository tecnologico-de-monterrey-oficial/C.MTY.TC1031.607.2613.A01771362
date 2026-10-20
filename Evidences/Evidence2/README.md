# Analizador de logs de red - C++

Aplicacion didactica para procesar registros de red por fecha/hora con estructuras
lineales implementadas mediante nodos y punteros. Desarrollada para la Parte B
de la actividad; las estructuras de la Parte A se ofrecen como **material de
referencia para estudiar y comprobar**, ya que el enunciado indica que la Parte
A debe trabajarse en clase sin asistentes de IA. Sigue esa regla con tu entrega.

## Requisitos

- macOS o Linux con `g++` compatible con C++17.
- Terminal y, opcionalmente, Visual Studio Code.
- No se necesitan paquetes externos.

## Inicio rapido en Mac (Terminal de VS Code)

1. Abre en VS Code la carpeta `Proyecto_Logs_Cpp` completa.
2. En **Terminal > New Terminal**, verifica que estes en esa carpeta (`pwd`).
3. Ejecuta `chmod +x ejecutar_mac.sh` (solo si fuera necesario).
4. Ejecuta `./ejecutar_mac.sh`.
5. Elige el archivo `1` o `2`, luego la opcion `1` del menu para ordenar.
6. En la prediccion escribe `1` para `n*log2(n)`.
7. Prueba las opciones `2`, `3`, `4` y `5`.

### Compilacion manual

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -Iinclude src/main.cpp -o app
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -Iinclude src/tests.cpp -o tests_estructuras
./tests_estructuras
./app
```

Importante: ejecuta `./app` desde la raiz del proyecto. Asi encontrara
`data/` y podra generar `out/output608.out`.

## Archivos de entrada y salida

El enunciado presenta una inconsistencia: menciona `log608-1.txt` y
`log608-2.txt` en algunas partes, pero los adjuntos reales se llaman
`log607-1.txt` y `log607-2.txt`.

- `data/log607-1.txt`: desordenado (orden aleatorio).
- `data/log607-2.txt`: casi ordenado cronologicamente.
- Los dos tienen 6,818 registros validos.
- `out/output608.out`: salida cronologica generada por la ultima corrida.

Formato de cada linea:

```text
Mmm DD AAAA HH:MM:SS IP Descripcion del evento
Sep 29 2024 14:37:38 10.14.19.188 Unauthorized Access Attempts
```

La fecha para una busqueda se escribe `Sep 14 2024`, respetando mayusculas
y dos digitos de dia. Se validan fecha real (incluidos bisiestos), hora,
formato IPv4 y descripcion no vacia.

## Estructuras y funciones

- `include/Node.h`, `include/LinkedList.h`: lista simple con `head`, `tail` y operaciones O(1).
- `include/Queue.h`: fila FIFO de lineas de entrada.
- `include/Stack.h`: pila LIFO de punteros a nodos encontrados.
- `include/DoublyLinkedList.h`: lista doble y Merge Sort estable que reenlaza los nodos.
- `src/main.cpp`: lectura, validacion, menu, ordenamiento, busqueda, estadisticas, escritura.
- `src/tests.cpp`: pruebas de estructuras vacias, un elemento, extremos, FIFO, LIFO,
  recorrido doble e integridad de enlaces tras Merge Sort.

No se usan `std::list`, `std::forward_list`, `std::queue`, `std::stack`,
`std::deque`, `std::sort` ni `std::stable_sort`. Unicamente se usan
`std::map` para contar frecuencias en estadisticas; los logs se guardan
exclusivamente en la lista doblemente ligada.

## Menu

1. Ordenar cronologicamente. Solicita prediccion antes de ordenar y mide
   tiempo, comparaciones, profundidad maxima. Escribe `out/output608.out`.
2. Buscar logs por dia (requiere ordenamiento). Detiene recorrido cuando
   se sobrepasa la fecha solicitada.
3. Mostrar ultimo dia buscado en descendente usando una Pila. Si no existe
   busqueda previa, solicita una fecha.
4. Estadisticas: total, fecha maxima, tipo maximo e IP maxima, incluidos
   TODOS los empates.
5. Salir.

En una unica ejecucion no se puede **demostrar** el orden asintotico; el
campo `Coincide con la COMPLEJIDAD TEORICA` contrasta tu prediccion con
Merge Sort (O(n log n)). Las mediciones reales sirven para comparar archivos.

## Comprobaciones y pruebas de borde

```bash
./tests_estructuras
./app
```

Para probar archivos adicionales, elige `3` y escribe, por ejemplo:

- `tests/log_invalido.txt`: reporta 4 lineas invalidas y carga 2 validas.
- `tests/log_empates.txt`: comprueba dos eventos con la misma marca de tiempo.
- `tests/no_existe.txt`: mensaje claro de archivo inexistente.

Para capturar el caso "buscar antes de ordenar", selecciona opcion 2 antes
que la 1. Para probar "ordenar dos veces", selecciona la opcion 1 de nuevo.

Las salidas reales de ejecucion verificadas se conservan en `tests/ejecucion_*.txt`.
**Los tiempos cambian** con CPU, compilacion y carga del equipo.

## Evidencia, IA y autoria

- `docs/Evidencia2.pdf`: guia / borrador de evidencia que distingue resultados
  verificados de informacion que debes completar personalmente.
- Debes hacer tus propias capturas del programa **corriendo en tu equipo**,
  historial incremental real de git/checkpoints, y grabar tu propio video sin cortes.
- No afirmes que escribiste por tu cuenta el codigo que te propuso la IA.
- El anexo del PDF incluye una falla real al crear un guion de pruebas:
  se eligio `n^2` para una prueba de Merge Sort y se corrigio a `n log n`.
- Relee, comprende, modifica y cita cualquier sugerencia de IA que decidas usar.

### Enlace de video (obligatorio antes de entregar)

**PENDIENTE: agrega aqui tu URL real de Drive o YouTube no listado.**
