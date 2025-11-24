**Proyecto de Estructuras de Datos — Consola de Bioinformática**

**Resumen:** 
Consola interactiva en C++ para análisis de secuencias biológicas (FASTA), operaciones sobre secuencias, histrogramas, enmascarado, codificación Huffman/decodificación binaria y algunos algoritmos de grafos aplicados a matrices de bases.

**Requisitos**:
- Compilador C++ compatible con C++17 (por ejemplo `g++`, `clang++`)
- `make` (opcional, hay Makefile incluido)
- Windows (PowerShell) o Linux/Unix

**Estructura del proyecto**
- `src/` : código fuente (módulos y punto de entrada `main.cpp`)
- `archivosFASTA/` : ejemplos de archivos `.fa` para pruebas
- `Makefile` : reglas de compilación

**Compilación**
- Con `make` (recomendado):

```pwsh
make
```

**Targets útiles (Makefile)**
- `make` : Compila el proyecto y genera el ejecutable `programa.exe`.
- `make run` : Compila si es necesario y ejecuta `programa.exe`.
- `make clean` : Elimina la carpeta `build/` y el ejecutable generado.

- Compilar manualmente en PowerShell:

```pwsh
& 'C:/msys64/ucrt64/bin/g++.exe' -std=c++17 (Get-ChildItem -Path ./src -Filter *.cpp) -o .\programa.exe
.\programa.exe
```

**Ejecución**
- Ejecutar el binario generado:

```pwsh
.\programa.exe
```

Al iniciarse muestra una consola interactiva donde se pueden ejecutar los comandos descritos en la sección "Comandos".

También puedes ejecutar directamente con `make run` (ejecuta el binario tras compilar):

```pwsh
make run
```

**Comandos principales**
- `help` o `ayuda [comando]` : Mostrar ayuda general o de un comando.
- `exit` / `quit` / `salir` : Salir del programa.
- `clear` : Limpiar la pantalla.
- `cargar <archivo.fa>` : Cargar secuencias desde un archivo FASTA (sobrescribe la memoria actual).
- `listar_secuencias` : Listar secuencias cargadas.
- `histograma <descripcion>` : Mostrar histograma de la secuencia identificada por la descripción.
- `es_subsecuencia <subsecuencia>` : Buscar ocurrencias de una subsecuencia en todas las secuencias cargadas.
- `enmascarar <subsecuencia>` : Reemplaza las bases de las ocurrencias por `X`.
- `guardar <archivo.fa>` : Guardar las secuencias en formato FASTA.
- `codificar <archivo.fabin>` : Generar un archivo binario con codificación Huffman de las secuencias cargadas.
- `decodificar <archivo.fabin>` : Cargar desde un archivo `.fabin` (formato binario propio del proyecto).
- `ruta_mas_corta <desc> <i> <j> <x> <y>` : Busca ruta mínima entre posiciones en la matriz de la secuencia indicada.
- `base_remota <desc> <i> <j>` : Encuentra la base más lejana igual a la indicad desde posición [i,j].

**Formato de archivos de entrada (FASTA simplificado)**
Cada secuencia en archivo `.fa` sigue el patrón:

```
>Descripción de la secuencia
ATCGATCGATCG
```

Notas:
- Las líneas vacías entre bloques están permitidas y se usan como separadores.
- El cargador intenta validar que cada secuencia tenga descripción y bases; en caso contrario la descarta y registra una advertencia.

**Módulos y archivos clave (resumen)**
- `src/main.cpp` : punto de entrada que instancia `Sistema` y arranca la consola.
- `src/sistema.h` / `src/sistema.cpp` : interfaz y lógica de la consola (parsing de comandos, flujo principal, I/O, llamadas a `Genoma`).
- `src/genoma.h` / `src/genoma.cpp` : operaciones sobre secuencias (listar, histograma, enmascarar, rutas, etc.).
- `src/secuencia.h` / `src/secuencia.cpp` : estructura `Secuencia` que guarda descripción, bases y ancho de línea.
- `src/ArbolHuffman.h` / `src/ArbolHuffman.cpp` : árbol de Huffman y funciones de codificación/decodificación.
- `src/NodoHuffman.h` / `src/NodoHuffman.cpp` : nodo del árbol de Huffman.
- `src/grafo.h` / `src/grafo.cpp` : (si aplica) utilidades para representación y búsqueda en grafos/matrices.
- `src/graph_renderer.*` : herramientas de visualización (si están presentes).
- `src/log.hpp` : macros/funciones de logging usadas por la aplicación.
- `src/termcolor.hpp` : utilidades para colorear la salida en consola.

**Ejemplo rápido**
1. Compilar: `make`
2. Ejecutar: `.\programa.exe`
3. En la consola:

```text
$ cargar archivosFASTA/yeast.fa
$ listar_secuencias
$ histograma nombre_de_secuencia
$ codificar salida.fabin
$ decodificar salida.fabin
$ exit
```

**Buenas prácticas y notas de desarrollo**
- El comando `cargar` sobrescribe las secuencias en memoria: si necesitas combinar archivos modifica el código en `Genoma`.
- El formato binario `.fabin` es propio: incluye un encabezado con frecuencias, cantidad de secuencias y para cada secuencia su descripción y datos codificados.
- El código fuente prioriza claridad y manejo de errores (validaciones de lectura/escritura, límites de tamaños).
