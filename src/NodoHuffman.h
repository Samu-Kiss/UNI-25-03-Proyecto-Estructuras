#ifndef __NODOHUFFMAN_H__
#define __NODOHUFFMAN_H__

// Almacena caracter, frecuencia, y punteros a hijos.
class NodoHuffman {
 public:
  char dato;
  int frecuencia;
  NodoHuffman* hijoIzq;
  NodoHuffman* hijoDer;

  // Constructor nodos hoja (caracter)
  NodoHuffman(char dato, int frecuencia);

  // Constructor nodos internos (no contienen caracter)
  NodoHuffman(NodoHuffman* izq, NodoHuffman* der);

  // destructor
  ~NodoHuffman();

  // saber si el nodo es una hoja o un nodo interno.
  bool esHoja();
};

#endif  // __NODOHUFFMAN_H__