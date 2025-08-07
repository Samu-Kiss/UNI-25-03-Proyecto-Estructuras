#include <iostream>
#include <string>
#include "../external/termcolor.hpp" // Librería para colores en la consola
#include "../include/commands.h"     // Incluir comandos personalizados

using namespace std;

int main() {
    setlocale(LC_ALL, "Spanish"); // Configurar la localización para caracteres especiales

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
        // Comando de ayuda (con o sin parámetro)
        else if (command.rfind("help", 0) == 0 || command.rfind("ayuda", 0) == 0) {
            // Extraer parámetro si existe
            size_t espacio = command.find(' ');
            string param = "";
            if (espacio != string::npos) {
                param = command.substr(espacio + 1);
            }
            comandoAyuda(param);
        }
        //validar comando cargar
        else if (valCargar(command)) {
            cout << termcolor::green << "comando válido: cargar" << termcolor::reset << endl;
        }
        //validar comando listar
        else if (valListar(command)) {
            cout << termcolor::green << "comando válido: listar_secuencias" << termcolor::reset << endl;
        }
        //validar comando histograma
        else if (valHistograma(command)) {
            cout << termcolor::green << "comando válido: histograma" << termcolor::reset << endl;
        }
        //validar comando subsecuencia
        else if (valEsSubsecuencia(command)) {
            cout << termcolor::green << "comando válido: es_subsecuencia" << termcolor::reset << endl;
        }
        //validar comando enmascarar
        else if (valEnmascarar(command)) {
            cout << termcolor::green << "comando válido: enmascarar" << termcolor::reset << endl;
        }
        //validar comando guardar
        else if (valGuardar(command)) {
            cout << termcolor::green << "comando válido: guardar" << termcolor::reset << endl;
        }
        //validar comando codificar
        else if (valCodificar(command)) {
            cout << termcolor::green << "comando válido: codificar" << termcolor::reset << endl;
        }
        //validar comando decodificar
        else if (valDecodificar(command)) {
            cout << termcolor::green << "comando válido: decodificar" << termcolor::reset << endl;
        }
        //validar comando ruta_mas_corta
        else if (valRutaMasCorta(command)) {
            cout << termcolor::green << "comando válido: ruta_mas_corta" << termcolor::reset << endl;
        }
        //validar comando base_remota
        else if (valBaseRemota(command)) {
            cout << termcolor::green << "comando válido: base_remota" << termcolor::reset << endl;
        }
        //validar comando clear
        else if (command == "clear") {
            clearScreen();
        }
        //validar otros
        else {
            cout << termcolor::red << "Error: comando no reconocido o parámetros incorrectos." << termcolor::reset << endl;
        }

        cout << termcolor::cyan << "> Comando finalizado." << termcolor::reset << endl << endl;
    }

    return 0;
}
