# ADT Linked List con Template (C++17)

## Objetivo

Implementar una lista simplemente enlazada (`LinkedList<T>`) que permita trabajar con cualquier tipo de dato compatible, mediante nodos `Node<T>` y memoria dinamica. El programa principal permite crear una lista de `int` o `string`, con datos aleatorios o capturados, y probar todas las operaciones requeridas desde un menu.

> **Nota de autoria:** este proyecto se genero con apoyo de ChatGPT a partir de los archivos de inicio y los requisitos proporcionados. Revisa y adapta el codigo y esta reflexion a lo que realmente hayas comprendido, modificado y probado antes de entregarlo.

## Estructura de archivos

```text
LinkedList_ADT/
├── Node.h                 Nodo generico con data y next
├── LinkedList.h           ADT con las operaciones y sobrecargas
├── main.cpp               Menu, datos int/string y captura/aleatorios
├── tests.cpp              Pruebas automaticas del ADT
├── test_node.cpp          Demostracion individual de Node<T>
├── pointer.cpp            Practica independiente de apuntadores
├── Fraction.h             Apoyo requerido por pointer.cpp
├── Makefile               Comandos de compilacion y pruebas
├── README.md              Documentacion y reflexion
├── tests.pdf              Evidencia generada con salidas reales
└── tests/                 Entradas y salidas reproducibles de prueba
```

## Compilacion y ejecucion (Mac / Linux)

Desde Terminal, abre la carpeta del proyecto y ejecuta:

```bash
make all
./app
```

Para correr las pruebas del ADT:

```bash
make check
```

Para los programas de apuntadores (son independientes, cada uno tiene su propio `main`):

```bash
./test_node
./pointer
```

Si no tienes `make`, compila directamente:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o app
g++ -std=c++17 -Wall -Wextra -pedantic tests.cpp -o tests_runner
./app
./tests_runner
```

**No compiles juntos `main.cpp`, `pointer.cpp`, `test_node.cpp` o `tests.cpp` en un mismo ejecutable:** cada uno contiene una funcion `main()` distinta.

## Interfaz del ADT

Los indices comienzan en 0. `insert(index, dato)` inserta **en** el indice `index`; el menu solicita insertar **despues** de un indice `i`, por lo que llama `insert(i + 1, dato)`.

| Operacion | Descripcion | Resultado ante error |
|---|---|---|
| `addFirst(dato)` | Agrega al principio | No aplica |
| `addLast(dato)` | Agrega al final | No aplica |
| `insert(index, dato)` | Inserta en el indice (0 a size) | `std::out_of_range` |
| `deleteData(dato)` | Elimina la primera coincidencia | `false` si no se encuentra |
| `deleteAt(index)` | Elimina por indice | `false` si es invalido |
| `getData(index)` | Obtiene dato por indice | `std::out_of_range` |
| `updateData(viejo, nuevo)` | Actualiza la primera coincidencia | `std::out_of_range` |
| `updateAt(index, nuevo)` | Actualiza por indice | `std::out_of_range` |
| `findData(dato)` | Devuelve el primer indice | `-1` si no existe |
| `lista[index]` | Lee el elemento por indice | `std::out_of_range` |
| `lista[index] = nuevo` | Escribe el elemento por indice | `std::out_of_range` |
| `lista2 = lista1` | Copia los nodos y datos, sin compartir nodos | No aplica |

Metodos auxiliares: `getSize()`, `empty()`, `clear()`, `print()` y alias `push_front()`/`push_back()` para compatibilidad con el ejemplo inicial.

## Menu interactivo

1. `addFirst`
2. `addLast`
3. `insert` (despues de un indice)
4. `deleteData`
5. `deleteAt`
6. `getData`
7. `updateData`
8. `updateAt`
9. `findData`
10. `[]` lectura
11. `[]` actualizacion
12. `=` duplicar lista
13. Mostrar la lista
14. Mostrar la copia
0. Regresar para crear una nueva lista o salir

Al crear la lista se elige `int` o `string`, la cantidad inicial (0 a 50) y el modo de datos. Los aleatorios `int` se generan entre 0 y 99; los `string` se eligen de un conjunto de ocho palabras. En captura manual, `string` acepta espacios.

## Pruebas y evidencias

Se compilaron los cuatro ejecutables con `g++ -std=c++17` y se realizaron **53 pruebas automaticas**, que terminaron en **53 aprobadas y 0 fallidas**. Tambien se ejecuto el menu con listas de enteros capturados, cadenas capturadas y datos aleatorios de ambos tipos.

El detalle se encuentra en `tests.pdf`, mientras que las entradas y salidas completas se conservan como archivos de texto en `tests/`. Para repetir la prueba de menu:

```bash
./app < tests/menu_int_input.txt
./app < tests/menu_string_capturado_input.txt
./app < tests/menu_random_input.txt
```

Los datos aleatorios cambian en cada ejecucion, lo cual es esperado.

## Prompts utilizados con ChatGPT

Los siguientes prompts resumen y citan las solicitudes realizadas para esta actividad (el enunciado completo y la interfaz del ADT tambien se compartieron):

1. "Dame lo todo. Diseña e implementa, en forma individual, siguiendo la especificacion de la interfaz para un ADT que represente una estructura de datos lineal (Linked List)."
2. "Esto tengo" [se compartieron los archivos iniciales `main.cpp`, `LinkedList.h`, `Node.h`, `pointer.cpp` y `test_node.cpp]. "Dame todos los esos completos dale".
3. "Esto tmb viene como requerimientos" [se compartieron las firmas y descripciones de `addFirst`, `addLast`, `insert`, `deleteData`, `deleteAt`, `getData`, `updateData`, `updateAt`, `findData`, `[]` y `=`].
4. "Dame todos los archivos".

