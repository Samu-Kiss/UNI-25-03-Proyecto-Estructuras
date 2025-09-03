// genoma.cpp
#include "./termcolor.hpp"
#include "./secuencia.h"
#include "./genoma.h"
#include "./log.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>

using namespace std;



// ==========================
// Constructores / Destructor
// ==========================
Genoma::Genoma() = default;
Genoma::Genoma(const std::vector<Secuencia> &secuencias) : secuencias_(secuencias) {}
Genoma::~Genoma() = default;

// ======= Getters ========
const std::vector<Secuencia> &Genoma::get_secuencias() const { return secuencias_; }
std::vector<Secuencia> &Genoma::get_secuencias() { return secuencias_; }

// ====== Setters / Modificadores ======
void Genoma::set_secuencias(const std::vector<Secuencia> &secuencias) { secuencias_ = secuencias; }
void Genoma::clear_secuencias() { secuencias_.clear(); }
void Genoma::add_secuencia(const Secuencia &s) { secuencias_.push_back(s); }
size_t Genoma::size() const { return secuencias_.size(); }

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

        map<char, set<char>> complementos;
        complementos['A'] = {'A'                    };
        complementos['C'] = {     'C'               };
        complementos['G'] = {          'G'          };
        complementos['T'] = {               'T'     };
        complementos['U'] = {                    'U'};

        complementos['R'] = {'A',      'G'          };
        complementos['Y'] = {     'C',      'T', 'U'};

        complementos['K'] = {          'G', 'T', 'U'};
        complementos['M'] = {'A', 'C'               };

        complementos['S'] = {     'C', 'G'          };
        complementos['W'] = {'A',           'T', 'U'};
        
        complementos['B'] = {     'C', 'G', 'T', 'U'};
        complementos['D'] = {'A',      'G', 'T', 'U'};
        complementos['H'] = {'A', 'C',      'T', 'U'};
        complementos['V'] = {'A', 'C', 'G'          };
        complementos['N'] = {'A', 'C', 'G', 'T', 'U'};
        complementos['X'] = {'A', 'C', 'G', 'T', 'U'};

    for (const Secuencia &secuencia: secuencias) {
        bool completa = true; // Indica si la secuencia es completa, en otras palabras si en la secuencia unicamente hay bases fijas

        //set list para asegurar unicidad
        vector<char> bases = secuencia.get_bases();
        set<char> basesUnicas;

        size_t gaps = 0;

        // Agregar bases fijas y contar espacios "-"
        for (char base: bases) {
            if (base == 'A' || base == 'C' || base == 'G' || base == 'T' || base == 'U') {
                basesUnicas.insert(base);
                //borrar la base del vector bases
                bases.erase(remove(bases.begin(), bases.end(), base), bases.end());
            }
             if (base == '-') {
                gaps++;
            }
        }

        //Verifica bases variables
        for (char base: bases) {

            set<char> complementosBase = complementos[base];

            // Si la interseccion entre basesUnicas y complementosBase es vacia, entonces se añade base a basesUnicas
            for (char c : complementosBase) { 
                if (basesUnicas.find(c) != basesUnicas.end()) {
                    completa = false; 
                    break;
                } else {
                    basesUnicas.insert(c);
                    completa = false;
                    break;
                }
            }
        }



        string msg = string("La secuencia '") + secuencia.get_descripcion() + "' " + (completa || basesUnicas.size() == 5 ? "tiene " : "tiene al menos ") + to_string(basesUnicas.size()) + " bases. Y la secuencia es de " + (gaps == 0 ? "exactamente " : "al menos ") + to_string(secuencia.bases_size()-gaps) + " bases de largo.";
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

                switch (a) { //Equivalencias
                    case 'A': equiv = (b=='A'); break;
                    case 'C': equiv = (b=='C'); break;
                    case 'G': equiv = (b=='G'); break;
                    case 'T': equiv = (b=='T'); break;
                    case 'U': equiv = (b=='U'); break;
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
                    case 'N': equiv = (b=='A' || b=='C' || b=='G' || b=='T' || b=='U' || b=='N'); break; // cualquiera
                    case 'X': equiv = (b=='X'); break; //Mascara
                    case '-': equiv = (b=='-'); break; //Indeterminado
                    default:  equiv = false;           
                }

                if (!equiv) break;
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
