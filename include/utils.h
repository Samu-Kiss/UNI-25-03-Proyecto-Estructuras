#ifndef UTILS_H
#define UTILS_H

#include <string>

// Función para validar que una cadena representa un entero positivo
bool esEnteroPositivo(const std::string &s);

// Función para limpiar la pantalla de la consola
void clearScreen();

// Función para configurar UTF-8 en Windows
void configureUTF8();

// Función para mostrar mensaje de bienvenida
void mostrarBienvenida();

// Función para procesar comandos de usuario
void procesarComandos();

#endif // UTILS_H
