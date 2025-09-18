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
    Secuencia(const string& desc);  // CAMBIADO: usar const string&
    
    // AGREGADO: Operador de asignación
    Secuencia& operator=(const Secuencia& other);
    
    // CORREGIDO: Cambiar referencias no constantes a constantes
    void setDescripcion(const string& desc);
    string getDescripcion() const;  // AGREGADO: const
    void agregarLinea(const string& linea);
    string getBases() const;  // AGREGADO: const
    int getAnchoLinea() const;  // AGREGADO: const
    bool secuenciaCompleta() const;  // AGREGADO: const
    int contarBases(const string& bases, int (&conteoBase)[256]) const;  // CORREGIDO
    void reemplazarSubsecuencia(const string& sub, int pos);  // CORREGIDO
    int contarSubsecuencia(const string& sub) const;
};

#endif // __SECUENCIA__H__