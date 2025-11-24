// genoma.cpp
#include "./genoma.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "./grafo.h"
#include "./log.hpp"
#include "./secuencia.h"
#include "./termcolor.hpp"
#include "graph_renderer.h"


using namespace std;

// ==========================
// Constructores / Destructor
// ==========================
Genoma::Genoma() = default;
Genoma::Genoma(const std::vector<Secuencia>& secuencias)
    : secuencias_(secuencias) {}
Genoma::~Genoma() = default;

// ======= Getters ========
const std::vector<Secuencia>& Genoma::get_secuencias() const {
  return secuencias_;
}
std::vector<Secuencia>& Genoma::get_secuencias() { return secuencias_; }

// ====== Setters / Modificadores ======
void Genoma::set_secuencias(const std::vector<Secuencia>& secuencias) {
  secuencias_ = secuencias;
}
void Genoma::clear_secuencias() { secuencias_.clear(); }
void Genoma::add_secuencia(const Secuencia& s) { secuencias_.push_back(s); }
size_t Genoma::size() const { return secuencias_.size(); }

// ListarSecuencias() -> void
void Genoma::ListarSecuencias() {
  // Posibles estados:
  // No hay secuencias cargadas
  // Resultado exitoso: Hay n secuencias cargadas
  vector<Secuencia>& secuencias = get_secuencias();
  if (secuencias.empty()) {
    LOG_ADVERTENCIA("ListarSecuencias", "No hay secuencias cargadas.");
    return;
  }
  LOG_INFO("ListarSecuencias",
           string("Total de secuencias: ") + to_string(secuencias.size()));

  // Usar vectores en lugar de map<>, set<>
  vector<vector<char>> complementos(256);
  complementos['A'].push_back('A');
  complementos['C'].push_back('C');
  complementos['G'].push_back('G');
  complementos['T'].push_back('T');
  complementos['U'].push_back('U');

  complementos['R'] = {'A', 'G'};
  complementos['Y'] = {'C', 'T', 'U'};

  complementos['K'] = {'G', 'T', 'U'};
  complementos['M'] = {'A', 'C'};

  complementos['S'] = {'C', 'G'};
  complementos['W'] = {'A', 'T', 'U'};

  complementos['B'] = {'C', 'G', 'T', 'U'};
  complementos['D'] = {'A', 'G', 'T', 'U'};
  complementos['H'] = {'A', 'C', 'T', 'U'};
  complementos['V'] = {'A', 'C', 'G'};
  complementos['N'] = {'A', 'C', 'G', 'T', 'U'};
  complementos['X'] = {'A', 'C', 'G', 'T', 'U'};

  for (const Secuencia& secuencia : secuencias) {
    bool completa =
        true;  // Indica si la secuencia es completa (solo bases fijas)

    // Obtener bases y separar fijas / variables, además contar gaps
    vector<char> bases = secuencia.get_bases();
    vector<char> basesUnicas;  // reemplazo de set<char>
    vector<char>
        basesVariables;  // guardar bases variables (para procesar una vez)
    size_t gaps = 0;

    for (char base : bases) {
      if (base == 'A' || base == 'C' || base == 'G' || base == 'T' ||
          base == 'U') {
        if (find(basesUnicas.begin(), basesUnicas.end(), base) ==
            basesUnicas.end()) {
          basesUnicas.push_back(base);
        }
      } else if (base == '-') {
        ++gaps;
      } else {
        if (find(basesVariables.begin(), basesVariables.end(), base) ==
            basesVariables.end()) {
          basesVariables.push_back(base);
        }
      }
    }

    // Verifica bases variables usando complementos, manteniendo la misma lógica
    // (añade/consulta la primera base complementaria encontrada y marca
    // completa = false si hay alguna variable)
    for (char base : basesVariables) {
      const vector<char>& comps = complementos[(unsigned char)base];
      for (char c : comps) {
        if (find(basesUnicas.begin(), basesUnicas.end(), c) !=
            basesUnicas.end()) {
          completa = false;
          break;
        } else {
          basesUnicas.push_back(c);
          completa = false;
          break;
        }
      }
    }

    string msg =
        string("La secuencia '") + secuencia.get_descripcion() + "' " +
        (completa || basesUnicas.size() == 5 ? "tiene " : "tiene al menos ") +
        to_string(basesUnicas.size()) + " bases. Y la secuencia es de " +
        (gaps == 0 ? "exactamente " : "al menos ") +
        to_string(secuencia.bases_size() - gaps) + " bases de largo.";
    LOG_INFO("ListarSecuencias", msg);
  }
}

