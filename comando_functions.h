#ifndef __COMANDO_FUNCTIONS__H__
#define __COMANDO_FUNCTIONS__H__
#include <string>
using namespace std;

// Encabezado de funciones para el manejo de comandos
//A estas funciones se les envía el String por referencia para no crear copias inncesarias.
void mostrarAyudaGeneral();
void mostrarAyudaEspecifica(const string& comando);
int comandoAEntero(const string& comando);

#endif // __COMANDO_FUNCTIONS__H__

// eof - comando_functions.h