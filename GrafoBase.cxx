#include "GrafoBase.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include <queue>

GrafoBase::GrafoBase(const string &bases, int cols, int filas)
{
    // Inicializa las dimensiones del grafo
    this->cols = cols;
    this->filas = filas;

    // Redimensiona la matriz para almacenar los nodos del grafo
    matriz.resize(filas, vector<NodoGrafo>(cols));

    int cont = 0;
    // Llena la matriz con nodos basados en las bases proporcionadas
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < cols; j++, cont++)
        {
            if (cont < bases.length()) // Usa '<' en lugar de '!=' para seguridad
                matriz[i][j] = NodoGrafo(i, j, bases[i * cols + j]);
            else
                matriz[i][j] = NodoGrafo(i, j); // nodo vacio (base = '\0')
        }
    }
}

// Verifica si la posición (i, j) es válida dentro de la matriz
bool GrafoBase::posicionValida(int i, int j)
{
    return i >= 0 && i < filas && j >= 0 && j < cols;
}

// Devuelve la base en la posición (i, j)
char GrafoBase::getBasePosicion(int i, int j) const
{
    return matriz[i][j].getBase();
}

// Peso basado en la diferencia ASCII entre dos bases
double GrafoBase::peso(char a, char b)
{
    double diff = abs((int)a - (int)b);
    return 1.0 / (1.0 + diff);
}

vector<pair<NodoGrafo, double>> GrafoBase::vecinos(int i, int j)
{
    vector<pair<NodoGrafo, double>> vecinos;

    // Movimientos posibles: arriba, abajo, izquierda, derecha
    int movs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Recorre cada movimiento posible y verifica si es válido
    for (int k = 0; k < 4; k++)
    {
        int ni = i + movs[k][0];
        int nj = j + movs[k][1];

        // 1. Si la nueva posición es válida, verificar si es una base real
        if (posicionValida(ni, nj))
        {
            char b = matriz[ni][nj].getBase();
            
            if (b == '\0') {
                continue; // No procesar ni añadir este vecino.
            }

            // 2. Si la base es válida, calcular el peso y añadir el vecino.
            char a = matriz[i][j].getBase();
            // Agregar el vecino y su peso a la lista de vecinos
            vecinos.push_back(pair<NodoGrafo, double>(matriz[ni][nj], peso(a, b)));
        }
    }
    return vecinos;
}

vector<NodoGrafo> GrafoBase::dijkstra(int i, int j, int x, int y, double &costoFinal)
{
    costoFinal = 0;
    vector<NodoGrafo> ruta;

    // Distancias iniciales poniendo todas en infinito
    vector<vector<double>> dist(filas, vector<double>(cols, numeric_limits<double>::infinity()));

    // Padres para reconstruir la ruta final
    vector<vector<pair<int, int>>> parent(filas, vector<pair<int, int>>(cols, pair<int, int>(-1, -1)));

    // Priority_queue que almacena [distancia, (fila, columna)] simulando un min-heap.
    // La cola prioriza el valor más alto, por eso se pone la distancia negativa.
    using EntradaPQ = pair<double, pair<int, int>>;
    priority_queue<EntradaPQ> pq;

    dist[i][j] = 0;
    // Insertamos {0.0, {i, j}} negando la distancia: {-0.0, {i, j}}
    pq.push({-0.0, {i, j}});

    while (!pq.empty())
    {
        // Obtener el elemento con el menor valor de -distancia, el cual corresponde a la menor distancia positiva.
        double n_cdist = pq.top().first;
        double cdist = -n_cdist;

        // Obtener fila y columna
        int ci = pq.top().second.first;
        int cj = pq.top().second.second;

        // Sacar de la cola (pop)
        pq.pop();

        // Si encontramos una distancia más corta anteriormente, ignorar esta entrada obsoleta.
        if (cdist > dist[ci][cj])
            continue;

        // Si encontramos el destino, terminamos y rompemos el bucle.
        if (ci == x && cj == y)
            break;

        // Si en la posición actual la base es nula, no procesar sus vecinos.
        if (matriz[ci][cj].getBase() == '\0')
            continue;

        // Crear vecinos y relaja las aristas
        vector<pair<NodoGrafo, double>> vecinosActual = vecinos(ci, cj);

        // Recorre cada vecino
        for (const auto &vecino : vecinosActual)
        {
            // Obtener nodo y peso
            const NodoGrafo &ng = vecino.first;
            double w = vecino.second;

            // Obtener fila y columna del vecino
            int ni = ng.getFila();
            int nj = ng.getColumna();

            // Relajación: Si encontramos una ruta más corta al vecino (ni, nj)
            if (dist[ci][cj] + w < dist[ni][nj])
            {
                dist[ni][nj] = dist[ci][cj] + w;
                parent[ni][nj] = {ci, cj};

                // Insertamos en la cola de prioridad: {-nueva_distancia, {ni, nj}}
                pq.push({-dist[ni][nj], {ni, nj}});
            }
        }
    }

    // Asignar el costo final
    costoFinal = dist[x][y];

    // Si la distancia sigue siendo infinita o no hay padre (y no es el origen), no hay ruta.
    if (costoFinal == numeric_limits<double>::infinity() || (parent[x][y].first == -1 && !(i == x && j == y)))
        return ruta;

    int ci = x, cj = y;
    // Reconstruir la ruta desde el destino hasta el origen
    while (!(ci == i && cj == j))
    {
        // Agregar el nodo actual a la ruta
        ruta.push_back(matriz[ci][cj]);
        // Moverse al padre
        pair<int, int> p = parent[ci][cj];
        ci = p.first;
        cj = p.second;
    }
    // Agregar el nodo origen
    ruta.push_back(matriz[i][j]);

    // Invertir ruta
    int n = ruta.size();

    // Simple reversa de la ruta
    for (int k = 0; k < n / 2; k++)
    {
        // Intercambiar ruta[k] con ruta[n - k - 1]
        NodoGrafo temp = ruta[k];
        ruta[k] = ruta[n - k - 1];
        ruta[n - k - 1] = temp;
    }
    return ruta;
}

pair<NodoGrafo, vector<NodoGrafo>> GrafoBase::baseMasRemota(const NodoGrafo &origen)
{
    double mayor = -1;
    NodoGrafo mejor;
    vector<NodoGrafo> mejorRuta;

    // Recorrer toda la matriz para encontrar nodos con la misma base que el origen
    for (int i = 0; i < filas; i++)
    {
        // Recorre cada columna
        for (int j = 0; j < cols; j++)
        {
            // Si la base es igual a la del origen y no es el mismo nodo
            if (matriz[i][j].getBase() == origen.getBase() && !(i == origen.getFila() && j == origen.getColumna()))
            {

                double costo;
                // Obtener la ruta desde el origen hasta el nodo actual
                vector<NodoGrafo> ruta = dijkstra(origen.getFila(), origen.getColumna(), i, j, costo);

                // Si la ruta no está vacía y el costo es mayor que el mayor encontrado hasta ahora, actualizar
                if (!ruta.empty() && costo > mayor)
                {
                    mayor = costo;
                    mejor = matriz[i][j];
                    mejorRuta = ruta;
                }
            }
        }
    }

    // Devolver el nodo más remoto y la ruta correspondiente
    return {mejor, mejorRuta};
}
