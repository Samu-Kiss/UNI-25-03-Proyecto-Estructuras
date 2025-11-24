#ifndef SISTEMA_H
#define SISTEMA_H

#include <cstdint>
#include <string>
#include <vector>

#include "ArbolHuffman.h"
#include "genoma.h"


class Sistema {
 private:
  // Atributos
  Genoma genoma;

  // Metodos privados
  void inicializar();
  void bienvenida();
  void procesarComandos();
  void limpiarPantalla();
  void ayuda(const std::string& param);

  // Operaciones
  bool cargar(const std::string& nombre_archivo);
  void guardar(const std::string& nombre_archivo);
  void codificar(const std::string& nombre_archivo);
  void decodificar(const std::string& nombre_archivo);
  void salir();

  // Funciones de ayuda
  int numParams(const std::string& input);
  bool parsePositiveInt(const std::string& s, int& out);
  void calcularFrecuencias(const std::string& texto,
                           std::uint64_t (&frecuencias_array)[256],
                           std::uint16_t& num_caracteres_unicos);

 public:
  // Constructor
  Sistema();

  // Método público para iniciar la aplicación
  void iniciarConsola();
};

#endif  // SISTEMA_H
