// secuencia.cpp
#include "./secuencia.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;

// ==========================
// Constructores / Destructor
// ==========================
Secuencia::Secuencia() = default;
Secuencia::Secuencia(const string& descripcion, const vector<char>& bases,
                     int ancho_linea)
    : descripcion_(descripcion), bases_(bases), ancho_linea_(ancho_linea) {}
Secuencia::~Secuencia() = default;

// ======= Getters ========
const string& Secuencia::get_descripcion() const { return descripcion_; }
const vector<char>& Secuencia::get_bases() const { return bases_; }
int Secuencia::get_ancho_linea() const { return ancho_linea_; }
vector<char>& Secuencia::get_bases() { return bases_; }

// ======= Setters ========
void Secuencia::set_descripcion(const string& descripcion) {
  descripcion_ = descripcion;
}
void Secuencia::set_bases(const vector<char>& bases) { bases_ = bases; }
void Secuencia::set_ancho_linea(int ancho_linea) { ancho_linea_ = ancho_linea; }

// ======= Helpers =========
void Secuencia::add_base(char b) { bases_.push_back(b); }
size_t Secuencia::bases_size() const { return bases_.size(); }
void Secuencia::set_base(size_t idx, char b) {
  if (idx < bases_.size()) bases_[idx] = b;
}

void Secuencia::llenarGrafo(Grafo<int, float>& g) const {
  int N = static_cast<int>(bases_.size());
  int W = (ancho_linea_ > 0) ? ancho_linea_ : (N > 0 ? N : 1);

  // Insertar vértices (uno por posición: id = índice)
  for (int idx = 0; idx < N; ++idx) {
    g.insertarVertice(idx);
  }

  // Añadir aristas no dirigidas entre vecinos 4-direcciones (por índice)
  for (int idx = 0; idx < N; ++idx) {
    int fila = idx / W;
    int col = idx % W;

    int nb = idx - W; // superior
    if (nb >= 0 && nb < N) {
      if (nb != idx) {
        g.insertarArista(idx, nb);
        g.insertarArista(nb, idx);
      }
    }

    nb = idx + W; // inferior
    if (nb >= 0 && nb < N) {
      if (nb != idx) {
        g.insertarArista(idx, nb);
        g.insertarArista(nb, idx);
      }
    }

    nb = idx - 1; // izquierda
    if (col > 0 && nb >= 0 && nb < N) {
      if (nb != idx) {
        g.insertarArista(idx, nb);
        g.insertarArista(nb, idx);
      }
    }

    nb = idx + 1; // derecha
    if (col + 1 < W && nb >= 0 && nb < N) {
      if (nb != idx) {
        g.insertarArista(idx, nb);
        g.insertarArista(nb, idx);
      }
    }
  }
}