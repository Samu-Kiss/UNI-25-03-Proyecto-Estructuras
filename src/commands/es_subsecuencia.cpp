#include <iostream>
#include "../../include/commands.h"
#include "../../external/termcolor.hpp"

using namespace std;

bool valEsSubsecuencia(string command) {
    int espacio = command.find(' ');
    if (espacio == -1) {
        return false;
    }

    string cmd = command.substr(0, espacio);
    string param = command.substr(espacio + 1);

    if (cmd != "es_subsecuencia") {
        return false;
    }

    if (param.empty() || param.find(' ') != -1) {
        return false;
    }

    cout << termcolor::yellow << "[es_subsecuencia] Parámetro recibido: " << param << termcolor::reset << endl;
    return true;
}
