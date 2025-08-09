#include "comando_functions.h"
#include <iostream>

// Esta funcion muestra los comandos diponibles que puede utilizar el usuario
void mostrarAyudaGeneral() {
    cout << "Comandos disponibles:\n";
    cout << " - cargar nombre_archivo\n";
    cout << " - listar_secuencias\n";
    cout << " - histograma descripcion_secuencia\n";
    cout << " - es_subsecuencia subsecuencia\n";
    cout << " - enmascarar subsecuencia\n";
    cout << " - guardar nombre_archivo\n";
    cout << " - codificar nombre_archivo.fabin\n";
    cout << " - decodificar nombre_archivo.fabin\n";
    cout << " - ruta_mas_corta descripcion_secuencia i j x y\n";
    cout << " - base_remota descripcion_secuencia i j\n";
    cout << " - ayuda [comando]\n";
    cout << " - salir\n";
}

// Esta funcion muestra la ayuda especifica de un comando
void mostrarAyudaEspecifica(const string& comando) {
    if (comando == "cargar") {
        cout << "Uso: cargar nombre_archivo\n"
             <<" Funcion: Se carga la informacion de los genomas que estan guardados en el archivo nombre_archivo. Cada vez que se use este comando todo lo anterior guardado por el mismo se borra y se carga la nueva informacion.\n";
    } else if (comando == "listar_secuencias") {
        cout << "Uso: listar_secuencias\n"
             << "Funcion: Imprime la cantidad de secuencias que se encuentran cargadas en el sistema y despues imprime la informacion basica de cada secuencia separado por saltos de linea. Si nota algun elemento incompleto en la secuencia lo tomara como - y al imprimirlo dira que la secuencia tiene al menos b bases, si esta completa la secuencia contiene b bases.\n";
    } else if (comando == "histograma") {
        cout << "Uso: histograma descripcion_secuencia\n"
             << " Funcion: Este comando ayuda en caso de que el usuario quiera saber la composicion de una secuencia genetica, verificar si esta completa o carece de alguna base, y tambien que bases predominan.\n";
    } else if (comando == "es_subsecuencia") {
        cout << "Uso: es_subsecuencia subsecuencia\n"
             << "Funcion: Determina si una subsecuencia dada por el usuario existe en algunas de las secuencias ya cargadas en el sistema. Si si existe, proporciona la cantidad de secuencia que contiene la subsecuencia.\n";
    } else if (comando == "enmascarar") {
        cout << "Uso: enmascarar subsecuencia\n"
             << "Funcion: Oculta una subsecuencia si aparece en alguna secuencia, esas bases existentes las cambia por X.\n";
    } else if (comando == "guardar") {
        cout << "Uso: guardar nombre_archivo\n"
             << "Funcion: Guardar la informacion guardada en memoria con todas las modificaciones (si las tuvo) de las secuencias en un archivo nombrado nombre_archivo.\n";
    } else if (comando == "codificar") {
        cout << "Uso: codificar nombre_archivo.fabin\n"
             << "Funcion: Convierte las secuencias cargadas en memoria a un formato binario comprimido usando el algoritmo de Huffman y las guarda en el archivo nombre_archivo.fabin.\n";
    } else if (comando == "decodificar") {
        cout << "Uso: decodificar nombre_archivo.fabin\n"
             << "Funcion: Lee un archivo nombre_archivo.fabin con secuencias comprimidas en formato Huffman, las descomprime y carga esas secuencias en memoria.\n";
    } else if (comando == "ruta_mas_corta") {
        cout << "Uso: ruta_mas_corta descripcion_secuencia i j x y\n"
             << "Funcion: Calcula la ruta con el menor costo entre dos posiciones especificas de bases dentro de la misma secuencia, considerando las conexiones en el grafo que representa esa secuencia.\n";
    } else if (comando == "base_remota") {
        cout << "Uso: base_remota descripcion_secuencia i j\n"
             << "Funcion: Encuentra la base mas lejana (en distancia dentro del grafo) que sea igual a la base ubicada en la posicion [i,j] y muestra la ruta para llegar hasta ella junto con el costo total.\n";
    } else {        cout << "[ERROR] No hay ayuda disponible para el comando: " << comando << "\n";
    }
}

// Esta funcion según el comando que recibe, devuelve un entero que representa ese comando para usarlo en el switch
int comandoAEntero(const string& comando) {
    if (comando == "salir")
	    return 1;
    else if (comando == "ayuda")
	    return 2;
    else if (comando == "cargar")
	    return 3;
    else if (comando == "listar_secuencias")
	    return 4;
    else if (comando == "histograma")
	    return 5;
    else if (comando == "es_subsecuencia")
	    return 6;
    else if (comando == "enmascarar")
	    return 7;
    else if (comando == "guardar")
	    return 8;
    else if (comando == "codificar")
	    return 9;
    else if (comando == "decodificar") 
	    return 10;
    else if (comando == "ruta_mas_corta") 
	    return 11;
    else if (comando == "base_remota")
	    return 12;
    else 
	    return 0;
}

