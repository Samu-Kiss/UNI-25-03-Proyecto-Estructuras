#include <iostream>
#include "../../include/commands.h"
#include "../../external/termcolor.hpp"

using namespace std;

void comandoSalida() {
    cout << termcolor::red << "Terminando Programa" << termcolor::reset << endl;
    exit(0);
}