// Histograma(descripcion_secuencia) -> void
void Genoma::Histograma(const char* descripcion_secuencia) {
  // Posibles estados:
  // la secuencia no existe: secuencia inválida
  // la secuencia existe A: frecuencia a \n C: frecuencia c \n G: frecuencia g
  // \n T: frecuencia t \n -: frecuencia -

  std::vector<Secuencia>& secuencias = get_secuencias();
  size_t tam = secuencias.size();
  for (size_t i = 0; i < secuencias.size(); ++i) {
    if (secuencias[i].get_descripcion() == descripcion_secuencia) {
      tam = i;
      break;
    }
  }

  if (tam == secuencias.size()) {
    LOG_ERROR("Histograma", "Secuencia inválida o inexistente.");
    return;
  }

  const char tabla[18] = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M',
                          'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};
  int frec[18];

  for (int i = 0; i < 18; ++i) {
    frec[i] = 0;
  }

  const vector<char>& bases = secuencias[tam].get_bases();

  for (size_t i = 0; i < bases.size(); ++i) {
    char b = bases[i];
    for (int j = 0; j < 18; ++j) {
      if (b == tabla[j]) {
        frec[j]++;
        break;
      }
    }
  }

  LOG_INFO("Histograma", string("Frecuencias de '") +
                             secuencias[tam].get_descripcion() + "':");
  for (int i = 0; i < 18; ++i) {
    Log("Histograma", LogEstado::Info,
        string(1, tabla[i]) + " -> " + to_string(frec[i]));
  }
}

// EsSubsecuencia(subsecuencia) -> booleano
bool Genoma::EsSubsecuencia(const char* subsecuencia) {
  // Posibles estados:
  // No hay secuencias cargadas
  // La subsecuencia no existe
  // Varias subsecuencias

  std::vector<Secuencia>& secuencias = get_secuencias();
  if (secuencias.empty()) {
    LOG_ADVERTENCIA("EsSubsecuencia", "No hay secuencias cargadas en memoria.");
    return false;
  }

  size_t tam = strlen(subsecuencia);

  if (tam == 0) {
    LOG_ADVERTENCIA("EsSubsecuencia", "La subsecuencia está vacía.");
    return false;
  }

  int total = 0;

  for (size_t s = 0; s < secuencias.size(); s++) {
    const vector<char>& scs = secuencias[s].get_bases();

    for (size_t i = 0; i + tam <= scs.size(); i++) {
      size_t k = 0;

      while (k < tam) {
        char a = scs[i + k];       // letra en la secuencia
        char b = subsecuencia[k];  // letra en la subsecuencia
        bool equiv = false;

        switch (a) {  // Equivalencias
          case 'A':
            equiv = (b == 'A');
            break;
          case 'C':
            equiv = (b == 'C');
            break;
          case 'G':
            equiv = (b == 'G');
            break;
          case 'T':
            equiv = (b == 'T');
            break;
          case 'U':
            equiv = (b == 'U');
            break;
          case 'R':
            equiv = (b == 'A' || b == 'G' || b == 'R');
            break;
          case 'Y':
            equiv = (b == 'C' || b == 'T' || b == 'U' || b == 'Y');
            break;
          case 'K':
            equiv = (b == 'G' || b == 'T' || b == 'U' || b == 'K');
            break;
          case 'M':
            equiv = (b == 'A' || b == 'C' || b == 'M');
            break;
          case 'S':
            equiv = (b == 'C' || b == 'G' || b == 'S');
            break;
          case 'W':
            equiv = (b == 'A' || b == 'T' || b == 'U' || b == 'W');
            break;
          case 'B':
            equiv = (b == 'C' || b == 'G' || b == 'T' || b == 'U' || b == 'B');
            break;
          case 'D':
            equiv = (b == 'A' || b == 'G' || b == 'T' || b == 'U' || b == 'D');
            break;
          case 'H':
            equiv = (b == 'A' || b == 'C' || b == 'T' || b == 'U' || b == 'H');
            break;
          case 'V':
            equiv = (b == 'A' || b == 'C' || b == 'G' || b == 'V');
            break;
          case 'N':
            equiv = (b == 'A' || b == 'C' || b == 'G' || b == 'T' || b == 'U' ||
                     b == 'N');
            break;  // cualquiera
          case 'X':
            equiv = (b == 'X');
            break;  // Mascara
          case '-':
            equiv = (b == '-');
            break;  // Indeterminado
          default:
            equiv = false;
        }

        if (!equiv) break;
        k++;
      }

      if (k == tam) {
        total++;
      }
    }
  }

  if (total == 0) {
    LOG_ADVERTENCIA("EsSubsecuencia",
                    "La subsecuencia no existe dentro de las secuencias "
                    "cargadas en memoria.");
    return false;
  }
  LOG_EXITO("EsSubsecuencia",
            string("La subsecuencia dada se repite ") + to_string(total) +
                " veces dentro de las secuencias cargadas en memoria.");
  return true;
}

