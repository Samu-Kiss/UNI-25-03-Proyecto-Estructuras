// graph_renderer.cpp
#include "graph_renderer.h"

#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <unordered_map>

#include "log.hpp"
#include "termcolor.hpp"

using namespace std;

void print_graph_stdout(const Grafo& g, const std::vector<int>& path_nodes,
                        const std::vector<char>& bases, int ancho,
                        bool color, int decimals) {
  int total_nodos = g.get_num_vertices();
  if (total_nodos <= 0) return;

  // Calcular bounding box de los nodos en path
  int minr = INT_MAX, minc = INT_MAX, maxr = INT_MIN, maxc = INT_MIN;
  for (int node : path_nodes) {
    int r = node / ancho;
    int c = node % ancho;
    minr = std::min(minr, r);
    minc = std::min(minc, c);
    maxr = std::max(maxr, r);
    maxc = std::max(maxc, c);
  }
  if (minr == INT_MAX) {
    LOG_ADVERTENCIA("Renderer",
                    "Camino vacío: no hay nodos para renderizar la matriz.");
    return;  // path vacío
  }

  // Usar exactamente el bounding box del path (sin padding ni truncado)
  minr = max(0, minr);
  minc = max(0, minc);
  int filas = (total_nodos + ancho - 1) / ancho;
  maxr = min(filas - 1, maxr);
  maxc = min(ancho - 1, maxc);

  // Set para identificar nodos del path rápidamente
  set<int> path_set(path_nodes.begin(), path_nodes.end());
  // Mapa nodo -> indice en path_nodes para detectar giros (esquinas)
  unordered_map<int, int> path_index;
  for (size_t idx = 0; idx < path_nodes.size(); ++idx)
    path_index[path_nodes[idx]] = static_cast<int>(idx);

  // Dibujar solo el camino en forma de matriz (un caracter por celda, sin
  // separadores)
  for (int r = minr; r <= maxr; ++r) {
    for (int c = minc; c <= maxc; ++c) {
      int id = r * ancho + c;
      std::string cellStr = " ";
      bool isPathNode = (id >= 0 && id < total_nodos && path_set.count(id));
      if (isPathNode) {
        // inicio o fin: mostrar letra base
        if (!path_nodes.empty() &&
            (id == path_nodes.front() || id == path_nodes.back())) {
          cellStr = std::string(1, bases[id]);
        } else {
          // nodo intermedio: determinar caracter de trayectoria según prev/next
          unordered_map<int, int>::iterator it = path_index.find(id);
          if (it != path_index.end()) {
            int idx = it->second;
            int prev = (idx > 0) ? path_nodes[idx - 1] : -1;
            int next =
                (idx + 1 < (int)path_nodes.size()) ? path_nodes[idx + 1] : -1;
            int pr = (prev == -1) ? INT_MIN : prev / ancho;
            int pc = (prev == -1) ? INT_MIN : prev % ancho;
            int nr = (next == -1) ? INT_MIN : next / ancho;
            int nc = (next == -1) ? INT_MIN : next % ancho;

            int vprev_r =
                (prev == -1) ? 0 : (pr - r);  // vector from curr to prev (row)
            int vprev_c =
                (prev == -1) ? 0 : (pc - c);  // vector from curr to prev (col)
            int vnext_r =
                (next == -1) ? 0 : (nr - r);  // vector from curr to next (row)
            int vnext_c =
                (next == -1) ? 0 : (nc - c);  // vector from curr to next (col)

            // Straight horizontal (both neighbors in same row)
            if (vprev_r == 0 && vnext_r == 0) cellStr = "─";
            // Straight vertical (both neighbors in same column)
            else if (vprev_c == 0 && vnext_c == 0)
              cellStr = "│";
            else {
              bool up = (vprev_r == -1) || (vnext_r == -1);
              bool down = (vprev_r == 1) || (vnext_r == 1);
              bool left = (vprev_c == -1) || (vnext_c == -1);
              bool right = (vprev_c == 1) || (vnext_c == 1);

              // Map connection pairs to correct box-drawing corners:
              // - connections to right+down => '┌' (top-left corner)
              // - connections to left+down  => '┐' (top-right corner)
              // - connections to right+up   => '└' (bottom-left corner)
              // - connections to left+up    => '┘' (bottom-right corner)
              if (down && right)
                cellStr = "┌";
              else if (down && left)
                cellStr = "┐";
              else if (up && right)
                cellStr = "└";
              else if (up && left)
                cellStr = "┘";
              else if (up && down)
                cellStr = "│";
              else if (left && right)
                cellStr = "─";
              else
                cellStr = "─";
            }
          }
        }
      }

      // imprimir sin espacios entre celdas; aplicar color si es nodo del path y
      // es letra (start/end)
      if (isPathNode && (id == path_nodes.front() || id == path_nodes.back())) {
        if (color)
          cout << termcolor::green << cellStr << termcolor::reset;
        else
          cout << cellStr;
      } else {
        // para los caracteres de trazado también aplicar color si requested
        if (isPathNode && color)
          cout << termcolor::green << cellStr << termcolor::reset;
        else
          cout << cellStr;
      }
    }
    cout << "\n";
  }

  // Detalle de la ruta: una línea por arista en el camino con peso
  cout << "\nDetalles de la ruta (pasos):\n";
  const std::vector<std::vector<double> >& mat = g.get_matriz_adyacencia();
  for (size_t k = 0; k + 1 < path_nodes.size(); ++k) {
    int u = path_nodes[k];
    int v = path_nodes[k + 1];
    int ur = u / ancho;
    int uc = u % ancho;
    int vr = v / ancho;
    int vc = v % ancho;

    double peso = 0.0;
    if (u >= 0 && u < (int)mat.size() && v >= 0 && v < (int)mat[u].size()) {
      peso = mat[u][v];
    }

    // Formatear peso con `decimals` si es solicitado
    std::ostringstream oss;
    if (decimals >= 0) {
      oss << std::fixed << std::setprecision(decimals) << peso;
    } else {
      oss << peso;
    }

    // Imprimir base-origen
    if (color) cout << termcolor::green;
    cout << bases[u] << "[" << ur << "," << uc << "]";
    if (color) cout << termcolor::reset;

    // Flecha con peso
    cout << " -" << oss.str() << "-> ";

    // Imprimir base-destino
    if (color) cout << termcolor::green;
    cout << bases[v] << "[" << vr << "," << vc << "]";
    if (color) cout << termcolor::reset;

    cout << "\n";
  }
}
