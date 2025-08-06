#include <iostream>
#include "../include/commands.h"
#include "../external/termcolor.hpp"

using namespace std;

void comandoSalida() {
    cout << termcolor::red << "Terminando Programa" << termcolor::reset << endl;
    exit(0);
}

void comandoAyuda(const string& param) {
    if (param.empty()) {
        cout << termcolor::blue << "Comandos disponibles:" << termcolor::reset << endl;
        cout << "  help, ayuda [comando]           - Mostrar esta ayuda o ayuda de un comando" << endl;
        cout << "  exit, quit, salir               - Salir de la consola" << endl;
        cout << "  cargar <nombre_archivo>         - Cargar secuencias desde un archivo" << endl;
        cout << "  listar_secuencias               - Listar todas las secuencias en memoria" << endl;
        cout << "  histograma <descripcion>        - Mostrar histograma de una secuencia" << endl;
        cout << "  es_subsecuencia <subsec>        - Verificar si existe una subsecuencia" << endl;
        cout << "  enmascarar <subsecuencia>       - Enmascarar una subsecuencia" << endl;
        cout << "  guardar <nombre_archivo>        - Guardar secuencias en un archivo" << endl;
        cout << "  codificar <secuencia>           - Codificar una secuencia" << endl;
        cout << "  decodificar <secuencia>         - Decodificar una secuencia" << endl;
        cout << "  ruta_mas_corta <a> <b> <c> <d> <y> - Buscar ruta más corta" << endl;
        cout << "  base_remota <a> <b> <j>         - Buscar base remota" << endl;
        return;
    }

    if (param == "cargar") {
        cout << termcolor::blue << "cargar <nombre_archivo>" << termcolor::reset << endl;
        cout << "Carga secuencias desde un archivo." << endl;
    } else if (param == "listar_secuencias") {
        cout << termcolor::blue << "listar_secuencias" << termcolor::reset << endl;
        cout << "Lista todas las secuencias en memoria." << endl;
    } else if (param == "histograma") {
        cout << termcolor::blue << "histograma <descripcion>" << termcolor::reset << endl;
        cout << "Muestra el histograma de una secuencia." << endl;
    } else if (param == "es_subsecuencia") {
        cout << termcolor::blue << "es_subsecuencia <subsec>" << termcolor::reset << endl;
        cout << "Verifica si existe una subsecuencia." << endl;
    } else if (param == "enmascarar") {
        cout << termcolor::blue << "enmascarar <subsecuencia>" << termcolor::reset << endl;
        cout << "Enmascara una subsecuencia." << endl;
    } else if (param == "guardar") {
        cout << termcolor::blue << "guardar <nombre_archivo>" << termcolor::reset << endl;
        cout << "Guarda las secuencias en un archivo." << endl;
    } else if (param == "codificar") {
        cout << termcolor::blue << "codificar <secuencia>" << termcolor::reset << endl;
        cout << "Codifica una secuencia." << endl;
    } else if (param == "decodificar") {
        cout << termcolor::blue << "decodificar <secuencia>" << termcolor::reset << endl;
        cout << "Decodifica una secuencia." << endl;
    } else if (param == "ruta_mas_corta") {
        cout << termcolor::blue << "ruta_mas_corta <a> <b> <c> <d> <y>" << termcolor::reset << endl;
        cout << "Busca la ruta más corta entre nodos." << endl;
    } else if (param == "base_remota") {
        cout << termcolor::blue << "base_remota <a> <b> <j>" << termcolor::reset << endl;
        cout << "Busca la base remota entre nodos." << endl;
    } else if (param == "help" || param == "ayuda") {
        cout << termcolor::blue << "help, ayuda [comando]" << termcolor::reset << endl;
        cout << "Muestra la ayuda general o de un comando específico." << endl;
    } else if (param == "exit" || param == "quit" || param == "salir") {
        cout << termcolor::blue << "exit, quit, salir" << termcolor::reset << endl;
        cout << "Termina el programa." << endl;
    } else {
        cout << termcolor::red << "No existe ayuda para el comando: " << param << termcolor::reset << endl;
    }
}

