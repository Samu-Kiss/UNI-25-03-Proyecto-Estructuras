#include "sistema.h"
#include "log.hpp"
#include "termcolor.hpp" // Librería para colores en la consola
#include <iostream>
#include <string>
#include <climits>
#include <fstream>
#include <sstream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

//constructor
Sistema::Sistema() {}

// Metodos privados

// Funcion para inicializar la consola
void Sistema::inicializar() {
#ifdef _WIN32
    // Cambiar la codificación de entrada y salida estándar a UTF-8
    // Fuente: https://stackoverflow.com/questions/10882277/properly-print-utf8-characters-in-windows-console
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

// Función para mostrar un mensaje de bienvenida
void Sistema::bienvenida() {
    cout << termcolor::green;
    cout << "===============================================" << endl;
    cout << "           >>> Consola Iniciada <<<           " << endl;
    cout << "===============================================" << endl;
    cout << termcolor::reset << endl;

    cout << "Escribe 'exit', 'quit' o 'salir' para terminar." << endl;
    cout << "Si necesitas ayuda, escribe 'help' o 'ayuda'." << endl << endl;
}

// Función para salir del programa
void Sistema::salir() {
    LOG_EXITO("Sistema", "Saliendo del programa...");
    exit(0);
}

// Función para limpiar la pantalla
void Sistema::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Función para guardar un archivo
void Sistema::guardar(const string &nombre_archivo) {
    // Posibles estados:
    // No hay secuencias cargadas
    // Archivo guardado exitosamente
    // Error al guardar el archivo
    if (genoma.get_secuencias().empty()) {
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
    for (const Secuencia& secuencia : genoma.get_secuencias()) {
        archivo << ">" << secuencia.get_descripcion() << endl;

        const vector<char> &bases = secuencia.get_bases();
        for (size_t i = 0; i < bases.size(); ++i) {
            if (i % secuencia.get_ancho_linea() == 0 && i != 0) archivo << endl;
            archivo << bases[i];
        }

        archivo << endl;
    }

    archivo.close();
    LOG_EXITO("Guardar", "Archivo guardado exitosamente.");
}

// Función para cargar un archivo
bool Sistema::cargar(const string &nombre_archivo) {
    genoma.clear_secuencias();
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
            if (!nueva_secuencia.get_descripcion().empty() || !nueva_secuencia.get_bases().empty()) {
                if (nueva_secuencia.get_descripcion().empty() && !nueva_secuencia.get_bases().empty()) {
                    LOG_ADVERTENCIA("Cargar", string("Se encontró una secuencia sin descripción en el archivo ") + nombre_archivo + ". Se descarta la secuencia.");
                } else if (!nueva_secuencia.get_descripcion().empty() && nueva_secuencia.get_bases().empty()) {
                    LOG_ADVERTENCIA("Cargar", string("La secuencia '") + nueva_secuencia.get_descripcion() + "' no contiene bases. Se descarta la secuencia.");
                } else {
                    genoma.add_secuencia(nueva_secuencia);
                    ++countAdded;
                    LOG_EXITO("Cargar", string("Secuencia añadida: ") + nueva_secuencia.get_descripcion());
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
            if (!nueva_secuencia.get_descripcion().empty() || !nueva_secuencia.get_bases().empty()) {
                if (nueva_secuencia.get_descripcion().empty() && !nueva_secuencia.get_bases().empty()) {
                    LOG_ADVERTENCIA("Cargar", string("Se encontró una secuencia sin descripción en el archivo ") + nombre_archivo + ". Se descarta la secuencia.");
                } else if (!nueva_secuencia.get_descripcion().empty() && nueva_secuencia.get_bases().empty()) {
                    LOG_ADVERTENCIA("Cargar", string("La secuencia '") + nueva_secuencia.get_descripcion() + "' no contiene bases. Se descarta la secuencia.");
                } else {
                    genoma.add_secuencia(nueva_secuencia);
                    ++countAdded;
                    LOG_EXITO("Cargar", string("Secuencia añadida: ") + nueva_secuencia.get_descripcion());
                }
            }
            nueva_secuencia = Secuencia();
            nueva_secuencia.set_descripcion(linea.substr(1));
            firstLine = true;
        } else {
            if (firstLine) {
                nueva_secuencia.set_ancho_linea(static_cast<int>(linea.length()));
                firstLine = false;
            }
            for (char base: linea) {
                nueva_secuencia.add_base(base);
            }
        }
    }

    // Agregar la última secuencia si existe y es válida
    if (!nueva_secuencia.get_descripcion().empty() || !nueva_secuencia.get_bases().empty()) {
        if (nueva_secuencia.get_descripcion().empty() && !nueva_secuencia.get_bases().empty()) {
            LOG_ADVERTENCIA("Cargar", string("Se encontró una secuencia sin descripción en el archivo ") + nombre_archivo + ". Se descarta la secuencia.");
        } else if (!nueva_secuencia.get_descripcion().empty() && nueva_secuencia.get_bases().empty()) {
            LOG_ADVERTENCIA("Cargar", string("La secuencia '") + nueva_secuencia.get_descripcion() + "' no contiene bases. Se descarta la secuencia.");
        } else {
            genoma.add_secuencia(nueva_secuencia);
            ++countAdded;
            LOG_EXITO("Cargar", string("Secuencia añadida: ") + nueva_secuencia.get_descripcion());
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

// Funacion para calcular precuencias
void Sistema::calcularFrecuencias(const std::string &texto, long long (&frecuencias_array)[256], short &num_caracteres_unicos) {
    for(int i = 0; i < 256; ++i) {
        frecuencias_array[i] = 0;
    }

    for (size_t i = 0; i < texto.length(); ++i) {
        char c = texto[i];
        frecuencias_array[static_cast<unsigned char>(c)]++;
    }

    num_caracteres_unicos = 0;
    for(int i = 0; i < 256; ++i) {
        if(frecuencias_array[i] > 0) {
            num_caracteres_unicos++;
        }
    }
}

// Función para codificar un archivo
void Sistema::codificar(const string &nombre_archivo) {
    //TODO: Implementación de la codificación
    //ESTO SE HACE EN LA SEGUNDA ENTREGA
	
	if (genoma.get_secuencias().empty()) {
        LOG_ADVERTENCIA("Codificar", "No hay secuencias cargadas para codificar.");
        return;
    }

    string texto_completo = "";
    for (const Secuencia& sec : genoma.get_secuencias()) {
        for (char base : sec.get_bases()) {
            texto_completo += base;
        }
    }

    if (texto_completo.empty()) {
        LOG_ADVERTENCIA("Codificar", "Las secuencias cargadas no contienen bases.");
        return;
    }

    long long frecuencias_array[256];
    short num_bases_diferentes;
    calcularFrecuencias(texto_completo, frecuencias_array, num_bases_diferentes);

    ArbolHuffman arbol(texto_completo);

    ofstream archivo_salida(nombre_archivo, ios::binary);
    if (!archivo_salida.is_open()) {
        LOG_ERROR("Codificar", "No se pudo crear el archivo " + nombre_archivo);
        return;
    }

    archivo_salida.write(reinterpret_cast<const char*>(&num_bases_diferentes), sizeof(short));

    for (int i = 0; i < 256; ++i) {
        if (frecuencias_array[i] > 0) {
            char caracter = static_cast<char>(i);
            long long frecuencia = frecuencias_array[i];
            archivo_salida.write(&caracter, sizeof(char));
            archivo_salida.write(reinterpret_cast<const char*>(&frecuencia), sizeof(long long));
        }
    }

    int num_secuencias = genoma.get_secuencias().size();
    archivo_salida.write(reinterpret_cast<const char*>(&num_secuencias), sizeof(int));

    string codigo_binario_total = "";
    for (const Secuencia& sec : genoma.get_secuencias()) {
        short tam_desc = sec.get_descripcion().length();
        archivo_salida.write(reinterpret_cast<const char*>(&tam_desc), sizeof(short));
        archivo_salida.write(sec.get_descripcion().c_str(), tam_desc);
        
        long long longitud_sec = sec.get_bases().size();
        short ancho_linea = sec.get_ancho_linea();
        archivo_salida.write(reinterpret_cast<const char*>(&longitud_sec), sizeof(long long));
        archivo_salida.write(reinterpret_cast<const char*>(&ancho_linea), sizeof(short));

        string bases_secuencia(sec.get_bases().begin(), sec.get_bases().end());
        codigo_binario_total += arbol.codificar(bases_secuencia);
    }

    unsigned char byte = 0;
    int bit_count = 0;
    for (size_t i = 0; i < codigo_binario_total.length(); ++i) {
        char bit = codigo_binario_total[i];
        byte <<= 1;
        if (bit == '1') byte |= 1;
        bit_count++;
        if (bit_count == 8) {
            archivo_salida.write(reinterpret_cast<const char*>(&byte), 1);
            byte = 0;
            bit_count = 0;
        }
    }
    if (bit_count > 0) {
        byte <<= (8 - bit_count);
        archivo_salida.write(reinterpret_cast<const char*>(&byte), 1);
    }

    archivo_salida.close();
    LOG_EXITO("Codificar", "Secuencias codificadas y guardadas en " + nombre_archivo);
	
}

// Función para decodificar un archivo
void Sistema::decodificar(const string &nombre_archivo) {
    //TODO: Implementación de la decodificación
    //ESTO SE HACE EN LA SEGUNDA ENTREGA
	
	ifstream archivo_entrada(nombre_archivo, ios::binary);
    if (!archivo_entrada.is_open()) {
        LOG_ERROR("Decodificar", "No se puede abrir el archivo " + nombre_archivo);
        return;
    }

    genoma.clear_secuencias();

    short num_bases_diferentes;
    archivo_entrada.read(reinterpret_cast<char*>(&num_bases_diferentes), sizeof(short));
    if (archivo_entrada.gcount() != sizeof(short)) {
        LOG_ERROR("Decodificar", "Archivo corrupto o formato invalido.");
        return;
    }

    string texto_reconstruido = "";
    for (short i = 0; i < num_bases_diferentes; ++i) {
        char caracter;
        long long frecuencia;
        archivo_entrada.read(&caracter, sizeof(char));
        archivo_entrada.read(reinterpret_cast<char*>(&frecuencia), sizeof(long long));
        for(long long j = 0; j < frecuencia; ++j) texto_reconstruido += caracter;
    }

    if (texto_reconstruido.empty()) {
        LOG_EXITO("Decodificar", "El archivo no contenia secuencias de bases, cargado correctamente.");
        archivo_entrada.close();
        return;
    }
    ArbolHuffman arbol(texto_reconstruido);

    int num_secuencias;
    archivo_entrada.read(reinterpret_cast<char*>(&num_secuencias), sizeof(int));
    vector<Secuencia> secuencias_temporales;
    vector<long long> longitudes;

    for (int i = 0; i < num_secuencias; ++i) {
        Secuencia sec_temp;
        short tam_desc;
        archivo_entrada.read(reinterpret_cast<char*>(&tam_desc), sizeof(short));
        string desc(tam_desc, '\0');
        archivo_entrada.read(&desc[0], tam_desc);
        sec_temp.set_descripcion(desc);

        long long longitud_sec;
        short ancho_linea;
        archivo_entrada.read(reinterpret_cast<char*>(&longitud_sec), sizeof(long long));
        archivo_entrada.read(reinterpret_cast<char*>(&ancho_linea), sizeof(short));
        sec_temp.set_ancho_linea(ancho_linea);
        
        secuencias_temporales.push_back(sec_temp);
        longitudes.push_back(longitud_sec);
    }

    string bits_str = "";
    char byte;
    while(archivo_entrada.read(&byte, 1)) {
        for(int i = 7; i >= 0; --i) {
            bits_str += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    
    string bases_decodificadas = arbol.decodificar(bits_str);

    size_t offset = 0;
    for (size_t i = 0; i < secuencias_temporales.size(); ++i) {
        string bases_para_sec = bases_decodificadas.substr(offset, longitudes[i]);
        vector<char> bases_vec(bases_para_sec.begin(), bases_para_sec.end());
        secuencias_temporales[i].set_bases(bases_vec);
        genoma.add_secuencia(secuencias_temporales[i]);
        offset += longitudes[i];
    }

    archivo_entrada.close();
    LOG_EXITO("Decodificar", "Secuencias decodificadas desde " + nombre_archivo + " y cargadas en memoria.");
	
}

// Devuelve cuántos parámetros reales hay después del comando.
// Ej: "cargar archivo" -> 1
int Sistema::numParams(const string &input) {
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
bool Sistema::parsePositiveInt(const string &s, int &out) {
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

// Ayuda() -> void
void Sistema::ayuda(const string &param) {
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
        cout << "El comando debe generar el archivo binario con la correspondiente codificación de Huffman en el formato descrito más arriba, almacenándolo en disco bajo el nombre nombre_archivo.fabin . Si no hay secuencias cargadas en memoria, o si el archivo no puede escribirse correctamente, el comando debe mostrar el mensaje correspondiente." << endl;
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

// --- Bucle principal de la consola ---

void Sistema::procesarComandos() {
    string input;
    while (true) {
        cout << "\n" << termcolor::yellow << "$ " << termcolor::reset;

        getline(cin, input);

        // Comando de salida
        if (input.rfind("exit", 0) == 0 || input.rfind("quit", 0) == 0 || input.rfind("salir", 0) == 0) {
            if (numParams(input) != 0) {
                LOG_ERROR("Salir", "El comando 'salir' no requiere parámetros.");
            } else {
                salir();
            }
        }
        // Comando de clear
        else if (input.rfind("clear", 0) == 0) {
            if (numParams(input) != 0) {
                LOG_ERROR("Clear", "El comando 'clear' no requiere parámetros.");
            } else {
                limpiarPantalla();
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
            ayuda(param);
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
                    cargar(nombre_archivo);
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
                    guardar(nombre_archivo);
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
                    codificar(nombre_archivo);
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
                    decodificar(nombre_archivo);
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
}

//Metodo Publico para Iniciar
void Sistema::iniciarConsola() {
    inicializar();
    bienvenida();
    procesarComandos();

}

