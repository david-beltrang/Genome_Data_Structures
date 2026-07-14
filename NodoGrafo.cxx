#include "NodoGrafo.h"

// Constructor para nodo del grafo
NodoGrafo::NodoGrafo()
{
    this->fila = 0;
    this->col = 0;
    this->base = '\0';
}

// Constructor con parámetros
NodoGrafo::NodoGrafo(int f, int c, char b)
{
    this->fila = f;
    this->col = c;
    this->base = b;
}

// Constructor sin base
NodoGrafo::NodoGrafo(int f, int c)
{
    this->fila = f;
    this->col = c;
    this->base = '\0';
}

// Getters
char NodoGrafo::getBase() const
{
    return base;
}

int NodoGrafo::getFila() const
{
    return fila;
}

int NodoGrafo::getColumna() const
{
    return col;
}