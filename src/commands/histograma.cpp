#include <iostream>
#include "../../include/commands.h"
#include "../../external/termcolor.hpp"

using namespace std;

bool valHistograma(string command)
{
    int espacio = command.find(' ');
    if (espacio == -1)
    {
        return false;
    }

    string cmd = command.substr(0, espacio);
    string param = command.substr(espacio + 1);

    if (cmd != "histograma")
    {
        return false;
    }

    if (param.empty() || param.find(' ') != -1)
    {
        return false;
    }

    cout << termcolor::yellow << "[histograma] Parámetro recibido: " << param << termcolor::reset << endl;
    return true;
}
