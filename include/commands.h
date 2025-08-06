#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>

// Declaraciones de funciones de comandos
void comandoSalida();
void comandoAyuda();
bool valCargar(std::string command);
bool valListar(std::string command);
bool valHistograma(std::string command);
bool valEsSubsecuencia(std::string command);
bool valEnmascarar(std::string command);
bool valGuardar(std::string command);
bool valCodificar(std::string command);
bool valDecodificar(std::string command);
bool valRutaMasCorta(std::string command);
bool valBaseRemota(std::string command);

#endif // COMMANDS_H