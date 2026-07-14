#ifndef NODO_HUFFMAN_H
#define NODO_HUFFMAN_H

class NodoHuffman
{
public:
    char simbolo;           // Base o caracter
    long long frecuencia;   // Frecuencia de aparicion
    NodoHuffman *izquierda; // Hijo izquierdo
    NodoHuffman *derecha;   // Hijo derecho

    // Constructor para un nodo hoja
    NodoHuffman(char simbolo, long long frecuencia);
    // Constructor para un nodo interno
    NodoHuffman(long long frecuencia, NodoHuffman *izquierda, NodoHuffman *derecha);
    // Indica si el nodo es hoja
    bool esHoja();
};

#endif
