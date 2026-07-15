# Genomic Data Manipulation and Analysis System

Aplicación de consola interactiva que carga, manipula y consulta
secuencias genéticas en formato FASTA mediante un REPL. Implementa un
TAD lineal (Secuencia), un contenedor (Genoma), compresión Huffman con
archivo binario `.fabin`, y análisis de caminos sobre un grafo
bidimensional de bases.

## Estructuras de datos implementadas

| Estructura | Uso | Clase/archivo |
|---|---|---|
| Secuencia (lineal) | Representa una secuencia genética individual con descripción, cadena de bases y ancho de línea original | `Secuencia.h` / `Secuencia.cxx` |
| Genoma (contenedor) | Alberga un `vector<Secuencia>`, orquesta carga FASTA, consultas y exportación | `Genoma.h` / `Genoma.cxx` |
| NodoHuffman (árbol) | Nodo de árbol de Huffman con símbolo, frecuencia y punteros a hijos izquierdo/derecho | `NodoHuffman.h` / `NodoHuffman.cxx` |
| ArbolHuffman (árbol binario) | Árbol de Huffman: construcción por frecuencias, generación de códigos, decodificación | `ArbolHuffman.h` / `ArbolHuffman.cxx` |
| NodoGrafo (grafo) | Nodo de grafo con fila, columna y base | `NodoGrafo.h` / `NodoGrafo.cxx` |
| GrafoBase (grafo matricial) | Grafo representado como `vector<vector<NodoGrafo>>` (matriz de adyacencia implícita) | `GrafoBase.h` / `GrafoBase.cxx` |

## Funcionalidades

**Carga y guardado FASTA** — `Genoma::cargarDesdeArchivo()` / `Genoma::guardarArchivo()`

El parser lee línea por línea (`Genoma.cxx:43`). Líneas que inician con
`>` crean una nueva `Secuencia` usando el resto como descripción
(`Genoma.cxx:65`). Las líneas siguientes se concatenan como bases
mediante `Secuencia::agregarLinea()` (`Secuencia.cxx:44–51`). Soporta
múltiples secuencias por archivo. Cada secuencia se valida con
`esBaseValida()` (`comando_functions.cxx:77–91`, switch con 18
símbolos IUPAC + `-`) antes de incorporarse al vector. El guardado
divide las bases en bloques del ancho de línea original
(`Genoma.cxx:147–150`).

**Listado de secuencias** — `Genoma::listar_secuencias()`

Imprime cantidad de secuencias, descripción y longitud en bases. Si la
secuencia contiene `-` (incompleta), reporta un mínimo de bases
contadas usando `Secuencia::secuenciaCompleta()` (`Secuencia.cxx:54–61`)
y `Secuencia::contarBases()`.

**Histograma de bases** — `Genoma::histograma()`

Cuenta frecuencia de 18 símbolos mediante
`Secuencia::contarBases()` (`Secuencia.cxx:64–95`), que usa un arreglo
`int[256]` indexado por valor ASCII y un `switch` para 18 símbolos
reconocidos (A, C, G, T, U, R, Y, K, M, S, W, B, D, H, V, N, X, `-`).
Solo imprime símbolos con conteo > 0.

**Búsqueda de subsecuencias** — `Genoma::es_subsecuencia()`

Cuenta ocurrencias de una subsecuencia mediante fuerza bruta:
`string::find()` en bucle dentro de
`Secuencia::contarSubsecuencia()` (`Secuencia.cxx:98–107`). No usa
KMP ni otros algoritmos de búsqueda de patrones.

**Enmascaramiento** — `Genoma::enmascarar()`

Reemplaza cada aparición de una subsecuencia con el carácter `X`
usando `Secuencia::reemplazarSubsecuencia()` (`Secuencia.cxx:110–115`).
La búsqueda usa `string::find()` desde la última posición encontrada
(`Genoma.cxx:259`).

## Compresión Huffman

**Construcción del árbol** — `ArbolHuffman::fijarRaiz()`
(`ArbolHuffman.cxx:41–76`)

1. Crea nodos hoja (`NodoHuffman`) para cada símbolo con su frecuencia.
2. Los inserta en orden ascendente por frecuencia mediante
   `insertarOrdenado()` (`ArbolHuffman.cxx:29–38`, inserción en
   `vector` manteniendo orden).
3. Itera combinando los dos nodos de menor frecuencia en un padre cuya
   frecuencia es la suma, y lo reinserta ordenadamente.
4. El nodo restante es la raíz.

**Generación de códigos** — `ArbolHuffman::generarCodigos()`
(`ArbolHuffman.cxx:96–99`)

Recorrido recursivo: `0` = izquierda, `1` = derecha. Asigna a cada
símbolo hoja su código binario como `string`.

**Decodificación** — `ArbolHuffman::decodificar()`
(`ArbolHuffman.cxx:107–151`)

