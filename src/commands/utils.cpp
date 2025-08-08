#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "../../include/utils.h"
#include "../../include/commands.h"
#include "../../external/termcolor.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Valida que una cadena representa un entero positivo
bool esEnteroPositivo(const string &s) {
    if (s.empty())
        return false;
    for (char c: s) {
        if (!isdigit(c))
            return false;
    }
    try {
        return std::stoi(s) > 0;
    } catch (const std::invalid_argument &) {
        return false;
    } catch (const std::out_of_range &) {
        return false;
    }
}

// Limpia la pantalla de la consola, compatible con Windows y Unix
// Fuente: https://stackoverflow.com/questions/228617/how-do-i-clear-the-console-in-both-windows-and-linux-using-c
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Configura la consola para UTF-8 en Windows
void configureUTF8() {
#ifdef _WIN32
    // Cambiar la codificación de entrada y salida estándar a UTF-8
    // Fuente: https://stackoverflow.com/questions/10882277/properly-print-utf8-characters-in-windows-console
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

// Muestra el mensaje de bienvenida
void mostrarBienvenida() {
    cout << termcolor::green;
    cout << "===============================================" << endl;
    cout << "           >>> Consola Iniciada <<<           " << endl;
    cout << "===============================================" << endl;
    cout << termcolor::reset << endl;

    cout << "Escribe 'exit', 'quit' o 'salir' para terminar." << endl;
    cout << "Si necesitas ayuda, escribe 'help' o 'ayuda'." << endl << endl;
}

// Procesa los comandos ingresados por el usuario
void procesarComandos() {
    string command;

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
        // validar comando cargar
        else if (valCargar(command)) {
            cout << termcolor::green << "Comando válido: cargar" << termcolor::reset << endl;
        }
        // validar comando listar
        else if (valListar(command)) {
            cout << termcolor::green << "Comando válido: listar_secuencias" << termcolor::reset << endl;
        }
        // validar comando histograma
        else if (valHistograma(command)) {
            cout << termcolor::green << "Comando válido: histograma" << termcolor::reset << endl;
        }
        // validar comando subsecuencia
        else if (valEsSubsecuencia(command)) {
            cout << termcolor::green << "Comando válido: es_subsecuencia" << termcolor::reset << endl;
        }
        // validar comando enmascarar
        else if (valEnmascarar(command)) {
            cout << termcolor::green << "Comando válido: enmascarar" << termcolor::reset << endl;
        }
        // validar comando guardar
        else if (valGuardar(command)) {
            cout << termcolor::green << "Comando válido: guardar" << termcolor::reset << endl;
        }
        // validar comando codificar
        else if (valCodificar(command)) {
            cout << termcolor::green << "Comando válido: codificar" << termcolor::reset << endl;
        }
        // validar comando decodificar
        else if (valDecodificar(command)) {
            cout << termcolor::green << "Comando válido: decodificar" << termcolor::reset << endl;
        }

        // Validar ruta_mas_corta y parsear parámetros
        else if (valRutaMasCorta(command)) {
            int i, j, x, y;
            if (parseRutaMasCorta(command, i, j, x, y)) {
                cout << termcolor::green << "Comando válido: ruta_mas_corta" << endl;
                cout << "Parámetros convertidos: i=" << i << ", j=" << j << ", x=" << x << ", y=" << y <<
                        termcolor::reset << endl;
            } else {
                cout << termcolor::red << "Error: Parámetros inválidos para ruta_mas_corta." << termcolor::reset <<
                        endl;
            }
        }

        // validar comando base_remota
        else if (valBaseRemota(command)) {
            int i, j;
            if (parseBaseRemota(command, i, j)) {
                cout << termcolor::green << "Comando válido: base_remota" << endl;
                cout << "Parámetros convertidos: i=" << i << ", j=" << j << termcolor::reset << endl;
            } else {
                cout << termcolor::red << "Error: Parámetros inválidos para base_remota." << termcolor::reset << endl;
            }
        }

        // validar comando clear
        else if (command == "clear") {
            clearScreen();
        }
        // validar otros
        else {
            cout << termcolor::red << "Error: Comando no reconocido o parámetros incorrectos." << termcolor::reset <<
                    endl;
        }

        cout << termcolor::cyan << "> Comando finalizado." << termcolor::reset << endl << endl;
    }
}
