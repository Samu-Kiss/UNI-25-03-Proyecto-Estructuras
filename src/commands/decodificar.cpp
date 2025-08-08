#include <iostream>
#include "../../include/commands.h"
#include "../../external/termcolor.hpp"

using namespace std;

bool valDecodificar(string command)
{
    int espacio = command.find(' ');
    if (espacio == -1)
    {
        return false;
    }

    string cmd = command.substr(0, espacio);
    string param = command.substr(espacio + 1);

    if (cmd != "decodificar")
    {
        return false;
    }

    if (param.empty() || param.find(' ') != -1)
    {
        return false;
    }

    cout << termcolor::yellow << "[decodificar] Parámetro recibido: " << param << termcolor::reset << endl;
    return true;
}
