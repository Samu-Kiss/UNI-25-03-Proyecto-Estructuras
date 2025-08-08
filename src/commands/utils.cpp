#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "../../include/utils.h"
#include "../../external/termcolor.hpp"

using namespace std;

// Valida que una cadena representa un entero positivo
bool esEnteroPositivo(const string &s)
{
    if (s.empty())
        return false;
    for (char c : s)
    {
        if (!isdigit(c))
            return false;
    }
    try
    {
        return std::stoi(s) > 0;
    }
    catch (const std::invalid_argument &)
    {
        return false;
    }
    catch (const std::out_of_range &)
    {
        return false;
    }
}

// Limpia la pantalla de la consola, compatible con Windows y Unix
// Fuente: https://stackoverflow.com/questions/228617/how-do-i-clear-the-console-in-both-windows-and-linux-using-c
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
