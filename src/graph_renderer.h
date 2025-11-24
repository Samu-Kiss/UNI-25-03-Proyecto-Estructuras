// graph_renderer.h
#ifndef GRAPH_RENDERER_H
#define GRAPH_RENDERER_H

#include <vector>

#include "grafo.h"


// Prototipo con la firma que ya usa `genoma.cpp`.
// Parámetros:
// - g: grafo construido
// - path_nodes: nodos en orden desde origen hasta destino
// - bases: vector de bases (letra por nodo)
// - ancho: ancho de la matriz original (para calcular filas/cols)
// - color: habilita coloreado (usa termcolor.hpp)
// - decimals: cantidad de decimales para pesos
void print_graph_stdout(const Grafo& g, const std::vector<int>& path_nodes,
                        const std::vector<char>& bases, int ancho,
                        bool color, int decimals);

#endif  // GRAPH_RENDERER_H