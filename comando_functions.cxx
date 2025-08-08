#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;



// Muestra la ayuda general con todos los comandos
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

// Muestra la ayuda específica para cada comando
void mostrarAyudaEspecifica(const string& comando) {
    if (comando == "cargar") {
        cout << "Uso: cargar nombre_archivo\n"
             << "Función: Carga las secuencias desde un archivo especificado.\n";
    } else if (comando == "listar_secuencias") {
        cout << "Uso: listar_secuencias\n"
             << "Función: Muestra todas las secuencias cargadas en el sistema.\n";
    } else if (comando == "histograma") {
        cout << "Uso: histograma descripcion_secuencia\n"
             << "Función: Genera un histograma de frecuencias de las bases en una secuencia.\n";
    } else if (comando == "es_subsecuencia") {
        cout << "Uso: es_subsecuencia subsecuencia\n"
             << "Función: Verifica si una subsecuencia está presente en las secuencias cargadas.\n";
    } else if (comando == "enmascarar") {
        cout << "Uso: enmascarar subsecuencia\n"
             << "Función: Enmascara las subsecuencias encontradas en las secuencias cargadas.\n";
    } else if (comando == "guardar") {
        cout << "Uso: guardar nombre_archivo\n"
             << "Función: Guarda las secuencias en el archivo especificado.\n";
    } else if (comando == "codificar") {
        cout << "Uso: codificar nombre_archivo.fabin\n"
             << "Función: Codifica las secuencias en formato binario comprimido.\n";
    } else if (comando == "decodificar") {
        cout << "Uso: decodificar nombre_archivo.fabin\n"
             << "Función: Decodifica un archivo binario comprimido con las secuencias.\n";
    } else if (comando == "ruta_mas_corta") {
        cout << "Uso: ruta_mas_corta descripcion_secuencia i j x y\n"
             << "Función: Calcula la ruta más corta entre dos puntos en una secuencia.\n";
    } else if (comando == "base_remota") {
        cout << "Uso: base_remota descripcion_secuencia i j\n"
             << "Función: Encuentra la base más lejana desde una posición dada en la secuencia.\n";
    } else {
        cout << "[ERROR] No hay ayuda disponible para el comando: " << comando << "\n";
    }
}

// Convierte el comando que esta en String a un Int para manejarlo mas facil
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
    else return 0; // Comando no reconocido
}

// Funcion principal
int main() {
    string linea;
    cout << "Sistema FASTA interactivo - Entrega 0\n";
    mostrarAyudaGeneral();

    // Bucle principal hasta que el usuario se salga
    while (true) {
        cout << "$ ";
        getline(cin, linea); // Leemos la línea de comandos
	// Si la línea está vacía, continuar
        if (linea.empty()) continue;

        istringstream iss(linea);
        string comando;
	// Extraer la primera parte de la linea
        iss >> comando;

        // Convertir el comando a un numero para usar el switch
        int comando_int = comandoAEntero(comando);

        // Implementar un switch para poder manejar los comandos mas facil
        switch (comando_int) {
            case 1: // salir
                return 0;
            case 2: { // ayuda
                string subcomando;
                if (iss >> subcomando) {
                    mostrarAyudaEspecifica(subcomando); // Muestra ayuda de un comando específico
                } else {
                    mostrarAyudaGeneral(); // Muestra ayuda general
                }
                break;
            }
            case 3: { // cargar
                string archivo;
                if (iss >> archivo) {
                    cout << "[OK] comando cargar reconocido con archivo: " << archivo << endl;
                } else {
                    cout << "[ERROR] Uso: cargar nombre_archivo\n";
                }
                break;
            }
            case 4: { // listar_secuencias
                cout << "[OK] comando listar_secuencias reconocido\n";
                break;
            }
            case 5: { // histograma
                string descripcion;
                if (iss >> descripcion) {
                    cout << "[OK] comando histograma reconocido con descripción: " << descripcion << endl;
                } else {
                    cout << "[ERROR] Uso: histograma descripcion_secuencia\n";
                }
                break;
            }
            case 6: { // es_subsecuencia
                string sub;
                if (iss >> sub) {
                    cout << "[OK] comando es_subsecuencia reconocido con subsecuencia: " << sub << endl;
                } else {
                    cout << "[ERROR] Uso: es_subsecuencia subsecuencia\n";
                }
                break;
            }
            case 7: { // enmascarar
                string sub;
                if (iss >> sub) {
                    cout << "[OK] comando enmascarar reconocido con subsecuencia: " << sub << endl;
                } else {
                    cout << "[ERROR] Uso: enmascarar subsecuencia\n";
                }
                break;
            }
            case 8: { // guardar
                string archivo;
                if (iss >> archivo) {
                    cout << "[OK] comando guardar reconocido con archivo: " << archivo << endl;
                } else {
                    cout << "[ERROR] Uso: guardar nombre_archivo\n";
                }
                break;
            }
            case 9: { // codificar
                string archivo;
                if (iss >> archivo) {
                    cout << "[OK] comando codificar reconocido con archivo: " << archivo << endl;
                } else {
                    cout << "[ERROR] Uso: codificar nombre_archivo.fabin\n";
                }
                break;
            }
            case 10: { // decodificar
                string archivo;
                if (iss >> archivo) {
                    cout << "[OK] comando decodificar reconocido con archivo: " << archivo << endl;
                } else {
                    cout << "[ERROR] Uso: decodificar nombre_archivo.fabin\n";
                }
                break;
            }
            case 11: { // ruta_mas_corta
                string descripcion;
                int i, j, x, y;
                if (iss >> descripcion >> i >> j >> x >> y) {
                    cout << "[OK] comando ruta_mas_corta reconocido con parámetros: " << descripcion << " " << i << " " << j << " " << x << " " << y << endl;
                } else {
                    cout << "[ERROR] Uso: ruta_mas_corta descripcion_secuencia i j x y\n";
                }
                break;
            }
            case 12: { // base_remota
                string descripcion;
                int i, j;
                if (iss >> descripcion >> i >> j) {
                    cout << "[OK] comando base_remota reconocido con parámetros: " << descripcion << " " << i << " " << j << endl;
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
