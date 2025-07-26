#include <iostream>
#include <vector>
#include <string>
#include "./include/termcolor.hpp" // Librería para colores en la consola

using namespace std;

int main()
{
    string command;
    
    cout << termcolor::green << "Consola Iniciada" << termcolor::reset << endl;
    cout << "Escribe 'exit', 'quit' o 'salir' para terminar." << endl << endl;

    while (true) {
        // Mostrar el prompt $
        cout << termcolor::yellow << "$ " << termcolor::reset;
        
        // Leer el comando del usuario
        getline(cin, command);


        // Comandos de salida
        if (command == "exit" || command == "quit" || command == "salir") {
            cout << termcolor::cyan << "Terminando Programa" << termcolor::reset << endl;
            break;
        }
        // Comando de ayuda
        else if (command == "help" || command == "ayuda") {
            cout << termcolor::blue << "Comandos disponibles:" << termcolor::reset << endl;
            cout << "  help, ayuda  - Mostrar esta ayuda" << endl;
            cout << "  exit, quit, salir - Salir de la consola" << endl;
        }
    }

    return 0;
}
