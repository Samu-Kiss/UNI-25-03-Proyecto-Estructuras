#include <iostream>
#include "../external/termcolor.hpp" // Librería para colores en la consola
#include "../include/commands.h"     // Incluir comandos personalizados

using namespace std;

int main() {
    string command;

    cout << termcolor::green << "Consola Iniciada" << termcolor::reset << endl;
    cout << "Escribe 'exit', 'quit' o 'salir' para terminar." << endl;
    cout << "Si necesitas ayuda, escribe 'help' o 'ayuda'." << endl << endl;

    while (true) {
        // Mostrar el prompt $
        cout << termcolor::yellow << "$ " << termcolor::reset;

        // Leer el comando del usuario
        getline(cin, command);

        // Comandos de salida
        if (command == "exit" || command == "quit" || command == "salir") {
            comandoSalida();
        }
        // Comando de ayuda
        else if (command == "help" || command == "ayuda") {
            comandoAyuda();
        }
    }

    return 0;
}
