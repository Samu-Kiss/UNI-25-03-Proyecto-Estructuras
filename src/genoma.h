// genoma.h
#ifndef GENOMA_H
#define GENOMA_H

#include "./secuencia.h"

class Genoma {
private:
    std::vector<Secuencia> secuencias_{};

public:
    // Constructores
    Genoma() = default;
    explicit Genoma(const std::vector<Secuencia> &secuencias)
        : secuencias_(secuencias) {}

    // Destructor
    ~Genoma() = default;

    // Getters
    [[nodiscard]] const std::vector<Secuencia> &get_secuencias() const { return secuencias_; }
    // Getter no const para modificar
    std::vector<Secuencia> &get_secuencias() { return secuencias_; }

    // Setters
    void set_secuencias(const std::vector<Secuencia> &secuencias) { secuencias_ = secuencias; }
    void clear_secuencias() { secuencias_.clear(); }
    void add_secuencia(const Secuencia &s) { secuencias_.push_back(s); }
    size_t size() const { return secuencias_.size(); }

    //ListarSecuencias() -> void
    void ListarSecuencias();

    //Histograma(descripcion_secuencia) -> void
    void Histograma(const char* descripcion_secuencia);

    //EsSubsecuencia(subsecuencia) -> booleano
    bool EsSubsecuencia(const char* subsecuencia);

    //Enmascarar(subsecuencia) -> void
    void Enmascarar(const char* subsecuencia);

    //RutaMasCorta(descripcion_secuencia, i, j, x, y) -> void
    void RutaMasCorta(const char* descripcion_secuencia, int i, int j, int x, int y);

    //BaseRemota (descripcion_secuencia, i, j) -> void
    void BaseRemota(const char* descripcion_secuencia, int i, int j);

};

#endif // GENOMA_H