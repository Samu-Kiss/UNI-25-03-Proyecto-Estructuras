#ifndef GRAFO_H
#define GRAFO_H

#include <vector>

// Estructura para devolver los resultados de Dijkstra
struct ResultadoDijkstra {
  std::vector<double> distancias;
  std::vector<int> previos;
};

class Grafo {
 private:
  int numVertices;
  // Matriz de Adyacencia matriz[origen][destino] = peso.
  // Si no hay arista, el valor es INFINITO.
  std::vector<std::vector<double> > matrizAdyacencia;

  // Constante para representar infinito
  const double INFINITO;

 public:
  // Constructor Inicializa la matriz de adyacencia
  Grafo(int vertices);

  // Metodo para agregar una arista con peso
  void agregarArista(int origen, int destino, double peso);

  // Algoritmo de Dijkstra
  ResultadoDijkstra dijkstra(int nodoOrigen);

  // Getters de solo lectura para renderizado
  int get_num_vertices() const;
  const std::vector<std::vector<double> >& get_matriz_adyacencia() const;
};

#endif  // GRAFO_H