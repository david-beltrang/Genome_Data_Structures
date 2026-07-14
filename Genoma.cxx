#include "Genoma.h"
#include "comando_functions.h"
#include "ArbolHuffman.h"
#include <fstream>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <list>
#include "Secuencia.h"
#include "GrafoBase.h"
#include "NodoGrafo.h"

// Busca una secuencia en memoria a partir de su descripción y devuelve la secuencia encontrada o una vacía si no existe
Secuencia Genoma::buscarSecuencia(const string &desc)
{
    // Recorre todas las secuencias en memoria
    for (vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it)
    {
        // Compara la descripción con la buscada
        if (it->getDescripcion() == desc)
            return *it;
    }
    return Secuencia(); // Si no se encuentra, devuelve objeto vacío
}

// Carga secuencias desde un archivo en formato FASTA cada secuencia inicia con '>'
void Genoma::cargarDesdeArchivo(const string &nombreArchivo)
{
    ifstream entrada(nombreArchivo);
    if (!entrada)
    { // Verifica que el archivo se pueda abrir
        cout << nombreArchivo << " no se encuentra o no puede leerse.\n";
        return;
    }

    string linea;
    Secuencia actual;
    list<Secuencia> invalidas;
    secuencias.clear(); // Limpia memoria antes de cargar nuevas secuencias

    // Lee línea por línea el archivo
    while (getline(entrada, linea))
    {
        // Ignora líneas vacías
        if (linea.empty())
            continue;

        if (linea[0] == '>')
        {
            // Si hay una secuencia previa, la guarda si es válida
            if (!actual.getDescripcion().empty() && !actual.getBases().empty())
            {
                // Comprueba que la secuencia tenga al menos una base
                if (esBaseValida(actual.getBases()))
                {
                    secuencias.push_back(actual);
                }
                else
                {
                    invalidas.push_back(actual);
                }
            }
            // Inicia una nueva secuencia con la descripción (sin '>')
            actual = Secuencia(linea.substr(1));
        }
        else
        {
            // Agrega bases a la secuencia en construcción
            actual.agregarLinea(linea);
        }
    }

    // Guarda la última secuencia procesada
    if (!actual.getDescripcion().empty() && !actual.getBases().empty())
    {
        // Comprueba que la secuencia tenga al menos una base
        if (esBaseValida(actual.getBases()))
        {
            secuencias.push_back(actual);
        }
        // Si no es válida, se guarda en lista de secuencias invalidas
        else
        {
            invalidas.push_back(actual);
        }
    }

    // Informa sobre secuencias inválidas
    if (!invalidas.empty())
    {
        cout << "  Las secuencias: " << endl;
        for (Secuencia sec : invalidas)
        {
            cout << "\t-" << sec.getDescripcion() << endl;
        }
        cout << "  No se puedieron guardar porque tienen algun dato invalido como base" << endl;
    }

    entrada.close();

    // Muestra cuántas secuencias se cargaron
    int n = secuencias.size();
    if (n == 0)
    {
        cout << nombreArchivo << " no contiene ninguna secuencia.\n";
    }
    else if (n == 1)
    {
        cout << "1 secuencia cargada correctamente desde " << nombreArchivo << ".\n";
    }
    else
    {
        cout << n << " secuencias cargadas correctamente desde " << nombreArchivo << ".\n";
    }
}

