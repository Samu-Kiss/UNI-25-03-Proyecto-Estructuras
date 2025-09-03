#include "./termcolor.hpp"
#include "./secuencia.h"
#include "./genoma.h"
#include "./log.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;



//ListarSecuencias() -> void
void Genoma::ListarSecuencias() {
    // Posibles estados:
    // No hay secuencias cargadas
    // Resultado exitoso: Hay n secuencias cargadas
    std::vector<Secuencia>& secuencias = get_secuencias();
    if (secuencias.empty()) {
        LOG_ADVERTENCIA("ListarSecuencias", "No hay secuencias cargadas.");
        return;
    }
    LOG_INFO("ListarSecuencias", string("Total de secuencias: ") + to_string(secuencias.size()));
    for (const Secuencia &secuencia: secuencias) {
        size_t gaps = 0;
        for (char b: secuencia.get_bases()) {
            if (b == '-') {
                gaps++;
            }
        }
        string msg = string("La secuencia '") + secuencia.get_descripcion() + "' " + (gaps > 0 ? "tiene al menos " : "tiene ") + to_string(secuencia.get_bases().size() - gaps) + " bases.";
        LOG_INFO("ListarSecuencias", msg);
    }
}

//Histograma(descripcion_secuencia) -> void
void Genoma::Histograma(const char *descripcion_secuencia) {
    // Posibles estados:
    // la secuencia no existe: secuencia inválida
    // la secuencia existe A: frecuencia a \n C: frecuencia c \n G: frecuencia g \n T: frecuencia t \n -: frecuencia -

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

    const char tabla[18] = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};
    int frec[18];

    for (int i = 0; i < 18; ++i) {
        frec[i] = 0;
    }

    const vector<char> &bases = secuencias[tam].get_bases();

    for (size_t i = 0; i < bases.size(); ++i) {
        char b = bases[i];
        for (int j = 0; j < 18; ++j) {
            if (b == tabla[j]) {
                frec[j]++;
                break;
            }
        }
    }

    LOG_INFO("Histograma", string("Frecuencias de '") + secuencias[tam].get_descripcion() + "':");
    for (int i = 0; i < 18; ++i) {
        Log("Histograma", LogEstado::Info, string(1, tabla[i]) + " -> " + to_string(frec[i]));
    }
}

//EsSubsecuencia(subsecuencia) -> booleano
bool Genoma::EsSubsecuencia(const char *subsecuencia) {
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
        const vector<char> &scs = secuencias[s].get_bases();

        for (size_t i = 0; i + tam <= scs.size(); i++) {
            size_t k = 0;

            while (k < tam) {
                char a = scs[i + k];       // letra en la secuencia
                char b = subsecuencia[k];  // letra en la subsecuencia
                bool equiv = false;

                // 1) ¿a pertenece al conjunto que representa b?
                switch (b) {
                    case 'A': equiv = (a=='A'); break;
                    case 'C': equiv = (a=='C'); break;
                    case 'G': equiv = (a=='G'); break;
                    case 'T': equiv = (a=='T'); break;
                    case 'U': equiv = (a=='U'); break;
                    case 'R': equiv = (a=='A' || a=='G'); break;
                    case 'Y': equiv = (a=='C' || a=='T' || a=='U'); break;
                    case 'K': equiv = (a=='G' || a=='T' || a=='U'); break;
                    case 'M': equiv = (a=='A' || a=='C'); break;
                    case 'S': equiv = (a=='C' || a=='G'); break;
                    case 'W': equiv = (a=='A' || a=='T' || a=='U'); break;
                    case 'B': equiv = (a=='C' || a=='G' || a=='T' || a=='U'); break;
                    case 'D': equiv = (a=='A' || a=='G' || a=='T' || a=='U'); break;
                    case 'H': equiv = (a=='A' || a=='C' || a=='T' || a=='U'); break;
                    case 'V': equiv = (a=='A' || a=='C' || a=='G'); break;
                    case 'N': equiv = (a=='A' || a=='C' || a=='G' || a=='T' || a=='U'); break;
                    case 'X': equiv = (a=='X'); break;   
                    case '-': equiv = (a=='-'); break;   
                    default:  equiv = false;             
                }

				if (!equiv) {
				switch (a) {
					case 'A': equiv = (b=='A' || b=='R' || b=='M' || b=='W' || b=='D' || b=='H' || b=='V' || b=='N'); break;
					case 'C': equiv = (b=='C' || b=='Y' || b=='M' || b=='S' || b=='B' || b=='H' || b=='V' || b=='N'); break;
					case 'G': equiv = (b=='G' || b=='R' || b=='S' || b=='K' || b=='B' || b=='D' || b=='V' || b=='N'); break;
					case 'T': equiv = (b=='T' || b=='Y' || b=='W' || b=='K' || b=='B' || b=='D' || b=='H' || b=='N'); break;
					case 'U': equiv = (b=='U' || b=='Y' || b=='W' || b=='K' || b=='B' || b=='D' || b=='H' || b=='N'); break;
					case 'R': equiv = (b=='A' || b=='G' || b=='R'); break;        
					case 'Y': equiv = (b=='C' || b=='T' || b=='U' || b=='Y'); break;   
					case 'K': equiv = (b=='G' || b=='T' || b=='U' || b=='K'); break;    
					case 'M': equiv = (b=='A' || b=='C' || b=='M'); break;          
					case 'S': equiv = (b=='C' || b=='G' || b=='S'); break;               
					case 'W': equiv = (b=='A' || b=='T' || b=='U' || b=='W'); break;     
					case 'B': equiv = (b=='C' || b=='G' || b=='T' || b=='U' || b=='B'); break;
					case 'D': equiv = (b=='A' || b=='G' || b=='T' || b=='U' || b=='D'); break;
					case 'H': equiv = (b=='A' || b=='C' || b=='T' || b=='U' || b=='H'); break;
					case 'V': equiv = (b=='A' || b=='C' || b=='G' || b=='V'); break;
					case 'N': equiv = (b=='A' || b=='C' || b=='G' || b=='T' || b=='U' || b=='N'); break;

					case 'X': equiv = (b=='X'); break; 
					case '-': equiv = (b=='-'); break;  
					default:  equiv = false;
				}
			}

                if (!equiv) { 
				break;
				}
                k++;
            }

            if (k == tam) {
                total++;
            }
        }
    }

    if (total == 0) {
        LOG_ADVERTENCIA("EsSubsecuencia", "La subsecuencia no existe dentro de las secuencias cargadas en memoria.");
        return false;
    }
    LOG_EXITO("EsSubsecuencia", string("La subsecuencia dada se repite ") + to_string(total) + " veces dentro de las secuencias cargadas en memoria.");
    return true;
}