Itera sobre la cadena de bits recorriendo el árbol desde la raíz: `0`
a izquierda, `1` a derecha. Al llegar a una hoja, emite el símbolo y
vuelve a la raíz. Se detiene al alcanzar `length` símbolos.

**Formato del archivo `.fabin`** — `Genoma::codificar()`
(`Genoma.cxx:309–427`)

```
Offset  Campo        Tamaño   Descripción
0       n            2B       Número de símbolos distintos
2       c_i          1B       Símbolo i-ésimo
3       f_i          8B       Frecuencia del símbolo i-ésimo
...     (repite n veces)
        n_s          4B       Número de secuencias
        l_i          2B       Longitud de la descripción de la secuencia i
        s_ij         l_i B    Descripción (bytes raw)
...     (repite n_s veces para las descripciones)
        w_i          8B       Longitud original de la secuencia i (en bases)
        x_i          2B       Ancho de línea original
        L_BIN        4B       Longitud del bloque binario comprimido (en bytes)
        datos        L_BIN B  Bits empaquetados (MSB primero, padding con 0s)
...     (repite n_s veces para los datos comprimidos)
```

El empaquetado de bits se realiza en `escribirBitsEmpaquetados()`
(`Genoma.cxx:430–466`): acumula bits en un `unsigned char` y escribe
cada 8 bits. El desempacado en `leerBitsDesempaquetados()`
(`Genoma.cxx:468–489`): lee bytes y los convierte a string de `'0'`/`'1'`.

Se verifico manualmente un ciclo completo codificar→decodificar sobre
`examples/dnaExample.fa` (5339 bases, solo A/C/G/T): el archivo
`.fabin` se genero sin errores y la recarga produjo exactamente la
misma secuencia de 5339 bases.

## Análisis de grafos

**Representación** — `GrafoBase` (`GrafoBase.h:19`)

La secuencia se organiza en una matriz bidimensional de `NodoGrafo`
con `filas` × `cols` (`GrafoBase.cxx:8–29`). Cada celda contiene la
base en esa posición. Si la posición excede la longitud de la
secuencia, la base es `'\0'` (nula).

**Peso de aristas** — `GrafoBase::peso()`
(`GrafoBase.cxx:44–48`)

```
peso(a, b) = 1.0 / (1.0 + abs(valorASCII(a) - valorASCII(b)))
```

El peso disminuye a medida que la diferencia ASCII aumenta: dos bases
identicas tienen peso 1.0 (maximo), mientras que bases muy distintas
(A, valorASCII 65, vs T, valorASCII 84) tienen un peso de aprox. 0.05.
Dijkstra minimiza la suma de pesos, por lo que favorece rutas que
atraviesan bases con valores ASCII cercanos, no similares en sentido
biologico.

Aristas solo entre vecinos ortogonales (arriba, abajo, izquierda,
derecha). No se consideran diagonales. Celdas con base `'\0'` no
generan aristas.

**Camino más corto** — `GrafoBase::dijkstra()`
(`GrafoBase.cxx:81–185`)

Implementa el algoritmo de Dijkstra con `priority_queue` simulando
min-heap mediante distancias negativas. Incluye relajación de aristas
y reconstrucción del camino mediante matriz de padres. Retorna el
vector de nodos y el costo total.

**Base más remota** — `GrafoBase::baseMasRemota()`
(`GrafoBase.cxx:187–220`)

Para cada celda con la misma base que el origen, ejecuta Dijkstra y
retorna aquella con mayor costo de ruta, junto con la ruta completa.

## Cómo compilar y ejecutar

No hay Makefile. Compilar con g++:

```
g++ -o genoma.exe test_comando.cxx Genoma.cxx Secuencia.cxx comando_functions.cxx ArbolHuffman.cxx NodoHuffman.cxx GrafoBase.cxx NodoGrafo.cxx
./genoma.exe
```

## Estructura de archivos

```
Genome_Data_Structures/
├── Genoma.h                  # TAD Genoma: contenedor vector<Secuencia>, declara métodos públicos
├── Genoma.cxx                # Implementación: carga/guardado FASTA, Huffman, Dijkstra, histograma
├── Secuencia.h               # TAD Secuencia: descripción, cadena de bases, ancho de línea
├── Secuencia.cxx             # Implementación: conteo por switch/ASCII, búsqueda por string::find()
├── ArbolHuffman.h            # TAD ArbolHuffman: raíz, construcción, codificación, decodificación
├── ArbolHuffman.cxx          # Implementación: construcción por frecuencia, códigos recursivos
├── NodoHuffman.h             # Nodo de árbol Huffman: símbolo, frecuencia, hijos
├── NodoHuffman.cxx           # Constructores: hoja (con símbolo) e interno (solo frecuencia + hijos)
├── GrafoBase.h               # TAD GrafoBase: matriz de NodoGrafo, Dijkstra, baseMasRemota
├── GrafoBase.cxx             # Implementación: peso por diferencia ASCII, Dijkstra con priority_queue
├── NodoGrafo.h               # Nodo de grafo: fila, columna, base
├── NodoGrafo.cxx             # Constructores y getters
├── comando_functions.h       # Funciones auxiliares: ayuda, mapeo comando→entero, validación de bases
├── comando_functions.cxx     # Implementación: mostrarAyuda*(), comandoAEntero(), esBaseValida()
├── test_comando.cxx          # Programa principal: REPL que parsea comandos y ejecuta Genoma
├── examples/
│   ├── dnaExample.fa             # 1 secuencia larga (Keratin, solo A,C,G,T)
│   ├── manySequences.fa          # 8 secuencias mezcladas (ADN, ARN, aminoacidos, gaps)
│   ├── multiSequence.fa          # 3 secuencias (aminoacidos/proteinas)
│   └── multisizeSequences.fa     # 11 secuencias de ADN mitocondrial (COI, solo A,C,G,T)
├── docs/
│   └── documentacion_tecnica.pdf  # Documento de entrega académica
└── README.md                 # Este archivo
```

