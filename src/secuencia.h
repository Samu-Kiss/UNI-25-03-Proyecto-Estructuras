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
    // Constructores / Destructor
    Secuencia();
    Secuencia(const string &descripcion, const vector<char> &bases, int ancho_linea);
    ~Secuencia();

    // Getters (const)
    [[nodiscard]] const string &get_descripcion() const;
    [[nodiscard]] const vector<char> &get_bases() const;
    [[nodiscard]] int get_ancho_linea() const;
    vector<char> &get_bases(); // no const

    // Setters
    void set_descripcion(const string &descripcion);
    void set_bases(const vector<char> &bases);
    void set_ancho_linea(int ancho_linea);

    // Helpers
    void add_base(char b);
    size_t bases_size() const;
    void set_base(size_t idx, char b);
};

#endif // SECUENCIA_H