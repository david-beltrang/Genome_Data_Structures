#ifndef __GENOMA__H__
#define __GENOMA__H__
#include <string>
#include <vector>
#include "Secuencia.h"

using namespace std;

// TAD Genoma
class Genoma {
private:
    vector<Secuencia> secuencias;       // Vector de secuencias
    Secuencia buscarSecuencia(const string& desc);
public:
    // Prototipos de las Funciones
    void cargarDesdeArchivo(const string& nombreArchivo);
    void guardarArchivo(const string& nombreArchivo);
    void listar_secuencias();
    void histograma(const string& descripcion);
    void es_subsecuencia(const string& subsecuencia);
    void enmascarar(const string& subsecuencia);
    void calcularFrecuencia(vector <long long> &frecuencias, vector<char> &bases);
    string leerBitsDesempaquetados(ifstream& entrada, long long bytesToRead);
    void escribirBitsEmpaquetados(ofstream& salida, const string& bitString);
    void codificar(const string& nombreArchivo);
    void decodificar(const string& nombreArchivo);
    void ruta_mas_corta(const string& desc, int i, int j, int x, int y);
    void base_remota(const string& desc, int i, int j);

};

#endif // __GENOMA__H__
