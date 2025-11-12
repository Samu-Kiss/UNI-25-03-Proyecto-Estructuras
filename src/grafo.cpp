#include "grafo.h"

#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>

  template <class T, class U>
  Grafo<T,U>::Grafo(){}

  template <class T, class U>
  void Grafo<T,U>::setVertices(std::vector<T> v){
    vertices = v;
    return;
  }

  template <class T, class U>
  void Grafo<T,U>::setAristas(U** a){
    return;
  }

  template <class T, class U>
  std::vector<T> Grafo<T,U>::getVertices(){
    return vertices;
  }

  template <class T, class U>
  U** Grafo<T,U>::getAristas(){
    return aristas;
  }

  template <class T, class U>
  int Grafo<T,U>::cantVertices() { return vertices.size(); }

  template <class T, class U>
  int Grafo<T,U>::cantAristas() {
    int suma = 0;
    for (int i = 0; i < cantVertices(); i++) {
      for (int j = 0; j < cantVertices(); j++) {
        if (*(*(aristas + i) + j) != 0) suma++;
      }
    }
    return suma;
  }
  
  template <class T, class U>
  int Grafo<T,U>::buscarVertice(T vert) {
    int ind = -1;
    for (int i = 0; i < cantVertices(); i++) {
      if (vertices[i] == vert) ind = i;
    }
    return ind;
  }
  
  template <class T, class U>
  bool Grafo<T,U>::insertarVertice(T vert) {
    bool res = false;
    if (buscarVertice(vert) == -1) {
      vertices.push_back(vert);
      U** nmatriz = new U*[cantVertices()];
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
        *(*(nmatriz + (cantVertices() - 1)) + i) = 0;
      }
      for (int i = 0; i < cantVertices() - 1; i++) {
        delete[] *(aristas + i);
      }
      delete[] aristas;
      aristas = nmatriz;
      res = true;
    }
    return res;
  }
  
  template <class T, class U>
  bool Grafo<T,U>::insertarArista(T ori, T des) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if (i_ori != -1 && i_des != -1) {
      if (*(*(aristas + i_ori) + i_des) == 0) {
        U cos = calcularCosto(ori, des);
        *(*(aristas + i_ori) + i_des) = cos;
        res = true;
      }
    }
    return res;
  }
  
  template <class T, class U>
  U Grafo<T,U>::buscarArista(T ori, T des) {
    U res = -1;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if (i_ori != -1 && i_des != -1) {
      res = *(*(aristas + i_ori) + i_des);
    }
    return res;
  }
  
  template <class T, class U>
  bool Grafo<T,U>::eliminarArista(T ori, T des) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if (i_ori != -1 && i_des != -1) {
      *(*(aristas + i_ori) + i_des) = 0;
      res = true;
    }
    return res;
  }
  
  //TODO: IMPRIMIR GRAFO (ASÍ SUPER LAMBON, QUE SE VEAN LAS CONEXIONES CON COLORES Y ESO)
  template <class T, class U>
  void Grafo<T,U>::imprimirGrafo(){
    int n = cantVertices();
    for (int i = 0; i < n; i++) {
      std::cout << vertices[i] << ": ";
      for (int j = 0; j < n; j++) {
        if (*(*(aristas + i) + j) != 0) {
          std::cout << vertices[j] << "(" << *(*(aristas + i) + j) << ") ";
        }
      }
      std::cout << std::endl;
    }
  }

  //TODO: CALCULAR COSTO
  template <class T, class U>
  U Grafo<T,U>::calcularCosto(T ori, T des){
    U costo = 0;
    int ascii_ori = static_cast<int>(ori);
    int ascii_des = static_cast<int>(des);

    costo = 1.0 / (1 + std::abs(ascii_ori - ascii_des));
    return costo;
  }

  //TODO: RUTA MAS CORTA (DIJKSTRA) (QUE SE IMPRIMA LA RUTA CON COLORES Y ASÍ)
  template <class T, class U>
  void Grafo<T,U>::dijkstra(T origen, T destino, std::vector<T>& ruta, U& costo){
    // Implementación del algoritmo de Dijkstra
    // Esta es una implementación básica y puede ser optimizada

    int n = cantVertices();
    std::vector<U> dist(n, std::numeric_limits<U>::max());
    std::vector<int> prev(n, -1);
    std::vector<bool> visited(n, false);

    int start = buscarVertice(origen);
    int end = buscarVertice(destino);

    if (start == -1 || end == -1) {
      costo = -1; // Indica que no se encontró la ruta
      return;
    }

    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
      U minDist = std::numeric_limits<U>::max();
      int u = -1;

      for (int j = 0; j < n; j++) {
        if (!visited[j] && dist[j] < minDist) {
          minDist = dist[j];
          u = j;
        }
      }

      if (u == -1) break; // Todos los nodos visitados o inaccesibles

      visited[u] = true;

      for (int v = 0; v < n; v++) {
        U weight = *(*(aristas + u) + v);
        if (weight != 0 && !visited[v]) {
          U alt = dist[u] + weight;
          if (alt < dist[v]) {
            dist[v] = alt;
            prev[v] = u;
          }
        }
      }
    }

    // Reconstruir la ruta
    ruta.clear();
    for (int at = end; at != -1; at = prev[at]) {
      ruta.push_back(vertices[at]);
    }
    std::reverse(ruta.begin(), ruta.end());

    if (dist[end] == std::numeric_limits<U>::max()) {
      costo = -1; // Indica que no se encontró la ruta
      ruta.clear();
    } else {
      costo = dist[end];
    } 
  }

template class Grafo<char, float>;