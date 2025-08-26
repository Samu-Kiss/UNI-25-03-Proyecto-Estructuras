// secuencia.h
#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <string>
#include <vector>

using namespace std;
class Secuencia {
public:
    string nombre;
    vector<vector<string>> bases;
    int ancho_linea;
};

#endif // SECUENCIA_H
