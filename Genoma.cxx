#include "Genoma.h"
#include "comando_functions.h"
#include <fstream>
#include <iostream>
#include <array>
#include <vector>
#include "Secuencia.h"

using namespace std;

// Busca una secuencia en memoria a partir de su descripción y devuelve la secuencia encontrada o vacia si no existe
const Secuencia& Genoma::buscarSecuencia(const string& desc) {
    for (vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it) {
        if (it->getDescripcion() == desc) return *it;
    }
    return Secuencia();  // Si no se encuentra, devuelve objeto vacío
}

// Carga secuencias desde un archivo en formato FASTA cada secuencia inicia con '>'
void Genoma::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream entrada(nombreArchivo);
    if (!entrada) { // Verifica que el archivo se pueda abrir
        cout << nombreArchivo << " no se encuentra o no puede leerse.\n";
        return;
    }

    string linea;
    Secuencia actual;
    secuencias.clear(); // Limpia memoria antes de cargar nuevas secuencias

    // Lee línea por línea el archivo
    while (getline(entrada, linea)) {
        if (linea.empty()) continue; // Ignora líneas vacías

        if (linea[0] == '>') {  
            // Si hay una secuencia previa, la guarda si es válida
            if (!actual.getDescripcion().empty() && !actual.getBases().empty()) {
                if (esBaseValida(actual.getBases())) {
                    secuencias.push_back(actual);
                }
            }
            // Inicia una nueva secuencia con la descripción (sin '>')
            actual = Secuencia(linea.substr(1));
        } else {
            // Agrega bases a la secuencia en construcción
            actual.agregarLinea(linea);
        }
    }

    // Guarda la última secuencia procesada
    if (!actual.getDescripcion().empty() && !actual.getBases().empty()) {
        if (esBaseValida(actual.getBases())) {
            secuencias.push_back(actual);
        }
    }

    entrada.close();

    // Muestra cuántas secuencias se cargaron
    int n = secuencias.size();
    if (n == 0) {
        cout << nombreArchivo << " no contiene ninguna secuencia.\n";
    } else if (n == 1) {
        cout << "1 secuencia cargada correctamente desde " << nombreArchivo << ".\n";
    } else {
        cout << n << " secuencias cargadas correctamente desde " << nombreArchivo << ".\n";
    }
}

// Guarda todas las secuencias en un archivo en formato FASTA.
void Genoma::guardarArchivo(const string& nombreArchivo) {
    if (secuencias.empty()) { // Si no hay nada en memoria, no guarda
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    // Verifica permisos de escritura
    ofstream salida(nombreArchivo);
    if (!salida) {
        cout << "Error guardando en " << nombreArchivo << ".\n";
        return;
    }

    // Recorre todas las secuencias y las escribe en formato FASTA
    for (std::vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it) {
        salida << ">" << it->getDescripcion() << "\n"; // Imprime el encabezado
        string bases = it->getBases();
        int ancho = it->getAnchoLinea(); // Número de bases por línea

        // Divide las bases en bloques de 'ancho' caracteres
        for (int i = 0; i < bases.length(); i += ancho) {
            salida << bases.substr(i, ancho) << "\n";
        }
    }

    salida.close();
    cout << "Las secuencias han sido guardadas en " << nombreArchivo << ".\n";
}

// Lista en pantalla todas las secuencias cargadas y su tamaño.
void Genoma::listar_secuencias() {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    cout << "Hay " << secuencias.size() << " secuencias cargadas en memoria:\n";

    // Recorre todas las secuencias, mostrando su descripción y tamaño
    for (vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it) {
        cout << "Secuencia " << it->getDescripcion();

        if (it->secuenciaCompleta()) { 
            // Si está completa, muestra el total de bases
            cout << " contiene " << it->getBases().length() << " bases.\n";
        } else {
            // Si no está completa, muestra un mínimo de bases contadas
            int conteoBase[256];
            cout << " contiene al menos " << it->contarBases(it->getBases(), conteoBase) << " bases.\n";
        }
    }
}

// Genera un histograma con la frecuencia de cada símbolo en la secuencia indicada.
void Genoma::histograma(const string& descripcion) {
    Secuencia seq = buscarSecuencia(descripcion);
    if (seq.getDescripcion().empty()) {
        cout << "Secuencia inválida.\n";
        return;
    }

    int conteo[256];
    seq.contarBases(seq.getBases(), conteo); // Cuenta cada carácter

    // Imprime cuantas veces aparece cada simbolo
    char simbolos[] = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};
    bool hayDatos = false;
    cout << "Histograma de la secuencia " << descripcion << ":\n";
    for (int i = 0; i < sizeof(simbolos) / sizeof(simbolos[0]); ++i) {
        
        // Imprime solo bases con conteo > 0
        if (conteo[simbolos[i]] > 0) {
            cout << simbolos[i] << " : " << conteo[simbolos[i]] << "\n";
            hayDatos = true;
        }
    }
    if (!hayDatos) {
        cout << "No hay bases con conteo mayor a 0 en esta secuencia.\n";
    }
}

// Revisa cuántas veces aparece una subsecuencia en todas las secuencias cargadas.
void Genoma::es_subsecuencia(const string& subsecuencia) {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    int totalApariciones = 0;
    for (vector<Secuencia>::const_iterator it = secuencias.begin(); it != secuencias.end(); ++it) {
        totalApariciones += it->contarSubsecuencia(subsecuencia); // Usa método de Secuencia
    }

    // Muestra el resultado al usuario
    if (totalApariciones > 0) {
        cout << "La subsecuencia dada se repite " << totalApariciones << " veces dentro de las secuencias cargadas en memoria.\n";
    } else {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria.\n";
    }
}

// Reemplaza todas las apariciones de una subsecuencia por otro
void Genoma::enmascarar(const string& subsecuencia) {
    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    int cantidad = 0;
    // Recorre cada secuencia y busca la subsecuencia repetidamente
    for (vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it) {
        int pos = 0;
        while ((pos = it->getBases().find(subsecuencia, pos)) != string::npos) {
            it->reemplazarSubsecuencia(subsecuencia, pos); // Reemplaza en esa posición
            cantidad++;
            pos += subsecuencia.length(); // Avanza para seguir buscando
        }
    }

    // Mensaje final con cuántas sustituciones se hicieron
    if (cantidad > 0) {
        cout << cantidad << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.\n";
    } else {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada.\n";
    }
}
