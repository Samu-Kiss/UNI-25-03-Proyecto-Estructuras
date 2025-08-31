#include "./termcolor.hpp"
#include "./secuencia.h"
#include "./genoma.h"
#include <iostream>
#include <vector>
#include <string>

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

    if (secuencias.empty()){
        cout << "No hay secuencias cargadas en memoria" << endl;
        return false;
    }

    size_t tam = strlen(subsecuencia);
	
    if (tam == 0){
        cout << "La subsecuencia no existe dentro de las secuencias cargadas en memoria" << endl;
        return false;
    }

    int total = 0;

    for (size_t s = 0; s < secuencias.size(); s++){
		
        const vector<char>& scs = secuencias[s].bases;

        for (size_t i = 0; i + tam <= scs.size(); i++){
			
            size_t k = 0;
			
            while (k < tam && scs[i + k] == subsecuencia[k]) {
				k++;
			}
			
            if (k == tam) {
                total++;
            }
			
        }
    }

    if (total == 0){
        cout << "La subsecuencia no existe dentro de las secuencias cargadas en memoria" << endl;
        return false;
    } else {
        cout << "La subsecuencia dada se repite " << total << " dentro de las secuencias cargadas en memoria" << endl;
        return true;
    }
    
}

//Enmascarar(subsecuencia) -> void
void Genoma::Enmascarar(const char* subsecuencia){
    // TODO: Implementación de la enmascaración

    // Posibles estados:
    // No hay secuencias cargadas
    // No se enmascararon subsecuencias
    // Varias subsecuencias enmascaradas
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
