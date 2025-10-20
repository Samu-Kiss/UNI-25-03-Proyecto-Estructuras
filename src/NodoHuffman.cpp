#include "NodoHuffman.h"
#include <cstddef> // Para NULL

NodoHuffman::NodoHuffman(char dato, int frecuencia) {
    this->dato = dato;
    this->frecuencia = frecuencia;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

NodoHuffman::NodoHuffman(NodoHuffman* izq, NodoHuffman* der) {
    this->dato = '\0'; // Caracter nulo para nodos internos
    this->frecuencia = izq->frecuencia + der->frecuencia;
    this->hijoIzq = izq;
    this->hijoDer = der;
}

NodoHuffman::~NodoHuffman() {
    // El destructor del arbol se encargara de la eliminacion recursiva.
}

bool NodoHuffman::esHoja() {
    return this->hijoIzq == NULL && this->hijoDer == NULL;
}