## Reflexion sobre el uso de IA (borrador para revisar y personalizar)

**¿Que parte del codigo te propuso la IA que aceptaste tal cual y por que era correcta?**

La organizacion generica con `Node<T>` y `LinkedList<T>` conserva la idea central del proyecto original. El uso de `template <typename T>` permite reutilizar la misma estructura con `int` y `string`. La implementacion de `addFirst` conecta el nodo nuevo con la cabeza anterior y actualiza `head`, lo que es consistente con una lista simplemente enlazada. Esto tambien se reviso con pruebas automaticas.

**¿Que parte modificaste y como verificaste que tu cambio era mejor?**

Se completo el manejo de `size` (en la version inicial `push_front` no lo incrementaba), se agregaron liberacion de memoria y copia profunda, y se alinearon los nombres de funciones con la interfaz solicitada. La diferencia entre `insert(index, dato)` y "insertar despues del indice" se resolvio manteniendo el metodo con la firma de la interfaz y sumando uno al indice desde el menu. Se verifico con pruebas de insercion al principio, en medio y al final, ademas de casos invalidos.

**¿Donde se equivoco la IA (si ocurrio) y como lo detectaste?**

No se observo un fallo en las 53 pruebas automaticas ejecutadas sobre la version entregada. Hubo un punto que requirio especial revision: una parte de las instrucciones dice insertar *despues* de la posicion, mientras que la tabla indica insertar *en* la posicion. Se comprobo la interpretacion de ambas mediante una prueba explicita y se documento la solucion. Tambien se corrigio un acceso invalido que existia en el ejemplo original de `pointer.cpp`, donde se intentaba leer un apuntador despues de `delete`.

**¿Que harias diferente si no tuvieras Copilot/ChatGPT?**

Consultaria apuntes de la clase y documentacion de C++ sobre templates, apuntadores y excepciones. Empezaria por `Node`, `addFirst`, `addLast` y `print`; luego agregaria cada metodo y lo probaria con listas pequenas de dos o tres nodos. Finalmente validaria indices invalidos, copia profunda y liberacion de memoria con un programa de pruebas.

## Consideraciones tecnicas

- Todos los nodos creados con `new` se liberan en `clear()`/destructor o al eliminar un elemento.
- `operator=` crea una copia profunda: modificar una lista no modifica la otra.
- El constructor de copia y `operator=` evitan compartir apuntadores y problemas de doble liberacion.
- `getData`, `updateData`, `updateAt` y `operator[]` lanzan `std::out_of_range` cuando corresponde.
- Solo se requieren librerias de la biblioteca estandar de C++17.
