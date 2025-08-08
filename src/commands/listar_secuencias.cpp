#include <iostream>
#include "../../include/commands.h"
#include "../../external/termcolor.hpp"

using namespace std;

bool valListar(string command)
{
    if (command == "listar_secuencias")
    {
        return true;
    }

    return false;
}
