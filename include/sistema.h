// sistema.h
#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <string>


// Inicialización del sistema
void Inicializar();

// Bienvenida() -> void 
void Bienvenida();

// Ayuda(param) -> void
void Ayuda(const std::string& param = "");

// Cargar(nombre_archivo) -> booleano
bool Cargar(std::string nombre_archivo);

// LimpiarPantalla() -> void
void LimpiarPantalla();

// Codificar(nombre_archivo) -> void
void Codificar(std::string nombre_archivo);

// Decodificar(nombre_archivo) -> void
void Decodificar(std::string nombre_archivo);

// Guardar(nombre_archivo) -> void
void Guardar(std::string nombre_archivo);

// Salir() -> void
void Salir();

#endif // SISTEMA_H