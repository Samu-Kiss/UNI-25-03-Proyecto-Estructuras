cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y versión
project(mi_proyecto VERSION 1.0 LANGUAGES CXX)

# Usar estándar moderno de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir directorio de headers si tienes uno
include_directories(include)

# Buscar todos los archivos .cpp en src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Crear ejecutable con esos archivos
add_executable(${PROJECT_NAME} ${SOURCES})