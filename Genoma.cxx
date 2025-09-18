#include "Genoma.h"
#include "comando_functions.h"
#include <fstream>
#include <iostream>
#include <array>
#include <vector>

// Implementación de TAD Genoma
Secuencia Genoma::buscarSecuencia(const string& desc) {
    for (vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it) {
        if (it->getDescripcion() == desc) return *it;
    }
    return Secuencia();  // Vacía si no existe
}

void Genoma::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cout << nombreArchivo << " no se encuentra o no puede leerse.\n";
        return;
    }

    string linea;
    Secuencia actual;
    secuencias.clear();

    while (getline(entrada, linea)) {
        if (linea.empty()) continue;

        if (linea[0] == '>') {
            if (!actual.getDescripcion().empty() && !actual.getBases().empty()) {
                if (esBaseValida(actual.getBases())) {
                    secuencias.push_back(actual);
                }
            }
            // Crear nuevo objeto
            Secuencia nuevo(linea.substr(1));
            actual = nuevo;
        } else {
            actual.agregarLinea(linea);
        }
    }

    if (!actual.getDescripcion().empty() && !actual.getBases().empty()) {
        if (esBaseValida(actual.getBases())) {
            secuencias.push_back(actual);
        }
    }

    entrada.close();
    int n = secuencias.size();
    if (n == 0) {
        cout << nombreArchivo << " no contiene ninguna secuencia.\n";
    } else if (n == 1) {
        cout << "1 secuencia cargada correctamente desde " << nombreArchivo << ".\n";
    } else {
        cout << n << " secuencias cargadas correctamente desde " << nombreArchivo << ".\n";
    }
}

void Genoma::guardarArchivo(string& nombreArchivo) {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    ofstream salida(nombreArchivo);
    if (!salida) {
        cout << "Error guardando en " << nombreArchivo << ".\n";
        return;
    }

    // Imprimir en el archivo cada una de las secuencias
    for (std::vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it) {
        // Imprimir el nombre de la secuencia
        salida << ">" << it->getDescripcion() << "\n";
        string bases = it->getBases();
        int ancho = it->getAnchoLinea();

        // Imprimir la secuencia en bloques de n ancho de linea en el archivo
        for (int i = 0; i < bases.length(); i += ancho) {
            salida << bases.substr(i, ancho) << "\n";
        }
    }

    // Cierra el archivo
    salida.close();
    cout << "Las secuencias han sido guardadas en " << nombreArchivo << ".\n";
}

void Genoma::listar_secuencias() {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    // Cuenta la cantidad de secuencias
    int n = secuencias.size();
    cout << "Hay " << n << " secuencias cargadas en memoria:\n";

    for (vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it) {
        cout << "Secuencia " << it->getDescripcion();

        if (it->secuenciaCompleta()) {
            cout << " contiene " << it->getBases().length() << " bases.\n";
        } else {
            int conteoBase[256];
            cout << " contiene al menos " << it->contarBases(it->getBases(), conteoBase) << " bases.\n";
        }
    }
}

void Genoma::histograma(const string& descripcion) {
    Secuencia seq = buscarSecuencia(descripcion);
    if (seq.getDescripcion().empty()) {
        cout << "Secuencia inválida.\n";
        return;
    }

    int conteo[256];
    seq.contarBases(seq.getBases(), conteo);


    char simbolos[] = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M',
                       'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};
    for (int i = 0; i < sizeof(simbolos) / sizeof(simbolos[0]); ++i) {
        cout << simbolos[i] << " : " << conteo[simbolos[i]] << "\n";
    }
}

void Genoma::es_subsecuencia(const string& subsecuencia) {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    int totalApariciones = 0;
    for (vector<Secuencia>::const_iterator it = secuencias.begin(); it != secuencias.end(); ++it) {
        totalApariciones += it->contarSubsecuencia(subsecuencia); // Delegar búsqueda
    }

    if (totalApariciones > 0) {
        cout << "La subsecuencia dada se repite " << totalApariciones << " veces dentro de las secuencias cargadas en memoria.\n";
    } else {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria.\n";
    }
}

void Genoma::enmascarar(const string& subsecuencia) {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    int cantidad = 0;
    for (vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it) {
        int pos = 0;
        while ((pos = it->getBases().find(subsecuencia, pos)) != string::npos) {
            it->reemplazarSubsecuencia(subsecuencia, pos);
            cantidad++;
            pos += subsecuencia.length();
        }
    }

    if (cantidad > 0) {
        cout << cantidad << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.\n";
    } else {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada.\n";
    }
}