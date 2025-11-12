#include "grafo.h"

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
  int cantVertices() { return vertices.size(); }
  int cantAristas() {
    int suma = 0;
    for (int i = 0; i < cantVertices(); i++) {
      for (int j = 0; j < cantVertices(); j++) {
        if (*(*(aristas + i) + j) != 0) suma++;
      }
    }
    return suma;
  }
  int buscarVertice(T vert) {
    int ind = -1;
    for (int i = 0; i < cantVertices(); i++) {
      if (vertices[i] == vert) ind = i;
    }
    return ind;
  }
  bool insertarVertice(T vert) {
    bool res = false;
    if (buscarVertice(vert) == -1) {
      vertices.push_back(vert);
      U** nmatriz = new* U[cantVertices()];
      for (int i = 0; i < cantVertices(); i++) {
        *(nmatriz + i) = new U[cantVertices()];
      }
      for (int i = 0; i < cantVertices() - 1; i++) {
        for (int j = 0; j < cantVertices() - 1; j++) {
          *(*(nmatriz + i) + j) = *(*(aristas + i) + j);
        }
      }
      for (int i = 0; i < cantVertices(); i++) {
        *(*(nmatriz + i) + (cantVertices() - 1)) = 0;
        *(*(nmatriz + (cantVertices() - 1)) + j) = 0;
      }
      for (int i = 0; i < cantVertices() - 1; i++) {
        delete[] *(aristas + i);
      }
      delete[] aristas;
      aristas = nmatriz;
    }
    return res;
  }
  bool insertarArista(T ori, T des, U cos) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if (i_ori != -1 && i_des != -1) {
      if (*(*(aristas + i_ori) + i_des) == 0) {
        *(*(aristas + i_ori) + i_des) = cos;
        res = true;
      }
    }
    return res;
  }
  U buscarArista(T ori, T des) {
    U res = -1;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if (i_ori != -1 && i_des != -1) {
      res = *(*(aristas + i_ori) + i_des);
    }
    return res;
  }
  bool eliminarArista(T ori, T des) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if (i_ori != -1 && i_des != -1) {
      *(*(aristas + i_ori) + i_des) = 0;
      res = true;
    }
    return res;
  }
};