//Enmascarar(subsecuencia) -> void
void Genoma::Enmascarar(const char *subsecuencia) {
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

    long totalEnmascaradas = 0; // número total de coincidencias (veces) en todas las secuencias
    long totalBasesEnmascaradas = 0; // cantidad total de bases reemplazadas por 'X'

    for (Secuencia &secuencia: secuencias) {
        if (secuencia.get_bases().size() < largoSub) continue; // imposible que exista

        long enmascaradasEnSecuencia = 0;
        // Búsqueda lineal no solapada; avance por largoSub si matchea, sino 1
    for (size_t i = 0; i + largoSub <= secuencia.get_bases().size();) {
            // Use std::equal for faster/more optimized comparison of the range.
            // (Requires #include <algorithm> in the file.)
            const std::vector<char> &basesRef = secuencia.get_bases();
            if (equal(basesRef.begin() + i, basesRef.begin() + i + largoSub, subsecuencia)) {
                // Enmascarar
                for (size_t k = 0; k < largoSub; ++k) { secuencia.set_base(i + k, 'X'); }
                ++enmascaradasEnSecuencia;
                ++totalEnmascaradas;
                totalBasesEnmascaradas += largoSub;
                i += largoSub; // evitar solapamientos
            } else {
                ++i;
            }
        }

        if (enmascaradasEnSecuencia > 0) {
            LOG_INFO("Enmascarar", string("La subsecuencia '") + subsecuencia + "' se enmascaró " + to_string(enmascaradasEnSecuencia) + (enmascaradasEnSecuencia==1?" vez":" veces") + " en la secuencia '" + secuencia.get_descripcion() + "'.");
        }
    }

    if (totalEnmascaradas == 0) {
        LOG_ADVERTENCIA("Enmascarar", string("No se encontraron coincidencias de '") + subsecuencia + "'.");
    } else {
        LOG_EXITO("Enmascarar", string("Se enmascaró la subsecuencia '") + subsecuencia + "' " + to_string(totalEnmascaradas) + (totalEnmascaradas==1?" vez":" veces") + " en total (" + to_string(totalBasesEnmascaradas) + " bases reemplazadas).");
    }
}

//RutaMasCorta(descripcion_secuencia, i, j, x, y) -> void
void Genoma::RutaMasCorta(const char *descripcion_secuencia, int i, int j, int x, int y) {
    //TODO: Implementación de la ruta más corta
    //ESTO SE HACE EN LA SEGUNDA ENTREGA
}

//BaseRemota (descripcion_secuencia, i, j) -> void
void Genoma::BaseRemota(const char *descripcion_secuencia, int i, int j) {
    //TODO: Implementación de la base remota
    //ESTO SE HACE EN LA SEGUNDA ENTREGA
}
