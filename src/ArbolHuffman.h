#ifndef __ARBOLHUFFMAN_H__
#define __ARBOLHUFFMAN_H__

#include "NodoHuffman.h"
#include <string>
#include <vector>

class ArbolHuffman {
private:
    NodoHuffman* raiz;

    // Vectore para almacenar codigos
    std::vector<char> caracteres;
    std::vector<std::string> codigos;

    // Metodos privados de ayuda
    void generarCodigosRecursivo(NodoHuffman* nodo, std::string codigoActual);
    void destruirRecursivo(NodoHuffman* nodo);
    std::string obtenerCodigo(char c);

public:
    // El constructor recibe texto y construye todo el arbol
    ArbolHuffman(std::string texto);

    // El destructor libera toda la memoria del arbol
    ~ArbolHuffman();

    // Funciones publicas
    void imprimirCodigos();
    std::string codificar(std::string texto);
    std::string decodificar(std::string textoCodificado);
};

#endif // __ARBOLHUFFMAN_H__