#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <vector>

template <class T, class U>
class Grafo {
 private:
  std::vector<T> vertices;
  U** aristas;

 public:
  // Constructor y destructor
  Grafo();
  ~Grafo();

  // Setters / getters
  void setVertices(const std::vector<T>& v);
  void setAristas(U** a);
  std::vector<T> getVertices() const;
  U** getAristas() const;

  // Operaciones básicas
  int cantVertices() const;
  int cantAristas() const;

  int buscarVertice(const T& vert) const;
  bool insertarVertice(const T& vert);
  bool insertarArista(const T& ori, const T& des, const U& cos);
  U buscarArista(const T& ori, const T& des) const;
  bool eliminarArista(const T& ori, const T& des);
};

#endif  // __GRAFO_H__