// Enmascarar(subsecuencia) -> void
void Genoma::Enmascarar(const char* subsecuencia) {
  // Validaciones básicas
  std::vector<Secuencia>& secuencias = get_secuencias();
  if (secuencias.empty()) {
    LOG_ADVERTENCIA("Enmascarar", "No hay secuencias cargadas.");
    return;
  }
  if (subsecuencia == nullptr || subsecuencia[0] == '\0') {
    LOG_ADVERTENCIA("Enmascarar", "Subsecuencia vacía o inválida.");
    return;
  }

  size_t largoSub = strlen(subsecuencia);

  long totalEnmascaradas =
      0;  // número total de coincidencias (veces) en todas las secuencias
  long totalBasesEnmascaradas =
      0;  // cantidad total de bases reemplazadas por 'X'

  for (Secuencia& secuencia : secuencias) {
    if (secuencia.get_bases().size() < largoSub)
      continue;  // imposible que exista

    long enmascaradasEnSecuencia = 0;
    // Búsqueda lineal no solapada; avance por largoSub si matchea, sino 1
    for (size_t i = 0; i + largoSub <= secuencia.get_bases().size();) {
      // Use std::equal for faster/more optimized comparison of the range.
      // (Requires #include <algorithm> in the file.)
      const std::vector<char>& basesRef = secuencia.get_bases();
      if (equal(basesRef.begin() + i, basesRef.begin() + i + largoSub,
                subsecuencia)) {
        // Enmascarar
        for (size_t k = 0; k < largoSub; ++k) {
          secuencia.set_base(i + k, 'X');
        }
        ++enmascaradasEnSecuencia;
        ++totalEnmascaradas;
        totalBasesEnmascaradas += largoSub;
        i += largoSub;  // evitar solapamientos
      } else {
        ++i;
      }
    }

    if (enmascaradasEnSecuencia > 0) {
      LOG_INFO("Enmascarar",
               string("La subsecuencia '") + subsecuencia + "' se enmascaró " +
                   to_string(enmascaradasEnSecuencia) +
                   (enmascaradasEnSecuencia == 1 ? " vez" : " veces") +
                   " en la secuencia '" + secuencia.get_descripcion() + "'.");
    }
  }

  if (totalEnmascaradas == 0) {
    LOG_ADVERTENCIA(
        "Enmascarar",
        string("No se encontraron coincidencias de '") + subsecuencia + "'.");
  } else {
    LOG_EXITO("Enmascarar",
              string("Se enmascaró la subsecuencia '") + subsecuencia + "' " +
                  to_string(totalEnmascaradas) +
                  (totalEnmascaradas == 1 ? " vez" : " veces") + " en total (" +
                  to_string(totalBasesEnmascaradas) + " bases reemplazadas).");
  }
}

