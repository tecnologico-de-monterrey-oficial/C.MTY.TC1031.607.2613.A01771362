//Pamela Hernández Camacho 
//A01771362

¿Dónde la recursión fue más lenta o usó más memoria?
Tiempo: fibonacciRecursive es el caso grave. No es lineal como la iterativa (O(n)); es exponencial (O(2ⁿ)), porque recalcula los mismos subproblemas una y otra vez (por ejemplo, fib(5) se vuelve a calcular varias veces dentro de fib(8)). Para n=8 casi no se nota, pero para n=40 la diferencia es brutal.
Memoria: en sum, bacteria, investment y pow, ambas versiones son O(n) en tiempo, pero la recursiva siempre gasta memoria extra: cada llamada apila un stack frame (variables locales + dirección de retorno) hasta que llega al caso base, mientras que la iterativa solo usa unas cuantas variables fijas (memoria O(1)). Esa pila de llamadas es la que te puede tronar el programa si n es grande.

Sobre buscar una fórmula antes de programar:
sumFormula resuelve en O(1) lo que a las otras dos les toma O(n) pasos. Esto dice algo importante: antes de escribir un ciclo o una recursión, vale la pena preguntarte si el problema tiene una fórmula cerrada (matemática) que lo resuelva directo. El código más rápido casi siempre es el que no se ejecuta —cuando existe una fórmula, evitas todo el trabajo repetitivo, sin importar qué tan bien optimizado esté tu ciclo o tu recursión.

Si bacteriasRecursive tuviera que calcular n = 100,000:
Tronaría por stack overflow. Cada llamada recursiva que no ha terminado se queda "abierta" en la pila de memoria esperando el resultado de la siguiente; con 100,000 llamadas anidadas, se agota el espacio de pila (normalmente ~1 MB) mucho antes de llegar al caso base. La solución es usar la versión iterativa, que resuelve el mismo problema con memoria constante (unas pocas variables), sin importar qué tan grande sea n. En general, cuando n puede crecer mucho, la iteración es la opción más segura frente a la recursión simple.