// Guarda todas las secuencias en un archivo en formato FASTA.
void Genoma::guardarArchivo(const string &nombreArchivo)
{
    // Si no hay nada en memoria, no guarda
    if (secuencias.empty())
    {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    // Se abre el archivo de salida
    ofstream salida(nombreArchivo);
    if (!salida)
    {
        cout << "Error guardando en " << nombreArchivo << ".\n";
        return;
    }

    // Recorre todas las secuencias y las escribe en formato FASTA
    for (std::vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it)
    {
        // Escribe el encabezado
        salida << ">" << it->getDescripcion() << "\n"; // Encabezado
        // Escribe las bases en líneas de ancho fijo
        string bases = it->getBases();
        // Número de bases por línea
        int ancho = it->getAnchoLinea();

        // Divide las bases en bloques de 'ancho' caracteres
        for (int i = 0; i < bases.length(); i += ancho)
        {
            salida << bases.substr(i, ancho) << "\n";
        }
    }

    salida.close();
    cout << "Las secuencias han sido guardadas en " << nombreArchivo << ".\n";
}

// Lista en pantalla todas las secuencias cargadas y su tamaño.
void Genoma::listar_secuencias()
{
    if (secuencias.empty())
    {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    cout << "Hay " << secuencias.size() << " secuencias cargadas en memoria:\n";

    // Para cada secuencia, imprime descripción y número de bases
    for (vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it)
    {
        cout << "Secuencia " << it->getDescripcion();

        if (it->secuenciaCompleta())
        {
            // Si está completa, muestra el total de bases
            cout << " contiene " << it->getBases().length() << " bases.\n";
        }
        else
        {
            // Si no está completa, muestra un mínimo de bases contadas
            int conteoBase[256] = {0};
            cout << " contiene al menos " << it->contarBases(it->getBases(), conteoBase) << " bases.\n";
        }
    }
}

// Genera un histograma con la frecuencia de cada símbolo en la secuencia indicada.
void Genoma::histograma(const string &descripcion)
{
    // Busca la secuencia indicada
    Secuencia seq = buscarSecuencia(descripcion);

    // Si no existe, muestra error
    if (seq.getDescripcion().empty())
    {
        cout << "Secuencia inválida.\n";
        return;
    }

    int conteo[256] = {0};
    // Cuenta la cantidad de apariciones de cada carácter
    seq.contarBases(seq.getBases(), conteo);

    // Imprime cuantas veces aparece cada simbolo
    char simbolos[] = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};

    // Imprime la frecuencia de cada simbolo
    for (int i = 0; i < sizeof(simbolos) / sizeof(simbolos[0]); ++i)
    {
        if (conteo[simbolos[i]] > 0)
            cout << simbolos[i] << " : " << conteo[simbolos[i]] << "\n";
    }
}

// Revisa cuántas veces aparece una subsecuencia en todas las secuencias cargadas.
void Genoma::es_subsecuencia(const string &subsecuencia)
{
    // Si no hay secuencias en memoria, no busca
    if (secuencias.empty())
    {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    int totalApariciones = 0;
    // Recorre cada secuencia y cuenta las apariciones de la subsecuencia
    for (vector<Secuencia>::const_iterator it = secuencias.begin(); it != secuencias.end(); ++it)
    {
        totalApariciones += it->contarSubsecuencia(subsecuencia); // Usa método de Secuencia
    }

    // Muestra el resultado al usuario
    if (totalApariciones > 0)
    {
        cout << "La subsecuencia dada se repite " << totalApariciones << " veces dentro de las secuencias cargadas en memoria.\n";
    }
    else
    {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria.\n";
    }
}

// Reemplaza todas las apariciones de una subsecuencia por otro
void Genoma::enmascarar(const string &subsecuencia)
{
    // Si no hay secuencias en memoria, no busca
    if (secuencias.empty())
    {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    int cantidad = 0;
    // Recorre cada secuencia y busca la subsecuencia repetidamente
    for (vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it)
    {
        int pos = 0;
        // Busca todas las apariciones de la subsecuencia en la secuencia actual
        while ((pos = it->getBases().find(subsecuencia, pos)) != string::npos)
        {
            it->reemplazarSubsecuencia(subsecuencia, pos); // Reemplaza en esa posición
            cantidad++;
            pos += subsecuencia.length(); // Avanza para seguir buscando
        }
    }

    // Mensaje final con cuántas sustituciones se hicieron
    if (cantidad > 0)
    {
        cout << cantidad << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.\n";
    }
    else
    {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada.\n";
    }
}

// Calcula la frecuencia de cada base en las secuencias cargadas
void Genoma::calcularFrecuencia(vector<long long> &frecuencias, vector<char> &bases)
{
    int conteoBase[256] = {0};

    // Recorre cada secuencia y cuenta la frecuencia de cada base
    for (vector<Secuencia>::iterator it = secuencias.begin(); it != secuencias.end(); ++it)
    {
        it->contarBases(it->getBases(), conteoBase);
    }

    // Limpia los vectores antes de llenarlos
    bases.clear();
    frecuencias.clear();

    // Vector con los caracteres posibles
    vector<char> simbolo = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};

    // Recorre cada simbolo y cuenta la frecuencia de cada base
    for (int i = 0; i < simbolo.size(); i++)
    {
        // Comprueba si la frecuencia es mayor a cero
        if (conteoBase[simbolo[i]] > 0)
        {
            bases.push_back(simbolo[i]);
            frecuencias.push_back(conteoBase[simbolo[i]]);
        }
    }
}

// Codifica las secuencias cargadas en memoria usando el algoritmo de Huffman y las guarda en un archivo binario
void Genoma::codificar(const string &nombreArchivo)
{

    // Verificación inicial
    if (secuencias.empty())
    {
        cout << "No hay secuencias cargadas en memoria para codificar.\n";
        return;
    }

    // Abrir el archivo binario para escritura
    std::ofstream salida(nombreArchivo, std::ios::binary);
    if (!salida)
    {
        cout << "Error guardando en " << nombreArchivo << ".\n";
        return;
    }

    // Cálculo de frecuencias y construcción del árbol
    vector<char> bases;
    vector<long long> frecuencias;
    // Rellena con las bases y frecuencias
    calcularFrecuencia(frecuencias, bases);

    // Crea un árbol de Huffman
    ArbolHuffman arbol;
    // Construye el árbol de Huffman
    arbol.fijarRaiz(bases, frecuencias);

    // Generación de los códigos binarios
    vector<char> simbolos_codificados;
    vector<string> codigos;

    // Genera los códigos de cada simbolo
    arbol.generarCodigos(simbolos_codificados, codigos);

    // Vector auxiliar para acceder rápidamente al código
    vector<pair<char, string>> tablaCodigos;

    // Rellena tabla de códigos
    for (size_t i = 0; i < simbolos_codificados.size(); ++i)
    {
        tablaCodigos.push_back({simbolos_codificados[i], codigos[i]});
    }

    // Escribir 'n', cantidad de bases diferentes (2 bytes)
    unsigned short n_simbolos = (unsigned short)bases.size();
    salida.write(reinterpret_cast<const char *>(&n_simbolos), sizeof(n_simbolos));

    // Escribir n pares de código y frecuencia (c_i, f_i)
    for (size_t i = 0; i < bases.size(); ++i)
    {
        char c_i = bases[i]; // 1 byte - Código de la base

        // La frecuencia se escribe como 8 bytes para consistencia al decodificar
        long long f_i_8bytes = (long long)frecuencias[i];

        // Escribir en el archivo con los bytes especificos
        salida.write(reinterpret_cast<const char *>(&c_i), 1);
        salida.write(reinterpret_cast<const char *>(&f_i_8bytes), sizeof(f_i_8bytes));
    }

    // Escribir 'n_s', cantidad de secuencias (4 bytes)
    int n_s = secuencias.size();
    salida.write(reinterpret_cast<const char *>(&n_s), sizeof(n_s));

    // Escribir las descripcion y sus tamaños
    for (const Secuencia &seq : secuencias)
    {
        // Generar la secuencia binaria de la secuencia actual
        std::string descripcion = seq.getDescripcion();
        // Escribir 'l_i', tamaño del nombre (2 bytes)
        unsigned short l_i = (unsigned short)descripcion.length();
        salida.write(reinterpret_cast<const char *>(&l_i), sizeof(l_i));
        // s_ij: Nombre (l_i bytes)
        salida.write(descripcion.c_str(), l_i);
    }
    // Escribir cada secuencia en el archivo
    for (const Secuencia &seq : secuencias)
    {
        // Generar la secuencia binaria de la secuencia actual
        std::string basesActuales = seq.getBases();

        std::string codigoBinarioCompleto = "";

        // Crear tabla de búsqueda rápida
        string tablaBusquedaRapida[256];
        for (const pair<char, std::string> &par : tablaCodigos)
        {
            tablaBusquedaRapida[(unsigned char)par.first] = par.second;
        }

        // Codificar
        for (char base : basesActuales)
        {
            codigoBinarioCompleto += tablaBusquedaRapida[(unsigned char)base];
        }

        // Escribir 'w_i', longitud de la secuencia de bases (8 bytes)
        long long w_i = (long long)basesActuales.length();
        salida.write(reinterpret_cast<const char *>(&w_i), sizeof(w_i));

        // Escribir 'x_i', ancho de línea original (2 bytes)
        unsigned short x_i = (unsigned short)seq.getAnchoLinea();
        salida.write(reinterpret_cast<const char *>(&x_i), sizeof(x_i));

        // Escritura de Longitud Binaria (L_BIN)
        long long num_bits = codigoBinarioCompleto.length();
        // Fórmula para calcular el número de bytes a partir del número de bits: (bits + 7) / 8
        unsigned int L_BIN = (unsigned int)((num_bits + 7) / 8);
        salida.write(reinterpret_cast<const char *>(&L_BIN), sizeof(L_BIN));

        // Escritura de Datos Binarios Comprimidos
        escribirBitsEmpaquetados(salida, codigoBinarioCompleto);
    }

    salida.close();
    cout << "Secuencias codificadas y guardadas en el archivo binario: " << nombreArchivo << ".\n";
}

// Escribe los bits empaquetados en un archivo binario
void Genoma::escribirBitsEmpaquetados(std::ofstream &salida, const std::string &bitString)
{
    if (bitString.empty())
        return;

    unsigned char buffer = 0;
    int bitCount = 0;

    // Iterar sobre la cadena de bits
    for (char bit : bitString)
    {
        // Desplazar el buffer a la izquierda y añadir el nuevo bit
        buffer <<= 1;
        if (bit == '1')
        {
            buffer = buffer | 1; // OR con 1 si el bit es '1'
        }
        bitCount++;

        // Si el buffer está lleno (8 bits), escribirlo
        if (bitCount == 8)
        {
            salida.write(reinterpret_cast<char *>(&buffer), 1);
            buffer = 0;   // Reiniciar buffer
            bitCount = 0; // Reiniciar contador
        }
    }

    // Manejar el padding (bits restantes que no llenaron un byte completo)
    if (bitCount > 0)
    {
        // Desplazar el buffer restante a la izquierda hasta completar 8 bits.
        // No se guarda el padding, dado que el decodificador lo ignorará por la longitud w_i.
        buffer <<= (8 - bitCount);
        salida.write(reinterpret_cast<char *>(&buffer), 1);
    }
}

string Genoma::leerBitsDesempaquetados(std::ifstream &entrada, long long bytesToRead)
{
    string bitString = "";
    unsigned char buffer;

    for (long long i = 0; i < bytesToRead; ++i)
    {
        // Lee 1 byte
        if (!entrada.read(reinterpret_cast<char *>(&buffer), 1))
        {
            break; // Salir si falla la lectura
        }

        // Convierte el byte leído a 8 caracteres '0' o '1'
        for (int j = 7; j >= 0; --j)
        {
            // Revisa bit por bit y concatena el caracter
            bitString += ((buffer >> j) & 1) ? '1' : '0';
        }
    }
    return bitString;
}

// Decodifica las secuencias desde un archivo binario usando el algoritmo de Huffman y las carga en memoria
void Genoma::decodificar(const string &nombreArchivo)
{

    // Validar extensión del archivo
    if (nombreArchivo.length() < 6 ||
        nombreArchivo.substr(nombreArchivo.length() - 6) != ".fabin")
    {
        cout << "Error: El archivo debe tener extensión .fabin\n";
        return;
    }

    // Abrir el archivo en modo binario
    std::ifstream entrada(nombreArchivo, std::ios::binary);
    if (!entrada)
    {
        std::cout << "No se pudo abrir o leer el archivo " << nombreArchivo << ".\n";
        return;
    }

    // Estructuras para la reconstrucción del árbol
    std::vector<char> bases_leidas_nuevas;
    std::vector<long long> frecuencias_leidas_nuevas; // Debe ser long long para los 8 bytes
    ArbolHuffman arbol;

    // Leer 'n', cantidad de bases diferentes (2 bytes)
    unsigned short n_simbolos;
    // Uso de sizeof() para leer exactamente 2 bytes
    if (!entrada.read(reinterpret_cast<char *>(&n_simbolos), sizeof(n_simbolos)))
    {
        std::cout << "Error: Archivo incompleto o corrupto (n_simbolos).\n";
        // Cerrar archivo y retornar
        entrada.close();
        return;
    }

    // Leer n pares de código y frecuencia (c_i, f_i)
    for (int i = 0; i < n_simbolos; ++i)
    {
        char c_i;      // Código de la base (1 byte)
        long long f_i; // Frecuencia (8 bytes)

        // Lectura de código de base (1 byte)
        if (!entrada.read(reinterpret_cast<char *>(&c_i), 1))
        {
            std::cout << "Error: Archivo incompleto o corrupto (c_i).\n";
            entrada.close();
            return;
        }
        // Lectura de frecuencia (8 bytes) usando sizeof()
        if (!entrada.read(reinterpret_cast<char *>(&f_i), sizeof(f_i)))
        {
            std::cout << "Error: Archivo incompleto o corrupto (f_i).\n";
            entrada.close();
            return;
        }

        // Almacenar las bases y frecuencias en vectores
        bases_leidas_nuevas.push_back(c_i);
        frecuencias_leidas_nuevas.push_back(f_i);
    }

    // Reconstruir el Árbol de Huffman
    arbol.fijarRaiz(bases_leidas_nuevas, frecuencias_leidas_nuevas);

    // Limpiar memoria antes de cargar las nuevas secuencias
    secuencias.clear();

    // Leer 'n_s', cantidad total de secuencias (4 bytes)
    int n_s;
    if (!entrada.read(reinterpret_cast<char *>(&n_s), sizeof(n_s)))
    {
        std::cout << "Error: Archivo incompleto o corrupto (n_s).\n";
        entrada.close();
        return;
    }

    vector<string> descripciones(n_s);
    for (int i = 0; i < n_s; ++i)
    {
        // Leer l_i, Tamaño del nombre (2 bytes)
        unsigned short l_i;
        if (!entrada.read(reinterpret_cast<char *>(&l_i), sizeof(l_i)))
        {
            std::cout << "Error: Lectura de l_i incompleta en secuencia " << i + 1 << ".\n";
            entrada.close();
            return;
        }

        // Leer s_ij, Caracter en la j-esima posición del nombre (1 Byte)
        string descripcion(l_i, '\0');
        if (!entrada.read(&descripcion[0], l_i))
        {
            std::cout << "Error: Lectura de nombre incompleta en secuencia " << i + 1 << ".\n";
            entrada.close();
            return;
        }
        descripciones[i] = descripcion;
    }

    // Leer cada secuencia del archivo
    for (int i = 0; i < n_s; ++i)
    {
        // Leer w_i, Longitud de la secuencia de bases (8 bytes)
        long long w_i;
        if (!entrada.read(reinterpret_cast<char *>(&w_i), sizeof(w_i)))
        {
            std::cout << "Error: Lectura de w_i incompleta en secuencia " << i + 1 << ".\n";
            entrada.close();
            return;
        }

        // Leer x_i, Ancho de línea original (2 bytes)
        unsigned short x_i;
        if (!entrada.read(reinterpret_cast<char *>(&x_i), sizeof(x_i)))
        {
            std::cout << "Error: Lectura de x_i incompleta en secuencia " << i + 1 << ".\n";
            entrada.close();
            return;
        }

        unsigned int L_BIN; // Longitud en BYtes del bloque binario
        if (!entrada.read(reinterpret_cast<char *>(&L_BIN), sizeof(L_BIN)))
        {
            std::cout << "Error: Lectura de la longitud binaria (L_BIN) fallida en secuencia " << i + 1 << ". Código Incompleto.\n";
            entrada.close();
            return;
        }

        long long bytes_a_leer = L_BIN;

        // Leer la secuencia binaria desempaquetada ('0's y '1's)
        std::string bitString = leerBitsDesempaquetados(entrada, bytes_a_leer);

        // Decodificar utilizando el árbol y teniendo en cuenta la longitud de la seuencia (w_i)
        std::string basesDecodificadas = arbol.decodificar(bitString, w_i);

        // Crear la Secuencia y cargarla en memoria
        Secuencia nuevaSecuencia(descripciones[i], basesDecodificadas, x_i);
        secuencias.push_back(nuevaSecuencia);
    }

    // Cerrar el archivo
    entrada.close();
    std::cout << "Secuencias decodificadas desde " << nombreArchivo << " y cargadas en memoria.\n";
}

void Genoma::ruta_mas_corta(const string &desc, int i, int j, int x, int y)
{
    // Buscar la secuencia por su descripción
    Secuencia s = buscarSecuencia(desc);

    // Verificar si la secuencia existe
    if (s.getDescripcion().empty())
    {
        cout << "La secuencia " << desc << " no existe.\n";
        return;
    }

    int cols = s.getAnchoLinea();

    int result = s.getBases().length() / cols;
    int filas = 0;

    // Calcular número de filas
    if (s.getBases().length() % cols != 0)
        filas = result + 1;
    else
        filas = result;

    // Verificar que las posiciones estén dentro de los límites
    if (i < 0 || i >= filas || j < 0 || j >= cols)
    {
        cout << "La base en la posición [" << i << "," << j << "] no existe.\n";
        return;
    }

    // Verificar que las posiciones estén dentro de los límites
    if (x < 0 || x >= filas || y < 0 || y >= cols)
    {
        cout << "La base en la posición [" << x << "," << y << "] no existe.\n";
        return;
    }

    // Crear el grafo de la secuencia
    GrafoBase grafo(s.getBases(), cols, filas);
    // Verificar que las bases en las posiciones no sean nulas
    if (grafo.getBasePosicion(i, j) == '\0')
    {
        cout << "La base origen en la posicion (" << i << ", " << j << ") es nula" << endl;
        return;
    }
    else if (grafo.getBasePosicion(x, y) == '\0')
    {
        cout << "La base destino en la posicion (" << x << ", " << y << ") es nula" << endl;
        return;
    }

    double costo;
    vector<NodoGrafo> ruta = grafo.dijkstra(i, j, x, y, costo);

    cout << "Para la secuencia " << desc << ", la ruta mas corta entre la base " << grafo.getBasePosicion(i, j)
         << " en " << "(" << i << "," << j << ") y la base " << grafo.getBasePosicion(x, y) << " en (" << x << ", " << y << ") es:\n"
         << "Ruta: ";

    // Recorremos la ruta con tipos explícitos
    // ... Código previo de ruta_mas_corta ...

    // Recorremos la ruta con tipos explícitos
    for (vector<NodoGrafo>::iterator it = ruta.begin(); it != ruta.end(); ++it)
    {
        char base = it->getBase();

        if (base == '\0')
        {
            base = '?';
        }

        // Imprimir en el formato [fila,columna](Base)
        cout << "[" << it->getFila() << "," << it->getColumna() << "](" << base << ")";

        if (it + 1 != ruta.end())
            cout << " -> ";
    }

    cout << "\nCosto total: " << costo << "\n";
}

void Genoma::base_remota(const string &desc, int i, int j)
{
    // Buscar la secuencia por su descripción
    Secuencia s = buscarSecuencia(desc);

    // Verificar si la secuencia existe
    if (s.getDescripcion().empty())
    {
        cout << "La secuencia " << desc << " no existe.\n";
        return;
    }

    int cols = s.getAnchoLinea();
    int result = s.getBases().length() / cols;
    int filas;
    // Calcular número de filas
    if (s.getBases().length() % cols != 0)
        filas = result + 1;
    else
        filas = result;

    // Verificar que las posiciones estén dentro de los límites
    if (i < 0 || i >= filas || j < 0 || j >= cols)
    {
        cout << "La base en la posición [" << i << "," << j << "] no existe.\n";
        return;
    }

    // Crear el grafo de la secuencia
    GrafoBase grafo(s.getBases(), cols, filas);

    // Verificar que la base en la posición no sea nula
    NodoGrafo origen(i, j, s.getBases()[i * cols + j]);

    // Llamada a baseMasRemota
    pair<NodoGrafo, vector<NodoGrafo>> res = grafo.baseMasRemota(origen);

    NodoGrafo objetivo = res.first;
    vector<NodoGrafo> ruta = res.second;

    cout << "Para la secuencia " << desc
         << ", la base remota está en [" << objetivo.getFila() << ","
         << objetivo.getColumna() << "].\nRuta: ";

    // Recorremos la ruta con tipos explícitos
    for (int nIndex = 0; nIndex < ruta.size(); nIndex++)
    {
        NodoGrafo n = ruta[nIndex];
        cout << n.getBase();
        if (nIndex + 1 < ruta.size())
            cout << " -> ";
    }

    double costo = 0;
    // Calcular el costo total de la ruta
    for (int k = 1; k < ruta.size(); k++)
    {
        NodoGrafo prev = ruta[k - 1];
        NodoGrafo curr = ruta[k];
        costo += grafo.peso(prev.getBase(), curr.getBase());
    }

    cout << "\nCosto total: " << costo << "\n";
}
