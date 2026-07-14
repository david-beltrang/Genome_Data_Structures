#ifndef NODOGRAFO_H
#define NODOGRAFO_H

class NodoGrafo
{

private:
    int fila;
    int col;
    char base;

public:
    NodoGrafo();
    NodoGrafo(int f, int c, char b);
    NodoGrafo(int f, int c);
    char getBase() const;
    int getFila() const;
    int getColumna() const;
};

#endif
