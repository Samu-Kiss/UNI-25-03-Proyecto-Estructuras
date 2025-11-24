// graph_renderer.h
#ifndef GRAPH_RENDERER_H
#define GRAPH_RENDERER_H

#include <vector>

#include "grafo.h"


// Prototipo con la firma que ya usa `genoma.cpp`.
// Parámetros:
// - g: grafo construido
// - res: resultado de dijkstra (distancias, previos)
// - path_nodes: nodos en orden desde origen hasta destino
// - bases: vector de bases (letra por nodo)
// - ancho: ancho de la matriz original (para calcular filas/cols)
// - pad: padding alrededor del bounding box de la ruta
// - max_nodes: máximo de nodos a mostrar; si la ventana excede este número se
// truncará
// - color: habilita coloreado (usa termcolor.hpp)
// - decimals: cantidad de decimales para pesos
// - color_edges: colorear también las aristas/pesos
void print_graph_stdout(const Grafo& g, const ResultadoDijkstra& res,
                        const std::vector<int>& path_nodes,
                        const std::vector<char>& bases, int ancho, int pad,
                        int max_nodes, bool color, int decimals,
                        bool color_edges);

#endif  // GRAPH_RENDERER_H