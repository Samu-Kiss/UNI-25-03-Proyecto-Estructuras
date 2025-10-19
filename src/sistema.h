#ifndef SISTEMA_H
#define SISTEMA_H

#include "genoma.h"
#include <string>

class Sistema {
private:
    // Atributos
    Genoma genoma;

    // Metodos privados
    void inicializar();
    void bienvenida();
    void procesarComandos();
    void limpiarPantalla();
    void ayuda(const std::string &param);
    
    // Operaciones
    bool cargar(const std::string &nombre_archivo);
    void guardar(const std::string &nombre_archivo);
    void codificar(const std::string &nombre_archivo);
    void decodificar(const std::string &nombre_archivo);
    void salir();

    // Funciones de ayuda
    int numParams(const std::string &input);
    bool parsePositiveInt(const std::string &s, int &out);

public:
    // Constructor
    Sistema();

    // Método público para iniciar la aplicación
    void iniciarConsola();
};

#endif // SISTEMA_H