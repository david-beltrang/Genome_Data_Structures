#include <iostream>
#include <string>
#include <sstream>
#include "comando_functions.h"

using namespace std;

int main() {
    string linea;
    cout << "Sistema FASTA interactivo - Entrega 0\n";
    while (true) {
        cout << "$ ";
        getline(cin, linea);
        if (linea.empty()) continue;

        // Utilizamos un istringstream para poder leer linea y Tokenizarla (separarla por palabras)
        istringstream lineaTokenizada(linea);
        string comando;
        // Leemos el primer token de la linea, que es el comando
        lineaTokenizada >> comando;

        switch (comandoAEntero(comando)) {
            case 1: // salir
                return 0;

            case 2: { // ayuda
                string subcomando, extra;
                // Si el comando es ayuda, leer el segundo token (Subcomando del cual se quiere ayuda)
                if (lineaTokenizada >> subcomando) {
                    if (lineaTokenizada >> extra) {
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
                // Si el comando es cargar, leer el segundo token (nombre del archivo)
                if (lineaTokenizada >> archivo) {
                    if (lineaTokenizada >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues del archivo.\n";
                    } else {
                        cout << "[OK] comando cargar reconocido con archivo: " << archivo << endl;
                    }
                } else {
                    cout << "[ERROR] Uso: cargar nombre_archivo\n";
                }
                break;
            }

            case 4: // listar_secuencias (sin argumentos)
            {
                string extra;
                // Si el comando es listar_secuencias, no debe haber argumentos adicionales
                if (lineaTokenizada >> extra) {
                    cout << "[ERROR] Este comando no recibe argumentos adicionales.\n";
                } else {
                    cout << "[OK] comando listar_secuencias reconocido\n";
                }
                break;
            }

            case 5: { // histograma
                string descripcion, extra;
                // Si el comando es histograma, leer el segundo token (descripcion de la secuencia)
                if (lineaTokenizada >> descripcion) {
                    if (lineaTokenizada >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues de la descripcion.\n";
                    } else {
                        cout << "[OK] comando histograma reconocido con descripcion: " << descripcion << endl;
                    }
                } else {
                    cout << "[ERROR] Uso: histograma descripcion_secuencia\n";
                }
                break;
            }

            case 6: { // es_subsecuencia
                string sub, extra;
                // Si el comando es es_subsecuencia, leer el segundo token (subsecuencia)
                if (lineaTokenizada >> sub) {
                    if (lineaTokenizada >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues de la subsecuencia.\n";
                    } else {
                        cout << "[OK] comando es_subsecuencia reconocido con subsecuencia: " << sub << endl;
                    }
                } else {
                    cout << "[ERROR] Uso: es_subsecuencia subsecuencia\n";
                }
                break;
            }

            case 7: { // enmascarar
                string sub, extra;
                // Si el comando es enmascarar, leer el segundo token (subsecuencia)
                if (lineaTokenizada >> sub) {
                    if (lineaTokenizada >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues de la subsecuencia.\n";
                    } else {
                        cout << "[OK] comando enmascarar reconocido con subsecuencia: " << sub << endl;
                    }
                } else {
                    cout << "[ERROR] Uso: enmascarar subsecuencia\n";
                }
                break;
            }

            case 8: { // guardar
                string archivo, extra;
                // Si el comando es guardar, leer el segundo token (nombre del archivo)
                if (lineaTokenizada >> archivo) {
                    if (lineaTokenizada >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues del archivo.\n";
                    } else {
                        cout << "[OK] comando guardar reconocido con archivo: " << archivo << endl;
                    }
                } else {
                    cout << "[ERROR] Uso: guardar nombre_archivo\n";
                }
                break;
            }

            case 9: { // codificar
                string archivo, extra;
                // Si el comando es codificar, leer el segundo token (nombre del archivo)
                if (lineaTokenizada >> archivo) {
                    if (lineaTokenizada >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues del archivo.\n";
                    } else {
                        cout << "[OK] comando codificar reconocido con archivo: " << archivo << endl;
                    }
                } else {
                    cout << "[ERROR] Uso: codificar nombre_archivo.fabin\n";
                }
                break;
            }

            case 10: { // decodificar
                string archivo, extra;
                // Si el comando es decodificar, leer el segundo token (nombre del archivo)
                if (lineaTokenizada >> archivo) {
                    if (lineaTokenizada >> extra) {
                        cout << "[ERROR] Ha digitado palabras demas despues del archivo.\n";
                    } else {
                        cout << "[OK] comando decodificar reconocido con archivo: " << archivo << endl;
                    }
                } else {
                    cout << "[ERROR] Uso: decodificar nombre_archivo.fabin\n";
                }
                break;
            }

            case 11: { // ruta_mas_corta
                string descripcion, extra;
                int i, j, x, y;
                // Si el comando es ruta_mas_corta, leer el segundo token (descripcion de la secuencia), tercer token (i), cuarto (j), quinto (x) y sexto (y)
                if (lineaTokenizada >> descripcion >> i >> j >> x >> y) {
                    if (lineaTokenizada >> extra) {
                        cout << "[ERROR] Ha digitado argumentos demas, solo se permite: descripcion_secuencia i j x y.\n";
                    } else {
                        cout << "[OK] comando ruta_mas_corta reconocido con parametros: "
                             << descripcion << " " << i << " " << j << " " << x << " " << y << endl;
                    }
                } else {
                    cout << "[ERROR] Uso: ruta_mas_corta descripcion_secuencia i j x y\n";
                }
                break;
            }

            case 12: { // base_remota
                string descripcion, extra;
                int i, j;
                // Si el comando es base_remota, leer el segundo token (descripcion de la secuencia), tercer token (i) y cuarto (j)
                if (lineaTokenizada >> descripcion >> i >> j) {
                    if (lineaTokenizada >> extra) {
                        cout << "[ERROR] Ha digitado argumentos demas, solo se permite: descripcion_secuencia i j.\n";
                    } else {
                        cout << "[OK] comando base_remota reconocido con parametros: "
                             << descripcion << " " << i << " " << j << endl;
                    }
                } else {
                    cout << "[ERROR] Uso: base_remota descripcion_secuencia i j\n";
                }
                break;
            }
            // Si no se reconoce el comando, muestra un mensaje de error
            default:
                cout << "[ERROR] Comando no reconocido\n";
        }
    }
    return 0;
}
