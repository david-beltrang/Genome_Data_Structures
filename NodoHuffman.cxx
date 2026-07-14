#include "NodoHuffman.h"

NodoHuffman::NodoHuffman(char simbolo, long long frecuencia)
{
    this->simbolo = simbolo;
    this->frecuencia = frecuencia;
    this->izquierda = 0;
    this->derecha = 0;
}

NodoHuffman::NodoHuffman(long long frecuencia, NodoHuffman *izquierda, NodoHuffman *derecha)
{
    this->simbolo = '\0';
    this->frecuencia = frecuencia;
    this->izquierda = izquierda;
    this->derecha = derecha;
}

bool NodoHuffman::esHoja()
{
    return (izquierda == 0 && derecha == 0);
}
