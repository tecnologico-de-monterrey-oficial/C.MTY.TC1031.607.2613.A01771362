# Evidencia 1 – Ordenamiento y búsqueda por rango en una bitácora de eventos

Pamela Hernández Camacho
A01771362 

Programa de consola en C++17 que lee una bitácora de eventos (cada línea tiene fecha, hora, IP y tipo de evento), la ordena cronológicamente con el algoritmo que elija el usuario, mide el tiempo de ejecución y lo compara con una predicción, y permite buscar todos los eventos entre dos fechas usando búsqueda binaria.

**Video explicativo (3–5 min):
https://youtu.be/_YYP9J0RCm4

---

## Cómo compilar y ejecutar

Requiere `g++` (o `clang++`) con soporte para C++17. **Todos los comandos se ejecutan desde la carpeta `Evidence1`**,
porque el programa usa rutas relativas (`data/` y `out/`).

```sh
mkdir -p out build        # solo la primera vez, si no existen
g++ -std=c++17 -O2 -Iinclude src/*.cpp -o build/bitacora
./build/bitacora
```

## Cómo se usa

Al ejecutarlo aparece un menú:

| Opción | Qué hace |
|---|---|
| **1) Ordenar un archivo** | Pide, en este orden: el archivo (`log607-1.txt` desordenado o `log607-2.txt` casi ordenado), el algoritmo y tu **predicción** con su justificación. Ordena, muestra el reporte y guarda los resultados. |
| **2) Buscar por rango de fechas** | Pide fecha/hora de inicio y de fin (no tienen que existir en el archivo) y muestra y guarda los registros de ese rango. |
| **0) Salir** | Termina el programa. |

Se pueden repetir corridas (otro algoritmo, otro archivo o ambos) sin reiniciar el programa. La búsqueda por rango usa los datos
de la **última corrida de ordenamiento**, así que primero hay que ordenar un archivo (opción 1) en la misma ejecución.

**Predicción:** antes de cada corrida se elige una categoría: *Rápida* (menos de 5 ms), *Media* (de 5 a 50 ms) o
*Lenta* (más de 50 ms), junto con una razón. Después de ordenar, el programa compara tu predicción con el tiempo medido.

**Reporte de cada corrida** (en pantalla y en `out/corridas607.txt`): algoritmo, archivo, tamaño de los datos, tiempo de
ordenamiento, complejidad teórica (mejor y peor caso), verificación de que el resultado quedó ordenado, tu predicción,
el resultado medido y si coincidieron.

### Archivos que genera (carpeta `out/`)

| Archivo | Contenido |
|---|---|
| `output607.txt` | Todos los registros ordenados de la corrida más reciente, con el mismo formato del archivo original |
| `corridas607.txt` | Reporte de cada corrida (se va agregando al final) |
| `range607.txt` | Registros de la última búsqueda por rango (todos, aunque en pantalla se muestren solo algunos) |

> El enunciado menciona tanto `output608.txt` como `output607.txt`; se usó `output607.txt` por consistencia con `range607.txt` y los logs.

### Formato de fechas esperado

```
Mon DD YYYY HH:MM:SS        ejemplo: Sep 29 2024 14:37:38
```

- El mes va en inglés, con tres letras y la primera en mayúscula: `Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec`.
- Día, hora, minuto y segundo llevan siempre dos dígitos (`Sep 09`, no `Sep 9`); el año lleva cuatro y es 1970 o posterior.
- Se valida que el día exista en ese mes (incluye años bisiestos: `Feb 29 2024` es válida y `Feb 29 2025` no), que la hora sea 0–23 y que minutos y segundos sean 0–59.
- Si la fecha es inválida, o si el inicio es posterior al fin, el programa avisa y regresa al menú sin cerrarse.
- Si el rango tiene más de 40 registros, en pantalla se muestran los primeros 20 y los últimos 10; el archivo `range607.txt` siempre guarda todos.

---

## Algoritmos de ordenamiento disponibles

| # | Algoritmo | Cómo funciona (idea) | Mejor caso | Peor caso |
|---|---|---|---|---|
| 1 | Burbuja (con bandera) | Compara vecinos e intercambia; se detiene si una pasada no intercambia nada | O(n) | O(n²) |
| 2 | Selección | Busca el mínimo de lo que falta y lo coloca en su lugar | O(n²) | O(n²) |
| 3 | Swap Sort | Compara cada posición con todas las de su derecha e intercambia cada vez que encuentra una menor | O(n²) | O(n²) |
| 4 | Inserción | Desliza cada registro hacia atrás hasta encontrar su lugar | O(n) | O(n²) |
| 5 | Shell | Inserción con saltos decrecientes (secuencia de Knuth: 1, 4, 13, 40…) | O(n log n) | O(n²) |
| 6 | Merge | Divide a la mitad, ordena cada mitad y las mezcla | O(n log n) | O(n log n) |
| 7 | Quick (mediana de 3) | Escoge pivote entre primero, central y último; parte y ordena cada lado | O(n log n) | O(n²) |

