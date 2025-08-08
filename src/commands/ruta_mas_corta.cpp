#include <iostream>
#include <string>
#include <stdexcept>
#include "../../include/commands.h"
#include "../../include/utils.h"
#include "../../external/termcolor.hpp"

using namespace std;

// Valida los cuatro parámetros y que sean enteros positivos
bool valRutaMasCorta(string command)
{
    int e1 = command.find(' ');
    if (e1 == -1)
        return false;
    string cmd = command.substr(0, e1);
    if (cmd != "ruta_mas_corta")
        return false;

    int e2 = command.find(' ', e1 + 1);
    if (e2 == -1)
        return false;
    int e3 = command.find(' ', e2 + 1);
    if (e3 == -1)
        return false;
    int e4 = command.find(' ', e3 + 1);
    if (e4 == -1)
        return false;

    string i = command.substr(e1 + 1, e2 - e1 - 1);
    string j = command.substr(e2 + 1, e3 - e2 - 1);
    string x = command.substr(e3 + 1, e4 - e3 - 1);
    string y = command.substr(e4 + 1);

    // No debe haber más espacios en y
    if (y.empty() || y.find(' ') != -1)
        return false;
    if (!esEnteroPositivo(i) || !esEnteroPositivo(j) || !esEnteroPositivo(x) || !esEnteroPositivo(y))
        return false;

    cout << termcolor::yellow << "[ruta_mas_corta] Parámetros recibidos: i=" << i << ", j=" << j << ", x=" << x << ", y=" << y << termcolor::reset << endl;
    return true;
}

// Convierte y parsea los parámetros de ruta_mas_corta a enteros por referencia
bool parseRutaMasCorta(const string &command, int &i, int &j, int &x, int &y)
{
    int e1 = command.find(' ');
    if (e1 == -1)
        return false;
    string cmd = command.substr(0, e1);
    if (cmd != "ruta_mas_corta")
        return false;

    int e2 = command.find(' ', e1 + 1);
    if (e2 == -1)
        return false;
    int e3 = command.find(' ', e2 + 1);
    if (e3 == -1)
        return false;
    int e4 = command.find(' ', e3 + 1);
    if (e4 == -1)
        return false;

    string si = command.substr(e1 + 1, e2 - e1 - 1);
    string sj = command.substr(e2 + 1, e3 - e2 - 1);
    string sx = command.substr(e3 + 1, e4 - e3 - 1);
    string sy = command.substr(e4 + 1);

    if (sy.empty() || sy.find(' ') != -1)
        return false;

    if (!esEnteroPositivo(si) || !esEnteroPositivo(sj) || !esEnteroPositivo(sx) || !esEnteroPositivo(sy))
        return false;

    i = std::stoi(si);
    j = std::stoi(sj);
    x = std::stoi(sx);
    y = std::stoi(sy);

    return true;
}