// Funcion auxiliar frmula de peso
double calcularPesoBases(char a, char b) {
  // Peso = 1 / (1 + |ASCII_a - ASCII_b|)
  double diff = std::abs(static_cast<int>(a) -
                         static_cast<int>(b));  // abs valor absoluto
  return 1.0 / (1.0 + diff);
}

// Metodo para construir el grafo
Grafo Genoma::construirGrafo(const std::vector<char>& bases, int ancho) const {
  int total_nodos = static_cast<int>(bases.size());
  Grafo grafo(total_nodos);

  for (int u = 0; u < total_nodos; ++u) {
    int fila_u = u / ancho;
    int col_u = u % ancho;

    // Arriba, Abajo, Izquierda, Derecha
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int k = 0; k < 4; ++k) {
      int fila_v = fila_u + dr[k];
      int col_v = col_u + dc[k];
      int v = fila_v * ancho + col_v;

      // Validar limites de matriz y vector
      if (fila_v >= 0 && col_v >= 0 && col_v < ancho && v < total_nodos) {
        double peso = calcularPesoBases(bases[u], bases[v]);
        grafo.agregarArista(u, v, peso);
      }
    }
  }
  return grafo;
}

void Genoma::RutaMasCorta(const char* descripcion_secuencia, int i, int j,
                          int x, int y) {
  // Buscar secuencia
  std::vector<Secuencia>& listaSec = get_secuencias();
  Secuencia* secuenciaObj = NULL;

  for (size_t k = 0; k < listaSec.size(); ++k) {
    if (listaSec[k].get_descripcion() == descripcion_secuencia) {
      secuenciaObj = &listaSec[k];
      break;
    }
  }

  if (secuenciaObj == NULL) {
    LOG_ERROR("RutaMasCorta",
              string("La secuencia ") + descripcion_secuencia + " no existe.");
    return;
  }

  // Datos secuencia
  const vector<char>& bases = secuenciaObj->get_bases();
  int ancho = secuenciaObj->get_ancho_linea();
  int total_nodos = static_cast<int>(bases.size());

  // Convertir coordenadas matriz(fila, col) a vector (ID de nodo)
  // ID = fila * ancho + columna
  int nodoOrigen = i * ancho + j;
  int nodoDestino = x * ancho + y;

  if (nodoOrigen < 0 || nodoOrigen >= total_nodos || j < 0 || j >= ancho) {
    LOG_ERROR("RutaMasCorta", string("La base en la posición [") +
                                  to_string(i) + "," + to_string(j) +
                                  "] no existe.");
    return;
  }
  if (nodoDestino < 0 || nodoDestino >= total_nodos || y < 0 || y >= ancho) {
    LOG_ERROR("RutaMasCorta", string("La base en la posición [") +
                                  to_string(x) + "," + to_string(y) +
                                  "] no existe.");
    return;
  }

  // Instanciar el TAD Grafo
  Grafo grafo = construirGrafo(bases, ancho);

  // Algoritmo de Dijkstra
  ResultadoDijkstra res = grafo.dijkstra(nodoOrigen);

  // Verificar si se encontro ruta
  if (res.distancias[nodoDestino] == numeric_limits<double>::infinity()) {
    LOG_ADVERTENCIA("RutaMasCorta",
                    "No hay ruta posible entre los nodos seleccionados.");
    return;
  }

  // Reconstruccio del camino
  stack<int> caminoPila;
  int actual = nodoDestino;
  while (actual != -1) {
    caminoPila.push(actual);
    actual = res.previos[actual];

    if (actual == nodoDestino) break;
  }

  // Imprimir salida (usar renderer para ventana rectangular)
  //  Construir vector de nodos en orden (origen -> destino)
  std::vector<int> path_nodes;
  while (!caminoPila.empty()) {
    path_nodes.push_back(caminoPila.top());
    caminoPila.pop();
  }

  cout << termcolor::green << "\t[RutaMasCorta/Exito]: " << termcolor::reset
       << endl;
  cout << "Para la secuencia " << descripcion_secuencia
       << ", la ruta más corta entre ";
  cout << "la base " << bases[nodoOrigen] << " en [" << i << "," << j << "] y ";
  cout << "la base " << bases[nodoDestino] << " en [" << x << "," << y
       << "] es:" << endl;

  // Llamada al renderer: mostrar ruta (4 decimales, color)
  print_graph_stdout(grafo, path_nodes, bases, ancho, true, 4);

  // Mostrar costo total
  cout << fixed << setprecision(4);
  cout << "El costo total de la ruta es: " << res.distancias[nodoDestino]
       << endl;
}

