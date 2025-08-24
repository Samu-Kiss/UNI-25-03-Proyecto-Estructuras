# Proyecto de Estructuras de Datos - Consola de Bioinformática

Este proyecto implementa una consola interactiva para el análisis de secuencias biológicas, desarrollado en C++ como parte del curso de Estructuras de Datos.

## Características

- **Consola interactiva** con soporte para comandos de bioinformática
- **Gestión de secuencias** desde archivos de texto
- **Análisis estadístico** con histogramas
- **Operaciones de secuencias** como subsecuencias y enmascaramiento
- **Codificación/decodificación** de secuencias
- **Algoritmos de grafos** para rutas más cortas y bases remotas
- **Colores en terminal** para mejor experiencia de usuario

## Estructura del Proyecto

```
├── src/
│   ├── main.cpp                    # Punto de entrada del programa
│   └── commands/                   # Implementación de comandos
│       ├── ayuda.cpp              # Sistema de ayuda
│       ├── cargar.cpp             # Carga de secuencias desde archivos
│       ├── listar_secuencias.cpp  # Listado de secuencias en memoria
│       ├── histograma.cpp         # Análisis estadístico
│       ├── es_subsecuencia.cpp    # Verificación de subsecuencias
│       ├── enmascarar.cpp         # Enmascaramiento de secuencias
│       ├── codificar.cpp          # Codificación de secuencias
│       ├── decodificar.cpp        # Decodificación de secuencias
│       ├── ruta_mas_corta.cpp     # Algoritmo de ruta más corta
│       ├── base_remota.cpp        # Cálculo de bases remotas
│       └── utils.cpp              # Utilidades auxiliares
├── include/
│   ├── commands.h                 # Declaraciones de comandos
│   └── utils.h                   # Declaraciones de utilidades
├── external/
│   └── termcolor.hpp             # Librería para colores en terminal
└── CMakeLists.txt               # Configuración de CMake
```

## Compilación
### Opción 1: Compilación manual

#### En Windows (PowerShell)
```bash
g++ (Get-ChildItem src/*.cpp) -o ./src/programa.exe && ./src/programa.exe 
```

## Uso

Una vez compilado y ejecutado, el programa presenta una consola interactiva con los siguientes comandos disponibles:

### Comandos Básicos
- `help` o `ayuda` - Mostrar ayuda general o específica de un comando
- `exit`, `quit` o `salir` - Salir de la consola
- `clear` o `cls` - Limpiar la pantalla

### Gestión de Secuencias
- `cargar <archivo>` - Cargar secuencias desde un archivo de texto
- `listar_secuencias` - Mostrar todas las secuencias cargadas en memoria
- `guardar <archivo> <descripcion>` - Guardar una secuencia específica

### Análisis de Secuencias
- `histograma <descripcion>` - Generar histograma de frecuencias de una secuencia
- `es_subsecuencia <seq1> <seq2>` - Verificar si seq1 es subsecuencia de seq2
- `enmascarar <descripcion> <patron>` - Enmascarar secuencia con un patrón

### Codificación
- `codificar <descripcion>` - Codificar una secuencia
- `decodificar <descripcion>` - Decodificar una secuencia

### Algoritmos Avanzados
- `ruta_mas_corta <i> <j> <x> <y>` - Encontrar la ruta más corta en una matriz
- `base_remota <i> <j>` - Calcular la base más remota desde una posición

## Formato de Archivos

Las secuencias deben estar en archivos de texto con el siguiente formato:
```
>Descripción de la secuencia 1
ATCGATCGATCG
>Descripción de la secuencia 2
GCTAGCTAGCTA
```

## Notas de Desarrollo

- El proyecto está diseñado para ser modular con comandos separados en archivos individuales
- Se incluye soporte para colores en terminal mediante la librería `termcolor.hpp`
- Configurado para Windows con soporte UTF-8 para caracteres especiales
- Compatible con sistemas Unix/Linux
