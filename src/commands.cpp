#include <iostream>
#include "../include/commands.h"
#include "../external/termcolor.hpp"

using namespace std;

void comandoSalida() {
    cout << termcolor::red << "Terminando Programa" << termcolor::reset << endl;
    exit(0);
}

void comandoAyuda() {
    cout << termcolor::blue << "Comandos disponibles:" << termcolor::reset << endl;
    cout << "  help, ayuda               - Mostrar esta ayuda" << endl;
    cout << "  exit, quit, salir         - Salir de la consola" << endl;
    cout << "  cargar <nombre_archivo>   - Cargar secuencias desde un archivo" << endl;
    cout << "  listar_secuencias         - Listar todas las secuencias en memoria" << endl;
    cout << "  histograma <descripcion>  - Mostrar histograma de una secuencia" << endl;
    cout << "  es_subsecuencia <subsec>  - Verificar si existe una subsecuencia" << endl;
    cout << "  enmascarar <subsecuencia> - Enmascarar una subsecuencia" << endl;
    cout << "  guardar <nombre_archivo>  - Guardar secuencias en un archivo" << endl;
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
