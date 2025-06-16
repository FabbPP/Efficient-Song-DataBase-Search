#ifndef CANCION_H
#define CANCION_H

#include <vector>
#include <string>
#include "Valoracion.h"

class Cancion {
private:
    string codigo;
    vector<Valoracion> valoraciones;
    double promedioValoracion;
    void calcularPromedio();
public:
    Cancion() : promedioValoracion(0.0) {}
    Cancion(const string& cod) : codigo(cod), promedioValoracion(0.0) {}
    void agregarValoracion(const Valoracion& val);
    string getCodigo() const { return codigo; }
    double getPromedioValoracion() const { return promedioValoracion; }
    const vector<Valoracion>& getValoraciones() const { return valoraciones; }
};

#endif