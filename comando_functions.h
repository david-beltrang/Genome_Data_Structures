#ifndef __COMANDO_FUNCTIONS__H__
#define __COMANDO_FUNCTIONS__H__
#include <string>

using namespace std;

// Prototipos de funciones auxiliares
void mostrarAyudaGeneral();
void mostrarAyudaEspecifica(const string& comando);
int comandoAEntero(const string& comando);
bool esBaseValida(const string& base);

#endif // __COMANDO_FUNCTIONS__H__