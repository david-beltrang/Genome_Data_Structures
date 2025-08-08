#include "comando_functions.h"
#include <iostream>


// -------------------------------------------------------------------------
void mostrarAyudaGeneral() {
    cout << "Comandos disponibles:\n";
    cout << " - cargar nombre_archivo\n";
    cout << " - listar_secuencias\n";
    cout << " - histograma descripcion_secuencia\n";
    cout << " - es_subsecuencia subsecuencia\n";
    cout << " - enmascarar subsecuencia\n";
    cout << " - guardar nombre_archivo\n";
    cout << " - codificar nombre_archivo.fabin\n";
    cout << " - decodificar nombre_archivo.fabin\n";
    cout << " - ruta_mas_corta descripcion_secuencia i j x y\n";
    cout << " - base_remota descripcion_secuencia i j\n";
    cout << " - ayuda [comando]\n";
    cout << " - salir\n";
}

// -------------------------------------------------------------------------
// ANI ACA TIENES QUE PONER LA DESCRIPCIÓN QUE PUSO LA PROFE ACERCA DE CADA COMANDO
void mostrarAyudaEspecifica(const string& comando) {
    if (comando == "cargar") {
        cout << "Uso: cargar nombre_archivo\n";
    } else if (comando == "listar_secuencias") {
        cout << "Uso: listar_secuencias\n";
    } else if (comando == "histograma") {
        cout << "Uso: histograma descripcion_secuencia\n";
    } else if (comando == "es_subsecuencia") {
        cout << "Uso: es_subsecuencia subsecuencia\n";
    } else if (comando == "enmascarar") {
        cout << "Uso: enmascarar subsecuencia\n";
    } else if (comando == "guardar") {
        cout << "Uso: guardar nombre_archivo\n";
    } else if (comando == "codificar") {
        cout << "Uso: codificar nombre_archivo.fabin\n";
    } else if (comando == "decodificar") {
        cout << "Uso: decodificar nombre_archivo.fabin\n";
    } else if (comando == "ruta_mas_corta") {
        cout << "Uso: ruta_mas_corta descripcion_secuencia i j x y\n";
    } else if (comando == "base_remota") {
        cout << "Uso: base_remota descripcion_secuencia i j\n";
    } else {
        cout << "[ERROR] No hay ayuda disponible para el comando: " << comando << "\n";
    }
}
//----------------------------------------------------------------------------------------------
int comandoAEntero(const string& comando) {
    if (comando == "salir") return 1;
    else if (comando == "ayuda") return 2;
    else if (comando == "cargar") return 3;
    else if (comando == "listar_secuencias") return 4;
    else if (comando == "histograma") return 5;
    else if (comando == "es_subsecuencia") return 6;
    else if (comando == "enmascarar") return 7;
    else if (comando == "guardar") return 8;
    else if (comando == "codificar") return 9;
    else if (comando == "decodificar") return 10;
    else if (comando == "ruta_mas_corta") return 11;
    else if (comando == "base_remota") return 12;
    else return 0;
}

// eof - factorial_functions.cxx

