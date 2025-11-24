# 🧬 Consola de Bioinformática

## 📝 Resumen

Consola interactiva en C++ para análisis de secuencias biológicas (FASTA), operaciones sobre secuencias, histogramas, enmascarado, codificación Huffman/decodificación binaria y algunos algoritmos de grafos aplicados a matrices de bases.

Una herramienta en C++ para cargar y analizar secuencias FASTA, manipular matrices de bases, realizar codificación Huffman y ejecutar consultas útiles desde una consola interactiva.

✨ ¿Qué encontrarás aquí?
- Visualizador de comandos interactivo
- Herramientas para análisis simple de secuencias (histogramas, búsqueda, enmascarado)
- Codificación/decodificación con Huffman
- Utilidades de grafos aplicadas a matrices de bases

## 📋 Requisitos
- Compilador compatible con C++17 (`g++`, `clang++`)
- `make` (opcional — el repositorio incluye `Makefile`)
- Windows (PowerShell) o Linux/Unix

## 📁 Estructura del repositorio
- `src/` — Código fuente (incluye `main.cpp` y módulos)
- `archivosFASTA/` — Ejemplos de archivos FASTA para pruebas
- `Makefile` — Reglas de compilación y ejecución

## ⚙️ Compilación rápida

Con `make` (recomendado). El `Makefile` incluye targets útiles:

- `make` — compila el proyecto y genera el ejecutable (`programa.exe`).
- `make run` — compila si es necesario y ejecuta el binario.
- `make clean` — elimina archivos de compilación y ejecutables (limpia `build/` y `programa.exe`).

Ejecuta:

```pwsh
make        # compila el proyecto
make run    # compila si es necesario y ejecuta
make clean  # limpia artefactos de compilación
```

Compilación manual en PowerShell:

```pwsh
& 'C:/msys64/ucrt64/bin/g++.exe' -std=c++17 (Get-ChildItem -Path ./src -Filter *.cpp) -o .\programa.exe
```

## ▶️ Ejecutar

```pwsh
.\programa.exe
# o
make run
```

## 🧭 Comandos principales
- `help` o `ayuda [comando]` : Mostrar ayuda
- `cargar <archivo.fa>` : Cargar secuencias desde un FASTA
- `listar_secuencias` : Mostrar descripciones de secuencias en memoria
- `histograma <descripcion>` : Ver histograma de bases
- `es_subsecuencia <subsecuencia>` : Buscar una subsecuencia
- `enmascarar <subsecuencia>` : Reemplazar ocurrencias por `X`
- `codificar <archivo.fabin>` : Guardar codificación Huffman
- `decodificar <archivo.fabin>` : Cargar desde `.fabin`
- `ruta_mas_corta <desc> <i> <j> <x> <y>` : Buscar ruta mínima en la matriz

Ejemplo rápido en la consola:

```text
> cargar archivosFASTA/yeast.fa
> listar_secuencias
> histograma MiSecuencia
> codificar salida.fabin
> decodificar salida.fabin
> exit
```

## 🗂️ Archivos y módulos clave
- `src/main.cpp` — Punto de entrada y arranque de la consola
- `src/sistema.*` — Parsing de comandos y flujo principal
- `src/genoma.*` — Lógica de operaciones sobre secuencias
- `src/secuencia.*` — Representación de una secuencia FASTA
- `src/ArbolHuffman.*`, `src/NodoHuffman.*` — Codificación Huffman
- `src/grafo.*`, `src/graph_renderer.*` — Utilidades de grafos/visualización
- `src/main.cpp` — Punto de entrada y arranque de la consola
- `src/sistema.*` — Parsing de comandos y flujo principal
- `src/genoma.*` — Lógica de operaciones sobre secuencias
- `src/secuencia.*` — Representación de una secuencia FASTA
- `src/ArbolHuffman.*`, `src/NodoHuffman.*` — Codificación Huffman
- `src/grafo.*`, `src/graph_renderer.*` — Utilidades de grafos/visualización
- `src/main.cpp` — Punto de entrada y arranque de la consola
- `src/sistema.*` — Parsing de comandos y flujo principal
- `src/genoma.*` — Lógica de operaciones sobre secuencias
- `src/secuencia.*` — Representación de una secuencia FASTA
- `src/ArbolHuffman.*`, `src/NodoHuffman.*` — Codificación Huffman
- `src/grafo.*`, `src/graph_renderer.*` — Utilidades de grafos/visualización

## 🔧 Notas de desarrollo
- El comando `cargar` sobrescribe el contenido en memoria; modifica `Genoma` si necesitas mezclar archivos.
- El formato `.fabin` es propio del proyecto y contiene un encabezado con frecuencias para reconstruir el árbol de Huffman.
- Se usan utilidades en `src/log.hpp` y `src/termcolor.hpp` para logging y salida coloreada.
- El comando `cargar` sobrescribe el contenido en memoria; modifica `Genoma` si necesitas mezclar archivos.
- El formato `.fabin` es propio del proyecto y contiene un encabezado con frecuencias para reconstruir el árbol de Huffman.
- Se usan utilidades en `src/log.hpp` y `src/termcolor.hpp` para logging y salida coloreada.
- El comando `cargar` sobrescribe el contenido en memoria; modifica `Genoma` si necesitas mezclar archivos.
- El formato `.fabin` es propio del proyecto y contiene un encabezado con frecuencias para reconstruir el árbol de Huffman.
- Se usan utilidades en `src/log.hpp` y `src/termcolor.hpp` para logging y salida coloreada.

## ✨ Sugerencias para contribuir
- Usa ramas por funcionalidad y pull requests claros
- Añade tests o archivos en `archivosFASTA/` para nuevos casos
- Documenta cambios significativos en este `README.md`

---

_Nota: Este proyecto fue desarrollado como parte de la asignatura **Estructuras de Datos** con fines académicos y didácticos. Su objetivo es servir como ejercicio práctico para aprender a manejar secuencias FASTA, aplicar estructuras de datos (listas, árboles, grafos, etc...) y practicar técnicas de entrada/salida en C++._

Si vas a usar, adaptar o distribuir parte de este código, por favor mantén la referencia a su origen y, si puedes, comparte mejoras o incidencias para que el repositorio sea más útil para futuros estudiantes. ✨