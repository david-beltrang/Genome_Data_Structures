#include <iostream>
#include <string>
#include <sstream>
#include "Genoma.h"
#include "comando_functions.h"

using namespace std;

int main() {
    Genoma genoma; // Declarar Genoma
    string linea;
    cout << "Sistema FASTA interactivo - Entrega 1\n";
    while (true) {
        cout << "$ ";
        getline(cin, linea);
        if (linea.empty()) continue;

        istringstream iss(linea);
        string comando;
        iss >> comando;

        switch (comandoAEntero(comando)) {
            case 1: // salir
                return 0;

            case 2: { // ayuda
                string subcomando, extra;
                if (iss >> subcomando) {
                    if (iss >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas para el comando ayuda.\n";
                    } else {
                        mostrarAyudaEspecifica(subcomando);
                    }
                } else {
                    mostrarAyudaGeneral();
                }
                break;
            }

            case 3: { // cargar
                string archivo, extra;
                if (iss >> archivo) {
                    if (iss >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues del archivo.\n";
                    } else {
                        genoma.cargarDesdeArchivo(archivo);
                    }
                } else {
                    cout << "[ERROR] Uso: cargar nombre_archivo\n";
                }
                break;
            }

            case 4: // listar_secuencias (sin argumentos)
            {
                string extra;
                if (iss >> extra) {
                    cout << "[ERROR] Este comando no recibe argumentos adicionales.\n";
                } else {
                    genoma.listar_secuencias();
                }
                break;
            }

            case 5: { // histograma
                string descripcion, extra;
                if (iss >> descripcion) {
                    if (iss >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues de la descripcion.\n";
                    } else {
                        genoma.histograma(descripcion);
                    }
                } else {
                    cout << "[ERROR] Uso: histograma descripcion_secuencia\n";
                }
                break;
            }

            case 6: { // es_subsecuencia
                string sub, extra;
                if (iss >> sub) {
                    if (iss >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues de la subsecuencia.\n";
                    } else {
                        genoma.es_subsecuencia(sub);
                    }
                } else {
                    cout << "[ERROR] Uso: es_subsecuencia subsecuencia\n";
                }
                break;
            }

            case 7: { // enmascarar
                string sub, extra;
                if (iss >> sub) {
                    if (iss >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues de la subsecuencia.\n";
                    } else {
                        genoma.enmascarar(sub);
                    }
                } else {
                    cout << "[ERROR] Uso: enmascarar subsecuencia\n";
                }
                break;
            }

            case 8: { // guardar
                string archivo, extra;
                if (iss >> archivo) {
                    if (iss >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues del archivo.\n";
                    } else {
                        genoma.guardarArchivo(archivo);
                    }
                } else {
                    cout << "[ERROR] Uso: guardar nombre_archivo\n";
                }
                break;
            }

            case 9: { // codificar
                string archivo, extra;
                if (iss >> archivo) {
                    if (iss >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues del archivo.\n";
                    } else {
                        // TODO: Codificar archivo
                    }
                } else {
                    cout << "[ERROR] Uso: codificar nombre_archivo.fabin\n";
                }
                break;
            }

            case 10: { // decodificar
                string archivo, extra;
                if (iss >> archivo) {
                    if (iss >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues del archivo.\n";
                    } else {
                        // TODO: Decodificar archivo
                    }
                } else {
                    cout << "[ERROR] Uso: decodificar nombre_archivo.fabin\n";
                }
                break;
            }

            case 11: { // ruta_mas_corta
                string descripcion, extra;
                int i, j, x, y;
                if (iss >> descripcion >> i >> j >> x >> y) {
                    if (iss >> extra) {
                        cout << "[ERROR] Ha digitado argumentos demas, solo se permite: descripcion_secuencia i j x y.\n";
                    } else {
                        // TODO: Ruta mas corta
                    }
                } else {
                    cout << "[ERROR] Uso: ruta_mas_corta descripcion_secuencia i j x y\n";
                }
                break;
            }

            case 12: { // base_remota
                string descripcion, extra;
                int i, j;
                if (iss >> descripcion >> i >> j) {
                    if (iss >> extra) {
                        cout << "[ERROR] Ha digitado argumentos demas, solo se permite: descripcion_secuencia i j.\n";
                    } else {
                        // TODO: Base remota
                    }
                } else {
                    cout << "[ERROR] Uso: base_remota descripcion_secuencia i j\n";
                }
                break;
            }

            default:
                cout << "[ERROR] Comando no reconocido\n";
        }
    }
    return 0;
}

// eof - test_comando.cxx