// BaseRemota (descripcion_secuencia, i, j) -> void
void Genoma::BaseRemota(const char* descripcion_secuencia, int i, int j) {
  // Buscar secuencia
  Secuencia* secuenciaObj = nullptr;
  std::vector<Secuencia>& lista = get_secuencias();
  for (size_t k = 0; k < lista.size(); ++k) {
    if (lista[k].get_descripcion() == descripcion_secuencia) {
      secuenciaObj = &lista[k];
      break;
    }
  }

  if (secuenciaObj == nullptr) {
    LOG_ERROR("BaseRemota",
              string("La secuencia ") + descripcion_secuencia + " no existe.");
    return;
  }

  const vector<char>& bases = secuenciaObj->get_bases();
  int ancho = secuenciaObj->get_ancho_linea();
  int total_nodos = static_cast<int>(bases.size());
  int nodoOrigen = i * ancho + j;

  // Validacio origen
  if (nodoOrigen < 0 || nodoOrigen >= total_nodos || j < 0 || j >= ancho) {
    LOG_ERROR("BaseRemota", "Posición de base inválida.");
    return;
  }

  char baseBuscada = bases[nodoOrigen];

  // Pitaoras Buscar la base mas lejana
  int nodoRemoto = -1;
  double maxDistanciaEuclidiana = -1.0;
  int remotoI = -1, remotoJ = -1;

  for (int k = 0; k < total_nodos; ++k) {
    if (bases[k] == baseBuscada) {
      int r = k / ancho;
      int c = k % ancho;

      // Distancia Euclidiana sqrt((x2-x1)^2 + (y2-y1)^2)
      double distancia = std::sqrt(std::pow(r - i, 2) + std::pow(c - j, 2));

      if (distancia > maxDistanciaEuclidiana) {
        maxDistanciaEuclidiana = distancia;
        nodoRemoto = k;
        remotoI = r;
        remotoJ = c;
      }
    }
  }

  if (nodoRemoto == -1 || nodoRemoto == nodoOrigen) {
    LOG_ADVERTENCIA(
        "BaseRemota",
        "No se encontró otra base idéntica lejana (o la única es la misma).");
    // Aqui no vale ruta que cueste 0 pero tambien podria valer
    //  return;
  }

  // Construir Grafo y Dijkstra
  Grafo grafo = construirGrafo(bases, ancho);
  ResultadoDijkstra res = grafo.dijkstra(nodoOrigen);

  // Verificar si hay camino
  if (res.distancias[nodoRemoto] == numeric_limits<double>::infinity()) {
    LOG_ADVERTENCIA("BaseRemota",
                    "La base remota existe pero no hay un camino válido (grafo "
                    "disconexo).");
    return;
  }

  // Reconstruir camino
  stack<int> camino;
  int curr = nodoRemoto;
  while (curr != -1) {
    camino.push(curr);
    curr = res.previos[curr];
  }

  // Salida (usar renderer)
  cout << termcolor::green << "\t[BaseRemota/Exito]: " << termcolor::reset
       << endl;
  cout << "Para la secuencia " << descripcion_secuencia
       << ", la base remota está ubicada en [" << remotoI << "," << remotoJ
       << "], ";
  cout << "y la ruta entre la base en [" << i << "," << j
       << "] y la base remota en [" << remotoI << "," << remotoJ
       << "] es:" << endl;

  std::vector<int> path_nodes;
  while (!camino.empty()) {
    path_nodes.push_back(camino.top());
    camino.pop();
  }

  print_graph_stdout(grafo, path_nodes, bases, ancho, true, 4);

  cout << fixed << setprecision(4);
  cout << "El costo total de la ruta es: " << res.distancias[nodoRemoto]
       << endl;
}
