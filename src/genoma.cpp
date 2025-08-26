#include "../include/secuencia.h"
#include "../include/genoma.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Genoma contiene una lista de secuencias
vector<Secuencia> secuencias;

//ListarSecuencias() -> void
void ListarSecuencias(){
    // TODO: Implementación de la lista de secuencias

    // Posibles estados:
    // No hay secuencias cargadas
    // Resultado exitoso: Hay n secuencias cargadas
}

//Histograma(descripcion_secuencia) -> void
void Histograma(const char* descripcion_secuencia){
    // TODO: Implementación del histograma

    // Posibles estados:
    // la secuencia no existe: secuencia inválida
    // la secuencia existe A: frecuencia a \n C: frecuencia c \n G: frecuencia g \n T: frecuencia t \n -: frecuencia -
}

//EsSubsecuencia(subsecuencia) -> booleano
bool EsSubsecuencia(const char* subsecuencia){
    // TODO: Implementación de la verificación de subsecuencia

    // Posibles estados:
    // No hay secuencias cargadas
    // La subsecuencia no existe
    // Varias subsecuencias
    return true; // Retornar true si es subsecuencia
}

//Enmascarar(subsecuencia) -> void
void Enmascarar(const char* subsecuencia){
    // TODO: Implementación de la enmascaración

    // Posibles estados:
    // No hay secuencias cargadas
    // No se enmascararon subsecuencias
    // Varias subsecuencias enmascaradas
}

//RutaMasCorta(descripcion_secuencia, i, j, x, y) -> void
void RutaMasCorta(const char* descripcion_secuencia, int i, int j, int x, int y){
    //TODO: Implementación de la ruta más corta
    //ESTO SE HACE EN LA SEGUNDA ENTREGA
}

//BaseRemota (descripcion_secuencia, i, j) -> void
void BaseRemota(const char* descripcion_secuencia, int i, int j){
    //TODO: Implementación de la base remota
    //ESTO SE HACE EN LA SEGUNDA ENTREGA
}