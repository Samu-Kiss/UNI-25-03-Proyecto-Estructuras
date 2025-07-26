#include <iostream>
#include "../include/commands.h"
#include "../external/termcolor.hpp"

using namespace std;

void comandoSalida() {
    cout << termcolor::red << "Terminando Programa" << termcolor::reset << endl;
    exit(0);
}

void comandoAyuda() {
    cout << termcolor::blue << "Comandos disponibles:" << termcolor::reset << endl;
    cout << "  help, ayuda  - Mostrar esta ayuda" << endl;
    cout << "  exit, quit, salir - Salir de la consola" << endl;
}