#include <iostream>
#include <vector>
#include <string>
#include "./include/termcolor.hpp" // Librería para colores en la consola

using namespace std;

int main()
{
    string command;
    
    cout << termcolor::green << "Consola Iniciada" << termcolor::reset << endl;

    while (true) {
        // Mostrar el prompt $
        cout << termcolor::yellow << "$ " << termcolor::reset;
        
        // Leer el comando del usuario
        getline(cin, command);

        break;
    }

    return 0;
}
