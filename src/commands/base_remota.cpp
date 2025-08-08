#include <iostream>
#include <string>
#include <stdexcept>
#include "../../include/commands.h"
#include "../../include/utils.h"
#include "../../external/termcolor.hpp"

using namespace std;

bool valBaseRemota(string command) {
    int e1 = command.find(' ');
    if (e1 == -1)
        return false;
    string cmd = command.substr(0, e1);
    if (cmd != "base_remota")
        return false;

    int e2 = command.find(' ', e1 + 1);
    if (e2 == -1)
        return false;

    string i = command.substr(e1 + 1, e2 - e1 - 1);
    string j = command.substr(e2 + 1);

    // No debe haber más espacios
    if (j.empty() || j.find(' ') != -1)
        return false;
    if (!esEnteroPositivo(i) || !esEnteroPositivo(j))
        return false;

    cout << termcolor::yellow << "[base_remota] Parámetros recibidos: i=" << i << ", j=" << j << termcolor::reset <<
            endl;
    return true;
}

// Convierte y parsea los parámetros de base_remota a enteros por referencia
bool parseBaseRemota(const string &command, int &i, int &j) {
    int e1 = command.find(' ');
    if (e1 == -1)
        return false;
    string cmd = command.substr(0, e1);
    if (cmd != "base_remota")
        return false;

    int e2 = command.find(' ', e1 + 1);
    if (e2 == -1)
        return false;

    string si = command.substr(e1 + 1, e2 - e1 - 1);
    string sj = command.substr(e2 + 1);

    if (sj.empty() || sj.find(' ') != -1)
        return false;

    if (!esEnteroPositivo(si) || !esEnteroPositivo(sj))
        return false;

    i = std::stoi(si);
    j = std::stoi(sj);

    return true;
}
