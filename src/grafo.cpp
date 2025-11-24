#include "grafo.h"

#include <limits>
#include <vector>


using namespace std;

// Constructor
Grafo::Grafo(int vertices)
    : numVertices(vertices), INFINITO(std::numeric_limits<double>::infinity()) {
  // Inicializar la matriz de VxV con valor INFINITO
  matrizAdyacencia.resize(numVertices);
  for (int i = 0; i < numVertices; ++i) {
    matrizAdyacencia[i].resize(numVertices, INFINITO);
    // La distancia de un nodo a si mismo es 0
    matrizAdyacencia[i][i] = 0.0;  // Diagonal princilal
  }
}

// Agregar arista
void Grafo::agregarArista(int origen, int destino, double peso) {
  // Confirmar de rangos
  if (origen >= 0 && origen < numVertices && destino >= 0 &&
      destino < numVertices) {
    matrizAdyacencia[origen][destino] = peso;
  }
}

// Algoritmo de Dijkstra
// Conjunto Q + Busqueda Lineal del Minimo
ResultadoDijkstra Grafo::dijkstra(int nodoOrigen) {
  // Inicializacion
  // dist[] inicializado en INFINITO
  // prev[] inicializado en -1
  // Q contiene todos los nodos
  vector<double> dist(numVertices, INFINITO);
  vector<int> prev(numVertices, -1);
  vector<int> Q;

  for (int v = 0; v < numVertices; ++v) {
    dist[v] = INFINITO;
    prev[v] = -1;
    Q.push_back(v);
  }

  // La distancia al origen es 0
  dist[nodoOrigen] = 0.0;

  // Bucle principa Mientras Q no este vacio
  while (!Q.empty()) {
    // Encontrar el vertice u en Q con la distancia minima
    int u = -1;
    double minDistancia = INFINITO;
    int indiceEnQ = -1;

    // Busqueda lineal
    for (size_t i = 0; i < Q.size(); ++i) {
      int nodoCandidato = Q[i];
      if (dist[nodoCandidato] < minDistancia) {
        minDistancia = dist[nodoCandidato];
        u = nodoCandidato;
        indiceEnQ = static_cast<int>(i);
      }
    }

    // Si la distancia minima es INFINITO o u es -1 termina
    if (u == -1 || minDistancia == INFINITO) {
      break;
    }

    // Remover u de Q
    // Borrar elemento en la posicion encontrada
    Q.erase(Q.begin() + indiceEnQ);

    // Para cada vecino v de u
    // En una matriz de adyacencia, recorrerla fila 'u' completa
    for (int v = 0; v < numVertices; ++v) {
      // Verifica si hay conexion (peso != INFINITO) y que no sea el mismo nodo
      if (matrizAdyacencia[u][v] != INFINITO && u != v) {
        double peso = matrizAdyacencia[u][v];

        // Mirar si este camino es el mas corto o no
        double alt = dist[u] + peso;

        if (alt < dist[v]) {
          dist[v] = alt;
          prev[v] = u;
        }
      }
    }
  }

  ResultadoDijkstra res;
  res.distancias = dist;
  res.previos = prev;
  return res;
}

// Getters
int Grafo::get_num_vertices() const { return numVertices; }

const std::vector<std::vector<double> >& Grafo::get_matriz_adyacencia() const {
  return matrizAdyacencia;
}