#ifndef __COMANDO_FUNCTIONS__H__
#define __COMANDO_FUNCTIONS__H__

#include <string>
using namespace std;

// Encabezado de funciones para el manejo de comandos en el sistema FASTA

// Función para mostrar la ayuda general del sistema (Comandos disponibles)
void mostrarAyudaGeneral();

// Función para mostrar la ayuda específica de un comando (Mostrar que hace cada uno)
void mostrarAyudaEspecifica(const string& comando);

// Función que convierte un comando de tipo string a un número entero para poder implementar un switch
int comandoAEntero(const string& comando);

#endif // __COMANDO_FUNCTIONS__H__