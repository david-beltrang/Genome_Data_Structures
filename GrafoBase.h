#ifndef GRAFOBASE_H
#define GRAFOBASE_H

#include <vector>
#include <string>
#include <queue>
#include <limits>
#include "NodoGrafo.h"

using namespace std;

class GrafoBase
{
private:
    vector<vector<NodoGrafo>> matriz;
    int filas, cols;

public:
    GrafoBase(const string &bases, int cols, int filas);
    bool posicionValida(int i, int j);
    char getBasePosicion(int i, int j) const;
    vector<pair<NodoGrafo, double>> vecinos(int i, int j);
    vector<NodoGrafo> dijkstra(int i, int j, int x, int y, double &costoFinal);
    double peso(char a, char b);
    pair<NodoGrafo, vector<NodoGrafo>> baseMasRemota(const NodoGrafo &origen);
};

#endif
