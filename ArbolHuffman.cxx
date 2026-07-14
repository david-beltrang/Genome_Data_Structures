#include "ArbolHuffman.h"
#include "NodoHuffman.h"
#include <vector>
using namespace std;

// Constructor: inicializa la raíz en nullptr
ArbolHuffman::ArbolHuffman() : raiz(nullptr) {}

// Destructor: libera toda la memoria del árbol
ArbolHuffman::~ArbolHuffman() {
    liberarArbol(raiz);
}

// Función auxiliar recursiva para liberar memoria
void ArbolHuffman::liberarArbol(NodoHuffman* nodo) {
    if (nodo == nullptr) {
        return;  // Caso base: nodo vacío
    }
    
    // Primero libera los hijos (post-orden)
    liberarArbol(nodo->izquierda);
    liberarArbol(nodo->derecha);
    
    // Luego libera el nodo actual
    delete nodo;
}

// Inserta un nodo manteniendo orden ascendente por frecuencia
void ArbolHuffman:: insertarOrdenado(vector<NodoHuffman*>& nodos, NodoHuffman* nuevo) {
    int pos = 0;
    // Encuentra la posición correcta para insertar el nodo
    while (pos < nodos.size() && nodos[pos]->frecuencia < nuevo->frecuencia) {
        pos++;
    }

    // Inserta el nodo en la posición encontrada
    nodos.insert(nodos.begin() + pos, nuevo);
}

// Construye la raíz del árbol
void ArbolHuffman::fijarRaiz(const vector<char>& simbolos, const vector<long long>& frecuencias) {
    // Liberar árbol anterior si existe
    liberarArbol(raiz);
    raiz = nullptr;
    
    vector<NodoHuffman*> nodos;

    // Crear nodos hoja para cada símbolo y frecuencia
    for (int i = 0; i < simbolos.size(); ++i) {
        // Crea un nuevo nodo hoja para cada símbolo y su frecuencia 
        NodoHuffman* nuevo = new NodoHuffman(simbolos[i], frecuencias[i]);

        // Inserta el nodo en el vector ordenado
        insertarOrdenado(nodos, nuevo);
    }

    // Construye el árbol combinando los nodos de menor frecuencia
    while (nodos.size() > 1) {
        // Obtiene los dos nodos primros nodos
        NodoHuffman* izq = nodos[0];
        NodoHuffman* der = nodos[1];

        // Crea un nuevo nodo padre con la suma de las frecuencias
        NodoHuffman* nuevo = new NodoHuffman(izq->frecuencia + der->frecuencia, izq, der);
        
        // Elimina los dos nodos ya usados
        nodos.erase(nodos.begin());
        nodos.erase(nodos.begin());

        // Inserta el nuevo nodo en el vector manteniendo el orden
        insertarOrdenado(nodos, nuevo);
    }

    // El último nodo restante es la raíz del árbol
    raiz = nodos[0];
}

// Generar los códigos binarios
void ArbolHuffman::generarCodigosRec(NodoHuffman* nodo, string codigo, vector<char>& simbolos, vector<string>& codigos) {
    // Caso base: si el nodo es nulo, retorna
    if (!nodo)
        return;
    
    // Si es un nodo hoja, guarda el símbolo y su código
    if (nodo->esHoja()) {
        simbolos.push_back(nodo->simbolo);
        codigos.push_back(codigo);
    // Si no es hoja, recorre los hijos izquierdo y derecho
    } else {
        generarCodigosRec(nodo->izquierda, codigo + "0", simbolos, codigos);
        generarCodigosRec(nodo->derecha, codigo + "1", simbolos, codigos);
    }
}

// Genera los códigos binarios de los símbolos y los guarda en el vector de strings
void ArbolHuffman::generarCodigos(vector<char>& simbolos, vector<string>& codigos) {
    // Llama la funcion recurrente
    generarCodigosRec(raiz, "", simbolos, codigos);
}

// Devuelve la raíz del árbol
NodoHuffman* ArbolHuffman::getRaiz() {
    return raiz;
}

// Decodifica una secuencia binaria usando el árbol de Huffman
string ArbolHuffman::decodificar(const string& codigoBinario, long long length) {
    // Revisión de casos límite
    if (!raiz || codigoBinario.empty() || length <= 0)
        return "";
    
    string secuenciaDecodificada = "";
    NodoHuffman* current = raiz;

    // Iterar sobre los bits
    for (char bit : codigoBinario) {
        
        // Detenerse cuando ya se han decodificado 'length' símbolos
        if (secuenciaDecodificada.length() >= length) {
            break; 
        }

        // Recorrer el árbol: 0 a la izquierda, 1 a la derecha
        if (bit == '0') {
            current = current->izquierda;
        } else if (bit == '1') {
            current = current->derecha;
        } else {
            // Ignorar caracteres no binarios
            continue; 
        }

        // Si current es un nodo hoja, se ha decodificado una base
        if (current && current->esHoja()) { 
            secuenciaDecodificada += current->simbolo; // Añadir el símbolo decodificado
            current = raiz; // Volver a la raíz para empezar a decodificar el siguiente símbolo
        }
        
        // verificar si el último símbolo decodificado fue el que completó la longitud 'length'
        if (secuenciaDecodificada.length() >= length) {
            break; 
        }
    }
    
    // Devolver exactamente 'length' bases, cortando cualquier exceso
    if (secuenciaDecodificada.length() > length) {
        return secuenciaDecodificada.substr(0, length);
    }
    
    return secuenciaDecodificada;
}