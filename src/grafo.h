//grafo.h

#ifndef GRAFO_H
#define GRAFO_H

#include <vector>

template <class T, class U>
class Grafo {
 private:
  std::vector<T> vertices;
  U** aristas;

 public:
  Grafo();
  void setVertices(std::vector<T> v);
  void setAristas(U** a);
  std::vector<T> getVertices();
  U** getAristas();
  int cantVertices();
  int cantAristas();
  int buscarVertice(T vert);
  bool insertarVertice(T vert);
  bool insertarArista(T ori, T des);
  U buscarArista(T ori, T des);
  bool eliminarArista(T ori, T des);
  void imprimirGrafo();
  U calcularCosto(T ori, T des);
  void dijkstra(T origen, T destino, std::vector<T>& ruta, U& costo);
};

extern template class Grafo<char, float>;

#endif  // GRAFO_H