## Estado de testing

No hay tests automatizados. `test_comando.cxx` no es un suite de
pruebas: es el programa principal que implementa el bucle REPL de la
aplicación (`test_comando.cxx:13`). Lee comandos de stdin, los parsea
con `istringstream`, los mapea a enteros mediante
`comandoAEntero()`, y despacha la ejecución con un `switch`
(`test_comando.cxx:22`). No contiene ningún `assert`, no incluye
ningún framework de testing y no realiza verificaciones automatizadas
de resultados. La verificación es manual a través de la consola
interactiva.

## Ejemplo de uso

Compilar y ejecutar el REPL:

```
g++ -o genoma.exe test_comando.cxx Genoma.cxx Secuencia.cxx comando_functions.cxx ArbolHuffman.cxx NodoHuffman.cxx GrafoBase.cxx NodoGrafo.cxx
./genoma.exe
```

Cargar un archivo de ejemplo y listar las secuencias:

```
$ cargar examples/multisizeSequences.fa
11 secuencias cargadas correctamente desde examples/multisizeSequences.fa.
$ listar_secuencias
Hay 11 secuencias cargadas en memoria:
Secuencia Seq1_Carpodacus_mexicanus contiene 695 bases.
Secuencia Seq2_uncultured_bacillus_sp. contiene 661 bases.
Secuencia Seq3_Phalaenopsis_equestris_var.leucaspis contiene 694 bases.
Secuencia Seq4_uncultured_archaeon contiene 674 bases.
Secuencia Seq5_InfluenzaAvirus contiene 694 bases.
Secuencia Seq6_Vireo_gilvus contiene 674 bases.
Secuencia Seq7_Pelecanus_erythrorhynchos contiene 662 bases.
Secuencia Seq8_Hippodamia_tredecimpunctata_tibialis contiene 652 bases.
Secuencia Seq9_Petunia_integrifolia_subsp.inflata contiene 592 bases.
Secuencia Seq10_Fusarium_oxysporum_f.tuberosi contiene 592 bases.
Secuencia Seq11_Dendroica_tigrina contiene 490 bases.
```

Generar histograma de una secuencia:

```
$ histograma Seq1_Carpodacus_mexicanus
A : 173
C : 223
G : 108
T : 191
```

Buscar una subsecuencia:

```
$ es_subsecuencia ATG
La subsecuencia dada se repite 62 veces dentro de las secuencias cargadas en memoria.
```

Cargar un archivo con gaps para verificar deteccion de incompletitud:

```
$ cargar examples/manySequences.fa
  Las secuencias:
	-LCBO_Bovine
	-MCHU_Calmodulin
	-gi|5524211|gb|AAD44166.1
  No se puedieron guardar porque tienen algun dato invalido como base
8 secuencias cargadas correctamente desde examples/manySequences.fa.
$ listar_secuencias
Hay 8 secuencias cargadas en memoria:
Secuencia NZ_GG697986.1 contiene al menos 140 bases.
Secuencia NC_002953.3 contiene al menos 169 bases.
Secuencia NC_017337.1 contiene al menos 159 bases.
Secuencia NC_003923.1 contiene al menos 169 bases.
Secuencia NC_017338.1 contiene al menos 112 bases.
Secuencia NZ_JH806555.1 contiene al menos 159 bases.
Secuencia NC_002951.2 contiene al menos 159 bases.
Secuencia NC_017340.1 contiene al menos 159 bases.
```

Nota: `manySequences.fa` contiene secuencias de aminoacidos (LCBO_Bovine,
MCHU_Calmodulin) que son rechazadas por `esBaseValida()`. Las 8 secuencias
cargadas corresponden a las cabeceras NZ_* y NC_* (ADN/ARN con gaps `-`).
Todas muestran "contiene al menos N bases" porque `Secuencia::secuenciaCompleta()`
detecta el caracter `-` en cada una.

## Autores

- Ana Maria Romero Cuadrado
- Juan Felipe Gómez López
- David Beltrán Gómez

Pontificia Universidad Javeriana — Estructuras de Datos, 2025-2.