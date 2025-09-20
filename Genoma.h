#ifndef __GENOMA__H__
#define __GENOMA__H__
#include <string>
#include <vector>
#include "Secuencia.h"

// TAD Genoma
class Genoma {
private:
    vector<Secuencia> secuencias;       // Vector de secuencias
    const Secuencia& buscarSecuencia(const string& desc);
public:
    // Prototipos de métodos
    void cargarDesdeArchivo(const string& nombreArchivo);
    void guardarArchivo(const string& nombreArchivo);
    void listar_secuencias();
    void histograma(const string& descripcion);
    void es_subsecuencia(const string& subsecuencia);
    void enmascarar(const string& subsecuencia);
};

#endif // __GENOMA__H__