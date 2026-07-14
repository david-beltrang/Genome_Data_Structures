#ifndef ARBOL_HUFFMAN_H
#define ARBOL_HUFFMAN_H

#include <vector>
#include <string>
#include "NodoHuffman.h"

using namespace std;

class ArbolHuffman {
private:
    NodoHuffman* raiz;
    void generarCodigosRec(NodoHuffman* nodo, string codigo, vector<char>& simbolos, vector<string>& codigos);
    void insertarOrdenado(vector<NodoHuffman*>& nodos, NodoHuffman* nuevo);
    void liberarArbol(NodoHuffman* nodo);

public:
    ArbolHuffman();
    ~ArbolHuffman();
    void fijarRaiz(const vector<char>& simbolos, const vector<long long>& frecuencias);
    string decodificar(const string& codigoBinario, long long length);
    void generarCodigos(vector<char>& simbolos, vector<string>& codigos);
    NodoHuffman* getRaiz();
};

#endif
