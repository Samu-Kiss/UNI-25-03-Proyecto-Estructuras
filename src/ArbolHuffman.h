#ifndef __ARBOLHUFFMAN_H__
#define __ARBOLHUFFMAN_H__

#include <string>
#include <vector>

#include "NodoHuffman.h"


class ArbolHuffman {
 private:
  NodoHuffman* raiz;

  // Vectores para almacenar códigos
  std::vector<char> caracteres;
  std::vector<std::string> codigos;

  // Métodos privados de ayuda
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
  NodoHuffman* obtenerRaiz();
};

#endif  // __ARBOLHUFFMAN_H__