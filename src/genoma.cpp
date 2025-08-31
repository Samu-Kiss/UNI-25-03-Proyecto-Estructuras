#include "./termcolor.hpp"
#include "./secuencia.h"
#include "./genoma.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

//ListarSecuencias() -> void
void Genoma::ListarSecuencias(){
    // TODO: Implementación de la lista de secuencias

    // Posibles estados:
    // No hay secuencias cargadas
    // Resultado exitoso: Hay n secuencias cargadas
    if (secuencias.empty()) {
        cout << termcolor::yellow << "\t[Listar Secuencias/Advertencia]: No hay secuencias cargadas." << termcolor::reset << endl;
    } else {
        cout << "Secuencias cargadas:" << endl;
        for (const Secuencia& secuencia : secuencias) {
            int cont = 0;
            for (const char& base : secuencia.bases) {
                if (base == '-') { cont++; }
            }
            cout << termcolor::cyan << "\t[Listar Secuencias]: La secuencia " << secuencia.descripcion << (cont > 0 ? " tiene al menos " : " tiene ") << secuencia.bases.size() - cont << " bases." << termcolor::reset << endl;
        }
    }
}

//Histograma(descripcion_secuencia) -> void
void Genoma::Histograma(const char* descripcion_secuencia){
    // TODO: Implementación del histograma

    // Posibles estados:
    // la secuencia no existe: secuencia inválida
    // la secuencia existe A: frecuencia a \n C: frecuencia c \n G: frecuencia g \n T: frecuencia t \n -: frecuencia -
}

//EsSubsecuencia(subsecuencia) -> booleano
bool Genoma::EsSubsecuencia(const char* subsecuencia){
    // TODO: Implementación de la verificación de subsecuencia

    // Posibles estados:
    // No hay secuencias cargadas
    // La subsecuencia no existe
    // Varias subsecuencias
    return true; // Retornar true si es subsecuencia
}

//Enmascarar(subsecuencia) -> void
void Genoma::Enmascarar(const char* subsecuencia){
    // Validaciones básicas
    if (secuencias.empty()) {
        cout << termcolor::yellow << "\t[Enmascarar/Advertencia]: No hay secuencias cargadas." << termcolor::reset << endl;
        return;
    }
    if (subsecuencia == nullptr || subsecuencia[0] == '\0') {
        cout << termcolor::yellow << "\t[Enmascarar/Advertencia]: Subsecuencia vacía o inválida." << termcolor::reset << endl;
        return;
    }

    size_t largoSub = strlen(subsecuencia);
    if (largoSub == 0) { // redundante, pero por claridad
        cout << termcolor::yellow << "\t[Enmascarar/Advertencia]: Subsecuencia vacía." << termcolor::reset << endl;
        return;
    }

    long totalEnmascaradas = 0; // número total de coincidencias (veces) en todas las secuencias
    long totalBasesEnmascaradas = 0; // cantidad total de bases reemplazadas por 'X'

    for (Secuencia &secuencia : secuencias) {
        if (secuencia.bases.size() < largoSub) continue; // imposible que exista

        long enmascaradasEnSecuencia = 0;
        // Búsqueda lineal no solapada; avance por largoSub si matchea, sino 1
        for (size_t i = 0; i + largoSub <= secuencia.bases.size(); ) {
            bool coincide = true;
            // Use std::equal for faster/more optimized comparison of the range.
            // (Requires #include <algorithm> in the file.)
            coincide = equal(secuencia.bases.begin() + i,
                             secuencia.bases.begin() + i + largoSub,
                             subsecuencia);
            if (coincide) {
                // Enmascarar
                for (size_t k = 0; k < largoSub; ++k) {
                    secuencia.bases[i + k] = 'X';
                }
                ++enmascaradasEnSecuencia;
                ++totalEnmascaradas;
                totalBasesEnmascaradas += largoSub;
                i += largoSub; // evitar solapamientos
            } else {
                ++i;
            }
        }

        if (enmascaradasEnSecuencia > 0) {
            cout << termcolor::cyan
                 << "\t[Enmascarar]: La subsecuencia '" << subsecuencia << "' se enmascaró "
                 << enmascaradasEnSecuencia << (enmascaradasEnSecuencia == 1 ? " vez" : " veces")
                 << " en la secuencia '" << secuencia.descripcion << "'." << termcolor::reset << endl;
        }
    }

    if (totalEnmascaradas == 0) {
        cout << termcolor::yellow << "\t[Enmascarar/Advertencia]: No se encontraron coincidencias de '" << subsecuencia << "'." << termcolor::reset << endl;
    } else {
        cout << termcolor::green
             << "\t[Enmascarar]: Se enmascaró la subsecuencia '" << subsecuencia << "' "
             << totalEnmascaradas << (totalEnmascaradas == 1 ? " vez" : " veces")
             << " en total (" << totalBasesEnmascaradas << " bases reemplazadas)." << termcolor::reset << endl;
    }

}

//RutaMasCorta(descripcion_secuencia, i, j, x, y) -> void
void Genoma::RutaMasCorta(const char* descripcion_secuencia, int i, int j, int x, int y){
    //TODO: Implementación de la ruta más corta
    //ESTO SE HACE EN LA SEGUNDA ENTREGA
}

//BaseRemota (descripcion_secuencia, i, j) -> void
void Genoma::BaseRemota(const char* descripcion_secuencia, int i, int j){
    //TODO: Implementación de la base remota
    //ESTO SE HACE EN LA SEGUNDA ENTREGA
}