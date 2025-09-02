#include "./termcolor.hpp" // Librería para colores en la consola
#include "./secuencia.h"
#include "./genoma.h"
#include "./log.hpp"
#include <iostream>
#include <string>
#include <climits>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

Genoma genoma;

// (Helper de logs centralizado en log.hpp)

// Devuelve cuántos parámetros reales hay después del comando.
// Ej: "cargar archivo" -> 1
int numParams(const string &input) {
    size_t pos = input.find(' ');
    if (pos == string::npos) return 0; // no hay espacio => sin parámetros
    string rest = input.substr(pos + 1); // lo que viene después del comando
    istringstream iss(rest);
    string tok;
    int count = 0;
    while (iss >> tok) ++count; // >> ignora espacios extra y tokens vacíos
    return count;
}

// Parsea una cadena y devuelve true si representa un entero positivo (>0).
// Si es válido, asigna el valor a `out`.
bool parsePositiveInt(const string &s, int &out) {
    if (s.empty()) return false;
    for (char c: s) {
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

// Función para guardar un archivo
void Guardar(const string &nombre_archivo) {
    // Posibles estados:
    // No hay secuencias cargadas
    // Archivo guardado exitosamente
    // Error al guardar el archivo
    if (genoma.secuencias.empty()) {
        LOG_ADVERTENCIA("Guardar", "No hay secuencias cargadas.");
        return;
    }

    // Intentar abrir el archivo
    ofstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        LOG_ERROR("Guardar", "No se pudo abrir el archivo para guardar.");
        return;
    }

    // Guardar las secuencias en el archivo
    for (const Secuencia& secuencia : genoma.secuencias) {
        archivo << ">" << secuencia.descripcion << endl;

        vector<char>::const_iterator it = secuencia.bases.begin();
        for (size_t i = 0; i < secuencia.bases.size(); ++i) {
            if (i % secuencia.ancho_linea == 0 && i != 0) archivo << endl;
            archivo << secuencia.bases[i];
        }

        archivo << endl;
    }

    archivo.close();
    LOG_EXITO("Guardar", "Archivo guardado exitosamente.");
}

// Función para codificar un archivo
void Codificar(const string &nombre_archivo) {
    //TODO: Implementación de la codificación
    //ESTO SE HACE EN LA SEGUNDA ENTREGA
}

// Función para decodificar un archivo
void Decodificar(const string &nombre_archivo) {
    //TODO: Implementación de la decodificación
    //ESTO SE HACE EN LA SEGUNDA ENTREGA
}

// Función para salir del programa
void Salir() {
    LOG_EXITO("Sistema", "Saliendo del programa...");
    exit(0);
}

// Funcion para inicializar la consola
void Inicializar() {
#ifdef _WIN32
    // Cambiar la codificación de entrada y salida estándar a UTF-8
    // Fuente: https://stackoverflow.com/questions/10882277/properly-print-utf8-characters-in-windows-console
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

// Función para mostrar un mensaje de bienvenida
void Bienvenida() {
    cout << termcolor::green;
    cout << "===============================================" << endl;
    cout << "           >>> Consola Iniciada <<<           " << endl;
    cout << "===============================================" << endl;
    cout << termcolor::reset << endl;

    cout << "Escribe 'exit', 'quit' o 'salir' para terminar." << endl;
    cout << "Si necesitas ayuda, escribe 'help' o 'ayuda'." << endl << endl;
}

// Ayuda() -> void
void Ayuda(const string &param) {
    if (param.empty()) {
        cout << termcolor::blue;
        cout << "==============================================================================================================" << endl;
        cout << "                                         >>> Comandos disponibles <<<                                         " << endl;
        cout << "==============================================================================================================" << termcolor::reset << endl << endl;
        cout << "  help, ayuda [comando]                                           - Mostrar esta ayuda o ayuda de un comando" << endl;
        cout << "  exit, quit, salir                                               - Salir de la consola" << endl;
        cout << "  cargar <nombre_archivo.fa>                                      - Cargar secuencias desde un archivo" << endl;
        cout << "  listar_secuencias                                               - Listar todas las secuencias en memoria" << endl;
        cout << "  histograma <descripcion_secuencia>                              - Mostrar histograma de una secuencia" << endl;
        cout << "  es_subsecuencia <subsecuencia>                                  - Verificar si existe una subsecuencia" << endl;
        cout << "  enmascarar <subsecuencia>                                       - Enmascarar una subsecuencia" << endl;
        cout << "  guardar <nombre_archivo.fa>                                     - Guardar secuencias en un archivo" << endl;
        cout << "  codificar <nombre_archivo.fabin>                                - Codificar una secuencia" << endl;
        cout << "  decodificar <nombre_archivo.fabin>                              - Decodificar una secuencia" << endl;
        cout << "  ruta_mas_corta <descripcion_secuencia> <i> <j> <x> <y>          - Buscar ruta más corta" << endl;
        cout << "  base_remota <descripcion_secuencia> <i> <j>                     - Buscar base remota" << endl;
        cout << "  clear                                                           - Limpiar la pantalla" << endl;
        return;
    }

    if (param == "cargar") {
        cout << termcolor::blue << "cargar <nombre_archivo>" << termcolor::reset << endl;
        cout << "Carga en memoria los datos contenidos en el archivo identificado por nombre_archivo, es decir, utiliza adecuadamente las estructuras lineales para cargar la información de los genomas en memoria. Si dentro de la misma sesión de trabajo ya se han cargado otros archivos de secuencias (usando el comando cargar), la información debe sobreescribirse en memoria, es decir, no se deben combinar informaciones de secuencias de diferentes archivos." << endl;
    } else if (param == "listar_secuencias") {
        cout << termcolor::blue << "listar_secuencias" << termcolor::reset << endl;
        cout << "Imprime la cantidad de secuencias actualmente en memoria, y luego, en n líneas (una para secuencia) la información básica (nombre y cantidad de bases diferentes) de cada secuencia. Si la secuencia es completa (no tiene el código '-' ) indica la cantidad de bases exactas (contiene b bases); si la secuencia es incompleta (incluye uno o varios códigos '-') indica la cantidad mínima de bases, sin contar el código '-' (contiene al menos b bases)." << endl;
    } else if (param == "histograma") {
        cout << termcolor::blue << "histograma <descripcion_secuencia>" << termcolor::reset << endl;
        cout << "Imprime el histograma de una secuencia, en caso de que exista. El histograma se define como el conteo (frecuencia) de cada código en la secuencia. Por cada línea se escribe el código y la cantidad de veces que aparece en la secuencia. El ordenamiento del histograma está dado por la tabla correspondiente. El código '-' debe incluirse también como parte del histograma." << endl;
    } else if (param == "es_subsecuencia") {
        cout << termcolor::blue << "es_subsecuencia <subsecuencia>" << termcolor::reset << endl;
        cout << "Determina si una subsecuencia (secuencia corta de bases) dada por el usuario, existe dentro de las secuencias cargadas en memoria. Si es así, determina la cantidad de veces en las que esta subsecuencia dada se repite. No es necesario indicar el nombre de la secuencia donde se encuentra la repetición (el conteo es general sobre todas las secuencias cargadas en memoria)." << endl;
    } else if (param == "enmascarar") {
        cout << termcolor::blue << "enmascarar <subsecuencia>" << termcolor::reset << endl;
        cout << "Enmascara una subsecuencia (secuencia corta de bases) dada por el usuario, si existe. Los elementos que pertenecen a la subsecuencia se enmascaran cambiando cada base individual por el código 'X'. No es necesario indicar el nombre de la secuencia donde se realiza el enmascarado (el proceso es general sobre todas las secuencias cargadas en memoria)." << endl;
    } else if (param == "guardar") {
        cout << termcolor::blue << "guardar <nombre_archivo>" << termcolor::reset << endl;
        cout << "Guarda en el archivo nombre_archivo las secuencias cargadas en memoria. Se debe tener en cuenta la justificación (de líneas) de cada secuencia inicial, así como las posibles modificaciones que hayan sufrir las secuencias en memoria (después de enmascarar)." << endl;
    } else if (param == "codificar") {
        cout << termcolor::blue << "codificar <secuencia>" << termcolor::reset << endl;
        cout << "El comando debe generar el archivo binario con la correspondiente codificación de Huffman en el formato descrito más arriba, almacenándolo en disco bajo el nombre nombre_archivo.fabin . Si no hay secuencias cargadas en memoria, o si el archivo no puede escribirse correctamente, el comandodebe mostrar el mensaje correspondiente." << endl;
    } else if (param == "decodificar") {
        cout << termcolor::blue << "decodificar <secuencia>" << termcolor::reset << endl;
        cout << "El comando debe cargar en memoria las secuencias contenidas en el archivo binario nombre_archivo.fabin , que contiene una codificación Huffman de un conjunto de secuencias en el formato descrito más arriba. Si dentro de la misma sesión de trabajo ya se han cargado otros archivos de secuencias (usando el comando cargar), la información debe sobreescribirse en memoria, es decir, no se deben combinar informaciones de secuencias de diferentes archivos. Si por alguna razón no es posible cargar la información de codificación, o no es posible realizar el proceso de decodificación, el comando debe mostrar el mensaje de error" << endl;
    } else if (param == "ruta_mas_corta") {
        cout << termcolor::blue << "ruta_mas_corta <i> <j> <x> <y>" << termcolor::reset << endl;
        cout << "El comando debe imprimir en pantalla la secuencia de vértices (bases) del grafo que describen la ruta más corta entre la base ubicada en la posición [i, j] de la matriz de la secuencia descripcion_secuencia y la base ubicada en la posición [x, y] de la misma matriz. Así mismo, debe imprimir el costo total de la ruta, teniendo en cuenta el peso que tiene cada conexión entre bases" << endl;
    } else if (param == "base_remota") {
        cout << termcolor::blue << "base_remota <i> <j>" << termcolor::reset << endl;
        cout << "Para la base ubicada en la posición [i, j] de la matriz de la secuencia descripcion_secuencia , el comando busca la ubicación de la misma base (misma letra) más lejana dentro de la matriz. Para esta base remota, el comando debe imprimir en pantalla su ubicación, la secuencia de vértices (bases) que describen la ruta entre la base origen y la base remota, y el costo total de la ruta, teniendo en cuenta el peso que tiene cada conexión entre bases" << endl;
    } else if (param == "clear") {
        cout << termcolor::blue << "clear" << termcolor::reset << endl;
        cout << "Limpia la pantalla de la consola." << endl;
    } else if (param == "help" || param == "ayuda") {
        cout << termcolor::blue << "help, ayuda [comando]" << termcolor::reset << endl;
        cout << "Muestra la ayuda general o de un comando específico." << endl;
    } else if (param == "exit" || param == "quit" || param == "salir") {
        cout << termcolor::blue << "exit, quit, salir" << termcolor::reset << endl;
        cout << "Termina la ejecución de la aplicación." << endl;
    } else {
        cout << termcolor::red << "\t[Help/Error]: No existe ayuda para el comando: " << param << termcolor::reset << endl;
    }
}

// Función para limpiar la pantalla
void LimpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Función para cargar un archivo
bool Cargar(const string &nombre_archivo) {
    genoma.secuencias.clear();
    ifstream archivo_entrada(nombre_archivo);
    if (!archivo_entrada) {
        LOG_ERROR("Cargar", string("No se pudo abrir el archivo ") + nombre_archivo);
        return false;
    }

    // Verificar si el archivo está vacío
    if (archivo_entrada.peek() == EOF) {
        LOG_ERROR("Cargar", string("El archivo ") + nombre_archivo + " está vacío.");
        archivo_entrada.close();
        return false;
    }

    string linea;
    Secuencia nueva_secuencia;
    bool firstLine = false;
    int countAdded = 0; // contador de secuencias añadidas en esta carga

    while (getline(archivo_entrada, linea)) {
        if (linea.empty()) {
            // Línea vacía actúa como separador entre secuencias.
            if (!nueva_secuencia.descripcion.empty() || !nueva_secuencia.bases.empty()) {
                if (nueva_secuencia.descripcion.empty() && !nueva_secuencia.bases.empty()) {
                    LOG_ADVERTENCIA("Cargar", string("Se encontró una secuencia sin descripción en el archivo ") + nombre_archivo + ". Se descarta la secuencia.");
                } else if (!nueva_secuencia.descripcion.empty() && nueva_secuencia.bases.empty()) {
                    LOG_ADVERTENCIA("Cargar", string("La secuencia '") + nueva_secuencia.descripcion + "' no contiene bases. Se descarta la secuencia.");
                } else {
                    genoma.secuencias.push_back(nueva_secuencia);
                    ++countAdded;
                    LOG_EXITO("Cargar", string("Secuencia añadida: ") + nueva_secuencia.descripcion);
                }
                nueva_secuencia = Secuencia();
                firstLine = false;
            } else {
                LOG_ADVERTENCIA("Cargar", string("Línea vacía en el archivo ") + nombre_archivo);
            }
            continue;
        }

        // La línea que marca el inicio de la secuencia es ">{descripcion de la secuencia}"
        if (linea[0] == '>') {
            // Si había una secuencia en construcción, procesarla antes de comenzar la nueva
            if (!nueva_secuencia.descripcion.empty() || !nueva_secuencia.bases.empty()) {
                if (nueva_secuencia.descripcion.empty() && !nueva_secuencia.bases.empty()) {
                    LOG_ADVERTENCIA("Cargar", string("Se encontró una secuencia sin descripción en el archivo ") + nombre_archivo + ". Se descarta la secuencia.");
                } else if (!nueva_secuencia.descripcion.empty() && nueva_secuencia.bases.empty()) {
                    LOG_ADVERTENCIA("Cargar", string("La secuencia '") + nueva_secuencia.descripcion + "' no contiene bases. Se descarta la secuencia.");
                } else {
                    genoma.secuencias.push_back(nueva_secuencia);
                    ++countAdded;
                    LOG_EXITO("Cargar", string("Secuencia añadida: ") + nueva_secuencia.descripcion);
                }
            }
            nueva_secuencia = Secuencia();
            nueva_secuencia.descripcion = linea.substr(1);
            firstLine = true;
        } else {
            if (firstLine) {
                nueva_secuencia.ancho_linea = linea.length();
                firstLine = false;
            }
            for (char base: linea) {
                nueva_secuencia.bases.push_back(base);
            }
        }
    }

    // Agregar la última secuencia si existe y es válida
    if (!nueva_secuencia.descripcion.empty() || !nueva_secuencia.bases.empty()) {
        if (nueva_secuencia.descripcion.empty() && !nueva_secuencia.bases.empty()) {
            LOG_ADVERTENCIA("Cargar", string("Se encontró una secuencia sin descripción en el archivo ") + nombre_archivo + ". Se descarta la secuencia.");
        } else if (!nueva_secuencia.descripcion.empty() && nueva_secuencia.bases.empty()) {
            LOG_ADVERTENCIA("Cargar", string("La secuencia '") + nueva_secuencia.descripcion + "' no contiene bases. Se descarta la secuencia.");
        } else {
            genoma.secuencias.push_back(nueva_secuencia);
            ++countAdded;
            LOG_EXITO("Cargar", string("Secuencia añadida: ") + nueva_secuencia.descripcion);
        }
    }

    archivo_entrada.close();

    // Informar cuántas secuencias se añadieron en esta operación
    if (countAdded == 0) {
        LOG_ERROR("Cargar", string("No se cargó ninguna secuencia desde el archivo ") + nombre_archivo);
        return false;
    } else {
        LOG_EXITO("Cargar", string("Se añadieron ") + to_string(countAdded) + " secuencia(s) desde '" + nombre_archivo + "'.");
    }

    return true;
}

int main() {
    Inicializar();
    Bienvenida();

    string input;
    while (true) {
        cout << "\n" << termcolor::yellow << "$ " << termcolor::reset;

        getline(cin, input);

        // Comando de salida
        if (input.rfind("exit", 0) == 0 || input.rfind("quit", 0) == 0 || input.rfind("salir", 0) == 0) {
            if (numParams(input) != 0) {
                LOG_ERROR("Salir", "El comando 'salir' no requiere parámetros.");
            } else {
                Salir();
            }
        }
        // Comando de clear
        else if (input.rfind("clear", 0) == 0) {
            if (numParams(input) != 0) {
                LOG_ERROR("Clear", "El comando 'clear' no requiere parámetros.");
            } else {
                LimpiarPantalla();
            }
        }
        // Comando de ayuda (con o sin parámetro)
        else if (input.rfind("help", 0) == 0 || input.rfind("ayuda", 0) == 0) {
            if (numParams(input) > 1) {
                LOG_ERROR("Help", "El comando 'ayuda' o 'help' acepta como máximo 1 parámetro. Uso: ayuda [comando]");
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
                LOG_ERROR("Cargar", "El comando 'cargar' requiere 1 parámetro. Uso: cargar <nombre_archivo.fa>");
            } else {
                string nombre_archivo = input.substr(input.find(' ') + 1);
                if (nombre_archivo.substr(nombre_archivo.find_last_of('.') + 1) != "fa") {
                    LOG_ERROR("Cargar", "El archivo debe tener la extensión .fa");
                } else {
                    Cargar(nombre_archivo);
                }
            }
        }
        // Comando de guardar
        else if (input.rfind("guardar", 0) == 0) {
            if (numParams(input) != 1) { 
                LOG_ERROR("Guardar", "El comando 'guardar' requiere 1 parámetro. Uso: guardar <nombre_archivo.fa>"); 
            } else {
                string nombre_archivo = input.substr(input.find(' ') + 1);
                if (nombre_archivo.substr(nombre_archivo.find_last_of('.') + 1) != "fa") {
                    LOG_ERROR("Guardar", "El archivo debe tener la extensión .fa");
                } else {
                    Guardar(nombre_archivo);
                }
            }
        }
        // Comando de codificar
        else if (input.rfind("codificar", 0) == 0) {
            if (numParams(input) != 1) {
                LOG_ERROR("Codificar", "El comando 'codificar' requiere 1 parámetro. Uso: codificar <nombre_archivo.fabin>");
            } else {
                string nombre_archivo = input.substr(input.find(' ') + 1);
                if (nombre_archivo.substr(nombre_archivo.find_last_of('.') + 1) != "fabin") {
                    LOG_ERROR("Codificar", "El archivo debe tener la extensión .fabin");
                } else {
                    Codificar(nombre_archivo);
                }
            }
        }
        // Comando de decodificar
        else if (input.rfind("decodificar", 0) == 0) {
            if (numParams(input) != 1) {
                LOG_ERROR("Decodificar", "El comando 'decodificar' requiere 1 parámetro. Uso: decodificar <nombre_archivo.fabin>");
            } else {
                string nombre_archivo = input.substr(input.find(' ') + 1);
                if (nombre_archivo.substr(nombre_archivo.find_last_of('.') + 1) != "fabin") {
                    LOG_ERROR("Decodificar", "El archivo debe tener la extensión .fabin");
                } else {
                    Decodificar(nombre_archivo);
                }
            }
        } else if (input.rfind("listar_secuencias", 0) == 0) {
            if (numParams(input) != 0) {
                LOG_ERROR("ListarSecuencias", "El comando 'listar_secuencias' no requiere parámetros. Uso: listar_secuencias");
            } else {
                genoma.ListarSecuencias();
            }
        } else if (input.rfind("histograma", 0) == 0) {
            if (numParams(input) != 1) {
                LOG_ERROR("Histograma", "El comando 'histograma' requiere 1 parámetro. Uso: histograma <descripcion_secuencia>");
            } else {
                string descripcion = input.substr(input.find(' ') + 1);
                genoma.Histograma(descripcion.c_str());
            }
        } else if (input.rfind("es_subsecuencia", 0) == 0) {
            if (numParams(input) != 1) {
                LOG_ERROR("EsSubsecuencia", "El comando 'es_subsecuencia' requiere 1 parámetro. Uso: es_subsecuencia <subsecuencia>");
            } else {
                string subsecuencia = input.substr(input.find(' ') + 1);
                genoma.EsSubsecuencia(subsecuencia.c_str());
            }
        } else if (input.rfind("enmascarar", 0) == 0) {
            if (numParams(input) != 1) {
                LOG_ERROR("Enmascarar", "El comando 'enmascarar' requiere 1 parámetro. Uso: enmascarar <subsecuencia>");
            } else {
                string subsecuencia = input.substr(input.find(' ') + 1);
                genoma.Enmascarar(subsecuencia.c_str());
            }
        }
        // Comando de ruta_mas_corta
        else if (input.rfind("ruta_mas_corta", 0) == 0) {
            if (numParams(input) != 5) {
                LOG_ERROR("RutaMasCorta", "El comando 'ruta_mas_corta' requiere 5 parámetros. Uso: ruta_mas_corta <descripcion_secuencia> <i> <j> <x> <y>");
            } else {
                istringstream iss(input);
                string cmd, descripcion;
                string si, sj, sx, sy;
                iss >> cmd >> descripcion >> si >> sj >> sx >> sy;
                int i, j, x, y;
                if (!parsePositiveInt(si, i) || !parsePositiveInt(sj, j) || !parsePositiveInt(sx, x) || !parsePositiveInt(sy, y)) {
                    LOG_ERROR("RutaMasCorta", "Los parámetros i, j, x, y deben ser enteros positivos (por ejemplo: 1 2 3 4).");
                } else {
                    genoma.RutaMasCorta(descripcion.c_str(), i, j, x, y);
                }
            }
        }
        // Comando de base_remota
        else if (input.rfind("base_remota", 0) == 0) {
            if (numParams(input) != 3) {
                LOG_ERROR("BaseRemota", "El comando 'base_remota' requiere 3 parámetros. Uso: base_remota <descripcion_secuencia> <i> <j>");
            } else {
                istringstream iss(input);
                string cmd, descripcion;
                string si, sj;
                iss >> cmd >> descripcion >> si >> sj;
                int i, j;
                if (!parsePositiveInt(si, i) || !parsePositiveInt(sj, j)) {
                    LOG_ERROR("BaseRemota", "Los parámetros i y j deben ser enteros positivos (por ejemplo: 1 2).");
                } else {
                    genoma.BaseRemota(descripcion.c_str(), i, j);
                }
            }
        }
        // Caso por defecto
        else {
            LOG_ERROR("Sistema", string("Comando no reconocido: '") + input + "'");
        }
    }
    return 0;
}
