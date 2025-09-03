// genoma.h
#ifndef GENOMA_H
#define GENOMA_H

#include "./secuencia.h"

class Genoma {
private:
    std::vector<Secuencia> secuencias_{};

public:
    // Constructores / Destructor
    Genoma();
    explicit Genoma(const std::vector<Secuencia> &secuencias);
    ~Genoma();

    // Getters
    [[nodiscard]] const std::vector<Secuencia> &get_secuencias() const;
    std::vector<Secuencia> &get_secuencias(); // no const

    // Setters / Modificadores
    void set_secuencias(const std::vector<Secuencia> &secuencias);
    void clear_secuencias();
    void add_secuencia(const Secuencia &s);
    size_t size() const;

    // Operaciones
    void ListarSecuencias();
    void Histograma(const char* descripcion_secuencia);
    bool EsSubsecuencia(const char* subsecuencia);
    void Enmascarar(const char* subsecuencia);
    void RutaMasCorta(const char* descripcion_secuencia, int i, int j, int x, int y);
    void BaseRemota(const char* descripcion_secuencia, int i, int j);
};

#endif // GENOMA_H