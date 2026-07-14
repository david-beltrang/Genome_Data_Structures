#ifndef __SECUENCIA__H__
#define __SECUENCIA__H__
#include <string>

using namespace std;

class Secuencia {
private:
    string descripcion;
    string bases;
    int anchoLinea;

public:
    // Constructores 
    Secuencia();
    Secuencia(string desc);
    Secuencia(const string& desc, const string& bases, unsigned short ancho);

    // Prototipos de las Funciones
    void setDescripcion(string& desc);
    string getDescripcion() const;
    void agregarLinea(const string& linea);
    string getBases() const;
    int getAnchoLinea() const;
    bool secuenciaCompleta();
    int contarBases(const string& bases, int (&conteoBase)[256]);
    void reemplazarSubsecuencia(const string& sub, int pos);
    int contarSubsecuencia(const string& sub) const;
};

#endif // __SECUENCIA__H__
