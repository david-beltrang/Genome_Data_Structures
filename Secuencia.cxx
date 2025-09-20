#include "Secuencia.h"
#include <string>

using namespace std;

// Constructor por defecto,inicializa anchoLinea en 0
Secuencia::Secuencia() : anchoLinea(0) {}

// Constructor que recibe una descripción
Secuencia::Secuencia(string desc) {
    descripcion = desc;  
    bases = "";         // inicializa la cadena de bases vacía
    anchoLinea = 0;     // ancho de línea inicializado en 0
}

// Setter para la descripción
void Secuencia::setDescripcion(string& desc) {
    descripcion = desc; // asigna la descripción
}

// Getter para obtener la descripción actual
string Secuencia::getDescripcion() {
    return descripcion;
}

// Getter para obtener la cadena de bases
string Secuencia::getBases() {
    return bases;
}

// Getter para obtener el ancho de línea actual
int Secuencia::getAnchoLinea() {
    return anchoLinea;
}

// Agrega una línea de bases a la secuencia
void Secuencia::agregarLinea(string& linea) {
    // Si el anchoLinea es 0 (primera línea), se asigna el largo de la línea actual
    if (anchoLinea == 0) {
        anchoLinea = linea.length();
    }
    // Se concatena la línea a la cadena de bases existentes
    bases += linea;
}

// Verifica si la secuencia está completa (sin guiones '-')
bool Secuencia::secuenciaCompleta() {
    // Recorre cada base en la cadena bases
    for (char base : bases) {
        if (base == '-')  // Si encuentra un guion, no está completa
            return false;
    }
    return true; // Si no hay guiones, la secuencia está completa
}

// Cuenta las bases que aparecen en la cadena bases pasada por parámetro y guarda el conteo en el arreglo conteoBase de tamaño 256 para índice ASCII
int Secuencia::contarBases(const string& bases, int (&conteoBase)[256]) {
    // Inicializa el conteo en 0 para todos los caracteres
    for (int i = 0; i < 256; i++) 
        conteoBase[i] = 0;

    // Recorre cada base en la cadena bases
    for(char base : bases){
        // Incrementa el contador correspondiente según el carácter base
        switch (base) {
            case 'A': conteoBase['A']++; break;
            case 'C': conteoBase['C']++; break;
            case 'G': conteoBase['G']++; break;
            case 'T': conteoBase['T']++; break; 
            case 'U': conteoBase['U']++; break;
            case 'R': conteoBase['R']++; break;
            case 'Y': conteoBase['Y']++; break;
            case 'K': conteoBase['K']++; break;
            case 'M': conteoBase['M']++; break;
            case 'S': conteoBase['S']++; break;
            case 'W': conteoBase['W']++; break;
            case 'B': conteoBase['B']++; break;
            case 'D': conteoBase['D']++; break;
            case 'H': conteoBase['H']++; break;
            case 'V': conteoBase['V']++; break;
            case 'N': conteoBase['N']++; break;
            case 'X': conteoBase['X']++; break;
            case '-': conteoBase['-']++; break;
            default: break; // Ignora otros demás caracteres
        }
    }
    // Retorna la suma de los conteos de bases que se consideran válidas
    return conteoBase['A'] + conteoBase['C'] + conteoBase['G'] + conteoBase['T'] + conteoBase['U'] + 
           conteoBase['R'] + conteoBase['Y'] + conteoBase['K'] + conteoBase['M'] + conteoBase['S'] + 
           conteoBase['W'] + conteoBase['B'] + conteoBase['D'] + conteoBase['H'] + conteoBase['V'] + 
           conteoBase['N'] + conteoBase['X'];
}

// Cuenta cuántas veces aparece la subsecuencia 'sub' dentro de la secuencia actual (bases)
int Secuencia::contarSubsecuencia(const string& sub) const {
    int conteo = 0;
    size_t pos = 0;
    // Busca la subsecuencia 'sub' dentro de las bases
    while ((pos = bases.find(sub, pos)) != string::npos) {
        conteo++;
        pos += 1;
    }
    return conteo; // Retorna total de ocurrencias encontradas
}

// Reemplaza la subsecuencia 'sub' que empieza en la posición 'pos' con 'X's
void Secuencia::reemplazarSubsecuencia(const string& sub, int pos) {
    // Itera desde la posición inicial hasta la longitud de la subsecuencia
    for (size_t i = pos; i < pos + sub.length(); ++i) {
        bases[i] = 'X';  // Reemplaza cada base por 'X'
    }
}
