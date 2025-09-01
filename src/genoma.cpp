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

size_t tam = secuencias.size();
    for (size_t i = 0; i < secuencias.size(); ++i) {
        if (secuencias[i].descripcion == descripcion_secuencia) {
            tam = i;
            break;
        }
    }
	
    if (tam == secuencias.size()) { //No entro al if, no encontro la secuencia
        cout << termcolor::red << "\t[Histograma/Error]: Secuencia inválida o inexistente" << termcolor::reset << endl;
		return;  //Se sale
    }

    const char tabla[18] = {'A','C','G','T','U','R','Y','K','M','S','W','B','D','H','V','N','X','-'};
    int frec[18];
	
    for (int i = 0; i < 18; ++i) {
		frec[i] = 0;
	}

    const vector<char>& bases = secuencias[tam].bases;
	
    for (size_t i = 0; i < bases.size(); ++i) {
        char b = bases[i];
        for (int j = 0; j < 18; ++j) {
            if (b == tabla[j]) { 
				frec[j]++; 
				break;
				}
        }
    }

    for (int i = 0; i < 18; ++i) {
        cout << termcolor::cyan << "\t[Histograma/"<< secuencias[tam].descripcion <<"]: " << tabla[i] << termcolor::reset << " -> "  << frec[i] << endl;
    }
    
}

//EsSubsecuencia(subsecuencia) -> booleano
bool Genoma::EsSubsecuencia(const char* subsecuencia){
    // TODO: Implementación de la verificación de subsecuencia

    // Posibles estados:
    // No hay secuencias cargadas
    // La subsecuencia no existe
    // Varias subsecuencias

    if (secuencias.empty()) {
        cout << termcolor::yellow << "\t[Es Subsecuencia/Advertencia]: No hay secuencias cargadas en memoria" << termcolor::reset << endl;
        return false;
    }

    size_t tam = strlen(subsecuencia);

    if (tam == 0) {
        cout << termcolor::yellow << "\t[Es Subsecuencia/Advertencia]: La subsecuencia no existe dentro de las secuencias cargadas en memoria" << termcolor::reset << endl;
        return false;
    }

    int total = 0;

    for (size_t s = 0; s < secuencias.size(); s++) {
        const vector<char> &scs = secuencias[s].bases;

        for (size_t i = 0; i + tam <= scs.size(); i++) {
            size_t k = 0;

            while (k < tam && scs[i + k] == subsecuencia[k]) {
                k++;
            }

            if (k == tam) {
                total++;
            }
        }
    }

    if (total == 0) {
        cout << termcolor::yellow <<
                "\t[Es Subsecuencia/Advertencia]: La subsecuencia no existe dentro de las secuencias cargadas en memoria" << termcolor::reset << endl;
        return false;
    } else {
        cout << termcolor::cyan << "\t[Es Subsecuencia]: La subsecuencia dada se repite " << total << " veces dentro de las secuencias cargadas en memoria" << termcolor::reset << endl;
        return true;
    }
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
            coincide = equal(secuencia.bases.begin() + i, secuencia.bases.begin() + i + largoSub, subsecuencia);
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
            cout << termcolor::cyan << "\t[Enmascarar]: La subsecuencia '" << subsecuencia << "' se enmascaró " << enmascaradasEnSecuencia << (enmascaradasEnSecuencia == 1 ? " vez" : " veces") << " en la secuencia '" << secuencia.descripcion << "'." << termcolor::reset << endl;
        }
    }

    if (totalEnmascaradas == 0) {
        cout << termcolor::yellow << "\t[Enmascarar/Advertencia]: No se encontraron coincidencias de '" << subsecuencia << "'." << termcolor::reset << endl;
    } else {
        cout << termcolor::green << "\t[Enmascarar]: Se enmascaró la subsecuencia '" << subsecuencia << "' " << totalEnmascaradas << (totalEnmascaradas == 1 ? " vez" : " veces") << " en total (" << totalBasesEnmascaradas << " bases reemplazadas)." << termcolor::reset << endl;
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
