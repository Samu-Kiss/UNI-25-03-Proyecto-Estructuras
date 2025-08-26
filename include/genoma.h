// genoma.h
#ifndef GENOMA_H
#define GENOMA_H

#include "../include/secuencia.h"

class Genoma {
public:

vector<Secuencia> secuencias;

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