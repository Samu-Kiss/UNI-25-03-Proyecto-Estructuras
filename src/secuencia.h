// secuencia.h
#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <string>
#include <vector>

using std::string; 
using std::vector;

class Secuencia {
private:
    string descripcion_{};          // Descripción de la secuencia
    vector<char> bases_{};          // Bases
    int ancho_linea_{0};            // Ancho de línea original del archivo

public:
    // Constructores
    Secuencia() = default;
    Secuencia(const string &descripcion, const vector<char> &bases, int ancho_linea)
        : descripcion_(descripcion), bases_(bases), ancho_linea_(ancho_linea) {}

    // Destructor
    ~Secuencia() = default;

    // Getters (const)
    [[nodiscard]] const string &get_descripcion() const { return descripcion_; }
    [[nodiscard]] const vector<char> &get_bases() const { return bases_; }
    [[nodiscard]] int get_ancho_linea() const { return ancho_linea_; }

    // Getters (no const) para modificaciones controladas
    vector<char> &get_bases() { return bases_; }

    // Setters
    void set_descripcion(const string &descripcion) { descripcion_ = descripcion; }
    void set_bases(const vector<char> &bases) { bases_ = bases; }
    void set_ancho_linea(int ancho_linea) { ancho_linea_ = ancho_linea; }

    // Helpers específicos usados en el código existente
    void add_base(char b) { bases_.push_back(b); }
    size_t bases_size() const { return bases_.size(); }
    void set_base(size_t idx, char b) { if (idx < bases_.size()) bases_[idx] = b; }
};

#endif // SECUENCIA_H