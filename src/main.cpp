#include <iostream>
#include <string>
#include "../external/termcolor.hpp" // Librería para colores en la consola
#include "../include/sistema.h"
#include "../include/genoma.h"
#include <climits>
#include <sstream>
#include <vector>

using namespace std;

// Devuelve cuántos parámetros reales hay después del comando.
// Ej: "cargar archivo" -> 1
int numParams(const string &input) {
    size_t pos = input.find(' ');
    if (pos == string::npos) return 0;           // no hay espacio => sin parámetros
    string rest = input.substr(pos + 1);         // lo que viene después del comando
    istringstream iss(rest);
    string tok;
    int count = 0;
    while (iss >> tok) ++count;                  // >> ignora espacios extra y tokens vacíos
    return count;
}

// Parsea una cadena y devuelve true si representa un entero positivo (>0).
// Si es válido, asigna el valor a `out`.
bool parsePositiveInt(const string &s, int &out) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(static_cast<unsigned char>(c))) return false;
    }
    try {
        long v = stol(s);
        if (v <= 0 || v > INT_MAX) return false;
        out = static_cast<int>(v);
        return true;
    } catch (...) {
        return false;
    }
}

int main() {
    Inicializar();
    Bienvenida();

    string input;
    while (true) {
        cout << "\n" <<termcolor::yellow << "$ " << termcolor::reset;

        getline(cin, input);

        // Comando de salida
        if (input == "exit" || input == "quit" || input == "salir") {
            if (numParams(input) != 0) {
                cout << termcolor::red << "Error: El comando 'salir' no requiere parámetros." << termcolor::reset << endl;
            } else {
                Salir();
            }
        }
        // Comando de clear
        else if (input == "clear") {
            if (numParams(input) != 0) {
                cout << termcolor::red << "Error: El comando 'clear' no requiere parámetros." << termcolor::reset << endl;
            } else {
                LimpiarPantalla();
            }
        }
        // Comando de ayuda (con o sin parámetro)
        else if (input.rfind("help", 0) == 0 || input.rfind("ayuda", 0) == 0) {
            if (numParams(input) > 1) {
                cout << termcolor::red << "Error: El comando 'ayuda' o 'help' acepta como máximo 1 parámetro. Uso: ayuda [comando]" << termcolor::reset << endl;
                continue;
            }
                // Extraer parámetro si existe, ignorando espacios en blanco extra.
                istringstream iss(input);
                string cmd, param;
                iss >> cmd; // extrae 'help' o 'ayuda'
                if (!(iss >> param)) param = ""; // si no hay token, param queda vacío (ignora espacios finales)
                Ayuda(param);
        } 
        // Comando de cargar
        else if (input.rfind("cargar", 0) == 0) {
            if (numParams(input) != 1) {
                cout << termcolor::red << "Error: El comando 'cargar' requiere 1 parámetro. Uso: cargar <nombre_archivo.fasta>" << termcolor::reset << endl;
            } else {
                //Verificar si el archivo tiene la extensión .fasta
                string nombre_archivo = input.substr(input.find(' ') + 1);
                if (nombre_archivo.substr(nombre_archivo.find_last_of('.') + 1) != "fasta") {
                    cout << termcolor::red << "Error: El archivo debe tener la extensión .fasta" << termcolor::reset << endl;
                } else {
                    Cargar(nombre_archivo);
                }
            }
        }
        // Comando de guardar
        else if (input.rfind("guardar", 0) == 0) {
            if (numParams(input) != 1) {
                cout << termcolor::red << "Error: El comando 'guardar' requiere 1 parámetro. Uso: guardar <nombre_archivo.fasta>" << termcolor::reset << endl;
            } else {
                //Verificar si el archivo tiene la extensión .fasta

                string nombre_archivo = input.substr(input.find(' ') + 1);
                if (nombre_archivo.substr(nombre_archivo.find_last_of('.') + 1) != "fasta") {
                    cout << termcolor::red << "Error: El archivo debe tener la extensión .fasta" << termcolor::reset << endl;
                } else {
                    Guardar(nombre_archivo);
                }
            }
        }
        // Comando de codificar
        else if (input.rfind("codificar", 0) == 0) {
            if (numParams(input) != 1) {
                cout << termcolor::red << "Error: El comando 'codificar' requiere 1 parámetro. Uso: codificar <nombre_archivo.fabin>" << termcolor::reset << endl;
            } else {
                //Verificar si el archivo tiene la extensión .fabin
                string nombre_archivo = input.substr(input.find(' ') + 1);
                if (nombre_archivo.substr(nombre_archivo.find_last_of('.') + 1) != "fabin") {
                    cout << termcolor::red << "Error: El archivo debe tener la extensión .fabin" << termcolor::reset << endl;
                } else {
                    Codificar(nombre_archivo);
                }
            }
        }
        // Comando de decodificar
        else if (input.rfind("decodificar", 0) == 0) {
            if (numParams(input) != 1) {
                cout << termcolor::red << "Error: El comando 'decodificar' requiere 1 parámetro. Uso: decodificar <nombre_archivo.fabin>" << termcolor::reset << endl;
            } else {
                //Verificar si el archivo tiene la extensión .fabin
                string nombre_archivo = input.substr(input.find(' ') + 1);
                if (nombre_archivo.substr(nombre_archivo.find_last_of('.') + 1) != "fabin") {
                    cout << termcolor::red << "Error: El archivo debe tener la extensión .fabin" << termcolor::reset << endl;
                } else {
                    Decodificar(nombre_archivo);
                }
            }
        }
        else if (input == "listar_secuencias") {
            ListarSecuencias();
        }
        else if (input.rfind("histograma", 0) == 0) {
            if (numParams(input) != 1) {
                cout << termcolor::red << "Error: El comando 'histograma' requiere 1 parámetro. Uso: histograma <descripcion_secuencia>" << termcolor::reset << endl;
            } else {
                string descripcion = input.substr(input.find(' ') + 1);
                Histograma(descripcion.c_str());
            }
        }
        else if (input.rfind("es_subsecuencia", 0) == 0) {
            if (numParams(input) != 1) {
                cout << termcolor::red << "Error: El comando 'es_subsecuencia' requiere 1 parámetro. Uso: es_subsecuencia <subsecuencia>" << termcolor::reset << endl;
            } else {
                string subsecuencia = input.substr(input.find(' ') + 1);
                EsSubsecuencia(subsecuencia.c_str());
            }
        }
        else if (input.rfind("enmascarar", 0) == 0) {
            if (numParams(input) != 1) {
                cout << termcolor::red << "Error: El comando 'enmascarar' requiere 1 parámetro. Uso: enmascarar <subsecuencia>" << termcolor::reset << endl;
            } else {
                string subsecuencia = input.substr(input.find(' ') + 1);
                Enmascarar(subsecuencia.c_str());
            }
        }
        // Comando de ruta_mas_corta
        else if (input.rfind("ruta_mas_corta", 0) == 0) {
            if (numParams(input) != 5) {
                cout << termcolor::red << "Error: El comando 'ruta_mas_corta' requiere 5 parámetros. Uso: ruta_mas_corta <descripcion_secuencia> <i> <j> <x> <y>" << termcolor::reset << endl;
            } else {
                istringstream iss(input);
                string cmd, descripcion;
                string si, sj, sx, sy;
                iss >> cmd >> descripcion >> si >> sj >> sx >> sy;
                int i, j, x, y;
                if (!parsePositiveInt(si, i) || !parsePositiveInt(sj, j) || !parsePositiveInt(sx, x) || !parsePositiveInt(sy, y)) {
                    cout << termcolor::red << "Error: Los parámetros i, j, x, y deben ser enteros positivos (por ejemplo: 1 2 3 4)." << termcolor::reset << endl;
                } else {
                    RutaMasCorta(descripcion.c_str(), i, j, x, y);
                }
            }
        }
        // Comando de base_remota
        else if (input.rfind("base_remota", 0) == 0) {
            if (numParams(input) != 3) {
                cout << termcolor::red << "Error: El comando 'base_remota' requiere 3 parámetros. Uso: base_remota <descripcion_secuencia> <i> <j>" << termcolor::reset << endl;
            } else {
                istringstream iss(input);
                string cmd, descripcion;
                string si, sj;
                iss >> cmd >> descripcion >> si >> sj;
                int i, j;
                if (!parsePositiveInt(si, i) || !parsePositiveInt(sj, j)) {
                    cout << termcolor::red << "Error: Los parámetros i y j deben ser enteros positivos (por ejemplo: 1 2)." << termcolor::reset << endl;
                } else {
                    BaseRemota(descripcion.c_str(), i, j);
                }
            }
        }
        // Caso por defecto
        else {
            cout << termcolor::red << "Comando no reconocido: " << input << termcolor::reset << endl;
        }
    }
    return 0;
}