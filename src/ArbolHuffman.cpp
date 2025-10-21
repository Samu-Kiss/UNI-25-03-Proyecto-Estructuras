#include "ArbolHuffman.h"
#include <iostream>
#include <vector>
#include <string>

// --- Metodos Privados

// Recorre el arbol para generar y almacenar los codigos de cada caracter
void ArbolHuffman::generarCodigosRecursivo(NodoHuffman* nodo, std::string codigoActual) {
    if (nodo == NULL) {
        return;
    }

    // Si es hoja, se ha encontrado un caracter y se guarda el codigo.
    if (nodo->esHoja()) {
        this->caracteres.push_back(nodo->dato);
        this->codigos.push_back(codigoActual);
    } else {
        // Si no es hoja, se sigue recorriendo. 0 para izquierda, 1 para derecha.
        generarCodigosRecursivo(nodo->hijoIzq, codigoActual + "0");
        generarCodigosRecursivo(nodo->hijoDer, codigoActual + "1");
    }
}

// Elimina el arbol de forma recursiva
void ArbolHuffman::destruirRecursivo(NodoHuffman* nodo) {
    if (nodo != NULL) {
        destruirRecursivo(nodo->hijoIzq);
        destruirRecursivo(nodo->hijoDer);
        delete nodo;
    }
}

// Busca y devuelve el codigo de un caracter especifico (busqueda lineal)
std::string ArbolHuffman::obtenerCodigo(char c) {
    for (size_t i = 0; i < this->caracteres.size(); ++i) {
        if (this->caracteres[i] == c) {
            return this->codigos[i];
        }
    }
    return "";
}


// --- Metodos Publicos

ArbolHuffman::ArbolHuffman(std::string texto) {
    this->raiz = NULL;

    // Calcular frecuencias
    // arreglo de 256 para todos los caracteres ASCII posibles
    int frecuencias[256] = {0};
    for (size_t i = 0; i < texto.length(); ++i) {
        frecuencias[static_cast<unsigned char>(texto[i])]++;
    }

    // 2. Crear una lista de nodos hoja
    std::vector<NodoHuffman*> nodos;
    for (int i = 0; i < 256; ++i) {
        if (frecuencias[i] > 0) {
            NodoHuffman* nuevoNodo = new NodoHuffman(static_cast<char>(i), frecuencias[i]);
            nodos.push_back(nuevoNodo);
        }
    }

    // 3. Construir arbol (Algoritmo de Huffman)
    // se repite hasta que solo quede un nodo en la lista (raiz)
    while (nodos.size() > 1) {
        // Encontrar y extraer los dos nodos con menor frecuencia
        
        // Encontrar el primer minimo
        int minIndex1 = 0;
        for (size_t i = 1; i < nodos.size(); ++i) {
            if (nodos[i]->frecuencia < nodos[minIndex1]->frecuencia) {
                minIndex1 = i;
            }
        }
        NodoHuffman* minNodo1 = nodos[minIndex1];
        nodos.erase(nodos.begin() + minIndex1);

        // Encontrar el segundo minimo
        int minIndex2 = 0;
        for (size_t i = 1; i < nodos.size(); ++i) {
            if (nodos[i]->frecuencia < nodos[minIndex2]->frecuencia) {
                minIndex2 = i;
            }
        }
        NodoHuffman* minNodo2 = nodos[minIndex2];
        nodos.erase(nodos.begin() + minIndex2);

        // Crear un nuevo nodo interno y agregarlo a la lista
        NodoHuffman* nodoPadre = new NodoHuffman(minNodo1, minNodo2);
        nodos.push_back(nodoPadre);
    }

    // 4. Asignar raiz y generar los codigos
    if (!nodos.empty()) {
        this->raiz = nodos[0];
        generarCodigosRecursivo(this->raiz, "");
    }
}

ArbolHuffman::~ArbolHuffman() {
    destruirRecursivo(this->raiz);
}

void ArbolHuffman::imprimirCodigos() {
    std::cout << "--- Codigos de Huffman ---" << std::endl;
    for (size_t i = 0; i < this->caracteres.size(); ++i) {
        std::cout << "'" << this->caracteres[i] << "' : " << this->codigos[i] << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
}

std::string ArbolHuffman::codificar(std::string texto) {
    std::string textoCodificado = "";
    for (size_t i = 0; i < texto.length(); ++i) {
        textoCodificado += obtenerCodigo(texto[i]);
    }
    return textoCodificado;
}

std::string ArbolHuffman::decodificar(std::string textoCodificado) {
    std::string textoDecodificado = "";
    if (this->raiz == NULL) {
        return textoDecodificado;
    }

    NodoHuffman* nodoActual = this->raiz;
    for (size_t i = 0; i < textoCodificado.length(); ++i) {
        if (textoCodificado[i] == '0') {
            nodoActual = nodoActual->hijoIzq;
        } else { // '1'
            nodoActual = nodoActual->hijoDer;
        }

        // Si llega a una hoja, carácter encontrado
        if (nodoActual->esHoja()) {
            textoDecodificado += nodoActual->dato;
            nodoActual = this->raiz; // Volvemos a la raiz para el siguiente caracter
        }
    }
    return textoDecodificado;
}