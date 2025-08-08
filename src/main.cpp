#include <iostream>
#include <string>
#include "../external/termcolor.hpp" // Librería para colores en la consola
#include "../include/commands.h"     // Incluir comandos personalizados
#include "../include/utils.h"        // Incluir utilidades

using namespace std;

int main() {
    // Configurar UTF-8 para caracteres especiales en Windows
    configureUTF8();

    // Mostrar mensaje de bienvenida
    mostrarBienvenida();

    // Procesar comandos del usuario
    procesarComandos();

    return 0;
}