bool valCargar(string command) {
    int espacio = command.find(' ');
    if (espacio == -1) {
        return false;
    }

    string cmd   = command.substr(0, espacio);
    string param = command.substr(espacio + 1);

    if (cmd != "cargar") {
        return false;
    }

    if (param.empty() || param.find(' ') != -1) {
        return false;
    }

    return true;
}

bool valListar(string command) {
    if (command == "listar_secuencias") {
        return true;
    }

    return false;
}

bool valHistograma(string command) {
    int espacio = command.find(' ');
    if (espacio == -1) {
        return false;
    }

    string cmd   = command.substr(0, espacio);
    string param = command.substr(espacio + 1);

    if (cmd != "histograma") {
        return false;
    }

    if (param.empty() || param.find(' ') != -1) {
        return false;
    }

    return true;
}

bool valEsSubsecuencia(string command) {
    int espacio = command.find(' ');
    if (espacio == -1) {
        return false;
    }

    string cmd   = command.substr(0, espacio);
    string param = command.substr(espacio + 1);

    if (cmd != "es_subsecuencia") {
        return false;
    }

    if (param.empty() || param.find(' ') != -1) {
        return false;
    }

    return true;
}

bool valEnmascarar(string command) {
    int espacio = command.find(' ');
    if (espacio == -1) {
        return false;
    }

    string cmd   = command.substr(0, espacio);
    string param = command.substr(espacio + 1);

    if (cmd != "enmascarar") {
        return false;
    }

    if (param.empty() || param.find(' ') != -1) {
        return false;
    }

    return true;
}

bool valGuardar(string command) {
    int espacio = command.find(' ');
    if (espacio == -1) {
        return false;
    }

    string cmd   = command.substr(0, espacio);
    string param = command.substr(espacio + 1);

    if (cmd != "guardar") {
        return false;
    }

    if (param.empty() || param.find(' ') != -1) {
        return false;
    }

    return true;
}

bool valCodificar(string command) {
    int espacio = command.find(' ');
    if (espacio == -1) {
        return false;
    }

    string cmd   = command.substr(0, espacio);
    string param = command.substr(espacio + 1);

    if (cmd != "codificar") {
        return false;
    }

    if (param.empty() || param.find(' ') != -1) {
        return false;
    }

    return true;
}

bool valDecodificar(string command) {
    int espacio = command.find(' ');
    if (espacio == -1) {
        return false;
    }

    string cmd   = command.substr(0, espacio);
    string param = command.substr(espacio + 1);

    if (cmd != "decodificar") {
        return false;
    }

    if (param.empty() || param.find(' ') != -1) {
        return false;
    }

    return true;
}

bool valRutaMasCorta(string command) {
    int e1 = command.find(' ');
    if (e1 == -1) {
        return false;
    }

    string cmd = command.substr(0, e1);
    if (cmd != "ruta_mas_corta") {
        return false;
    }

    int e2 = command.find(' ', e1 + 1);
    if (e2 == -1) {
        return false;
    }

    int e3 = command.find(' ', e2 + 1);
    if (e3 == -1) {
        return false;
    }

    int e4 = command.find(' ', e3 + 1);
    if (e4 == -1) {
        return false;
    }

    int e5 = command.find(' ', e4 + 1);
    if (e5 == -1) {
        return false;
    }

    string y = command.substr(e5 + 1);
    if (y.empty() || y.find(' ') != -1) {
        return false;
    }

    return true;
}

bool valBaseRemota(string command) {
    int e1 = command.find(' ');
    if (e1 == -1) {
        return false;
    }

    string cmd = command.substr(0, e1);
    if (cmd != "base_remota") {
        return false;
    }

    int e2 = command.find(' ', e1 + 1);
    if (e2 == -1) {
        return false;
    }

    int e3 = command.find(' ', e2 + 1);
    if (e3 == -1) {
        return false;
    }

    string j = command.substr(e3 + 1);
    if (j.empty() || j.find(' ') != -1) {
        return false;
    }

    return true;
}
