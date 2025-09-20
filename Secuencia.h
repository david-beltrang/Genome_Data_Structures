#ifndef __SECUENCIA__H__
#define __SECUENCIA__H__
#include <string>

// TAD Secuencia
class Secuencia {
private:
    string descripcion;
    string bases;
    int anchoLinea;

public:
    // Constructores 
    Secuencia();
    Secuencia(string desc);

    // Prototipos de las Funciones
    void setDescripcion(string& desc);
    string getDescripcion();
    void agregarLinea(string& linea);
    string getBases();
    int getAnchoLinea();
    bool secuenciaCompleta();
    int contarBases(const string& bases, int (&conteoBase)[256]);
    void reemplazarSubsecuencia(const string& sub, int pos);
    int contarSubsecuencia(const string& sub) const;
};

#endif // __SECUENCIA__H__