**Regla de orden.** Todos los algoritmos comparan por `(fecha/hora, posición original en el archivo)`. Así, los registros con la misma fecha
y hora conservan su orden relativo y los siete algoritmos producen exactamente la misma salida.

**Nota sobre Quick Sort.** La primera versión usaba el último registro como pivote; con el archivo casi ordenado tardó 41.2 ms (contra 1.26 ms con el desordenado)
porque las particiones salían muy desiguales. Con la mediana de tres bajó a 0.62 ms.

## Resultados principales

Detalle completo en `docs/EvidenciasPruebas.pdf`. Una corrida por combinación (n = 6,818 registros):

| Algoritmo | Archivo 1 (desordenado) | Archivo 2 (casi ordenado) |
|---|---|---|
| Burbuja | 82.7 ms | 0.40 ms |
| Selección | 105.1 ms | 98.8 ms |
| Swap Sort | 85.5 ms | 21.0 ms |
| Inserción | 17.9 ms | 0.11 ms |
| Shell | 0.73 ms | 0.26 ms |
| Merge | 0.65 ms | 0.46 ms |
| Quick | 0.54 ms | 0.35 ms |

No todos los algoritmos se benefician igual de un archivo casi ordenado: Burbuja (con bandera) e Inserción mejoran muchísimo, Selección casi nada,
y Swap Sort mejora a medias. Los tiempos dependen de la computadora; las diferencias menores a 1 ms son ruido de medición.

---

## Búsqueda por rango

Se usa **búsqueda binaria** sobre los datos ya ordenados, con dos funciones (`src/search.cpp`):

- `limiteInferior(v, clave)`: primera posición cuya fecha es **mayor o igual** a la buscada.
- `limiteSuperior(v, clave)`: primera posición cuya fecha es **estrictamente mayor** a la buscada.

El rango resultante son las posiciones desde `limiteInferior(inicio)` hasta `limiteSuperior(fin)`, sin incluir esta última.
Cada búsqueda descarta la mitad de los datos en cada paso, por lo que su costo es **O(log n)**: como máximo 13 pasos para 6,818 registros,
en lugar de recorrerlos todos.

### Timestamps duplicados (caso de borde)

El archivo `log607-2.txt` tiene fechas y horas repetidas. **Política:** el rango es un **intervalo cerrado `[inicio, fin]`**. Si uno o varios registros
coinciden exactamente con el inicio o con el fin, **todos** se incluyen.

Ejemplo con las fechas `10, 20, 20, 30, 40` y el rango `[20, 35]`: el límite inferior de 20 es la posición 1 y el límite superior de 35 es la posición 4,
así que entran las posiciones 1, 2 y 3 (`20, 20, 30`). Los dos 20 quedan dentro, sin perder ni repetir ninguno. Con los datos reales, buscar del `Feb 13 2025 07:01:11`
al `Feb 13 2025 07:01:11` devuelve los dos registros con esa fecha, en su orden original.

Un rango sin registros (por ejemplo, entre dos registros consecutivos muy separados) se reporta como *rango vacío* y `range607.txt` queda vacío.

---

## Estructura del repositorio

```
Evidence1/
├── data/       log607-1.txt (desordenado) y log607-2.txt (casi ordenado)
├── include/    LogEntry.h, Parser.h, sorts.h, search.h
├── src/        main.cpp (menú), parser.cpp, sorts.cpp, search.cpp
├── docs/       EvidenciasPruebas.pdf y ReflexEvidencia1.pdf
├── out/        output607.txt, corridas607.txt, range607.txt
├── build/      programa compilado
└── README.md
```

| Archivo | Para qué sirve |
|---|---|
| `LogEntry.h` | Define un registro: fecha convertida a número (`clave`), posición original y la línea de texto |
| `parser.cpp` / `Parser.h` | Convierte `Sep 29 2024 14:37:38` en un número comparable y valida que la fecha exista |
| `sorts.cpp` / `sorts.h` | Los siete algoritmos, la regla de comparación y la verificación de orden |
| `search.cpp` / `search.h` | Las dos búsquedas binarias (límite inferior y superior) |
| `main.cpp` | El menú, la lectura y escritura de archivos, la predicción y el reporte |

El desarrollo fue incremental; el historial se puede ver con `git log --oneline` (primero la lectura y el parsing, luego cada algoritmo, el menú, la búsqueda y la validación de fechas).

---

## Política de uso de IA

Usé Claude (Anthropic) como guía durante todo el proyecto.

**Lo que permití que hiciera la IA:**
- Explicarme cada algoritmo y la búsqueda binaria paso a paso.
- Ayudarme a interpretar errores del compilador y a entender mis mediciones.

**Lo que no permití / condiciones que puse:**
- No entregar nada sin compilarlo, ejecutarlo y probarlo yo, con los datos reales.

