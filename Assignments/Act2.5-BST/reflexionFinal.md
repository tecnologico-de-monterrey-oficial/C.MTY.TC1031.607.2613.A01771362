# Reflexión – BST

**1. ¿Qué aprendí al implementar estos métodos más complejos?**

Lo que más aprendí es que casi todo en un árbol binario de búsqueda se resuelve con recursión, y que lo importante es identificar bien el caso base. Eliminar un nodo fue lo más complicado, porque hay tres casos distintos: que sea hoja, que tenga un hijo o que tenga dos. En el último caso hay que reemplazarlo por su sucesor inorder (el menor del subárbol derecho) y luego borrar ese sucesor. También entendí por qué el recorrido inorder regresa los datos ordenados y que operaciones como `insert`, `find` y `whatLevelAml` dependen de la altura del árbol, o sea que si queda muy desbalanceado se vuelven O(n) en lugar de O(log n). Para `ancestors` y `whatLevelAml` me di cuenta de que basta con seguir el camino de la raíz al nodo, sin recorrer todo el árbol.

**2. ¿Qué tan útil fue Copilot en esta actividad?**

Fue útil sobre todo para lo mecánico: armar la estructura de la clase con templates, escribir los recorridos y recordar detalles de sintaxis. Me ahorró tiempo en lo repetitivo y me sirvió para comparar mi enfoque con otro. Aun así, no me quitó el trabajo de entender cómo funciona el árbol, porque para revisar y probar lo que generaba tenía que saber qué debía hacer cada método.

**3. ¿Hubo momentos en los que Copilot no te dio la solución correcta? ¿Cómo lo resolviste?**

Sí, hubo cosas que no salieron bien a la primera, sobre todo en los casos especiales y en las convenciones. Por ejemplo, la especificación no dice si la raíz está en el nivel 0 o en el 1, ni si la altura se cuenta en nodos o en aristas, y hubo que decidirlo y mantenerlo igual en `height` y en `whatLevelAml`. También hay que cuidar casos como eliminar la raíz, borrar un nodo con dos hijos o buscar un dato que no existe. Lo resolví probando el programa con esos casos a mano y dibujando el árbol en papel para comparar el resultado con lo que debía salir, en lugar de confiar en que el código compilara.

**4. ¿Consideras que usar Copilot te ayuda a aprender o puede limitar tu comprensión si se usa mal?**

Creo que ayuda si lo uso para resolver dudas, comparar soluciones y revisar mi código después de intentarlo yo. Puede limitar el aprendizaje si acepto las sugerencias sin entenderlas: el programa compila y pasa una prueba, pero yo no podría explicar ni modificar lo que escribí, por ejemplo en un examen sin herramientas. La diferencia está en si yo dirijo la herramienta o la herramienta me dirige a mí.

**5. ¿Qué harías diferente la próxima vez para aprender más?**

Escribiría primero a mano la lógica o un pseudocódigo de cada método y usaría Copilot después, para comparar o corregir. También dibujaría el árbol en papel antes de programar, escribiría mis propios casos de prueba y trataría de explicar cada función sin mirar el código. Así me aseguro de que entiendo lo que entrego y no solo de que funciona.