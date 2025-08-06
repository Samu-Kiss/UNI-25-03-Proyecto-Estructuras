#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>

using namespace std;

// Declaraciones de funciones de comandos
void comandoSalida();
void comandoAyuda();
bool valCargar(string command);
bool valListar(string command);
bool valHistograma(string command);
bool valEsSubsecuencia(string command);
bool valEnmascarar(string command);
bool valGuardar(string command);
bool valCodificar(string command);
bool valDecodificar(string command);
bool valRutaMasCorta(string command);
bool valBaseRemota(string command);

#endif // COMMANDS_H