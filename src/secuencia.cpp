#include "../include/secuencia.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Una secuencia tiene un nombre, bases (conjunto de cadenas), ancho linea (numero)
class Secuencia {
public:
    string nombre;
    vector<vector<string>> bases;
    int ancho_linea;
};