#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <map>
#include <unordered_map>
#include "Valoracion.h"

class Usuario {
private:
    string codigo;
    map<string, Valoracion> valoraciones;
    mutable unordered_map<string, double> cacheSimilaridad;
public:
    Usuario() = default;
    Usuario(const string& cod) : codigo(cod) {}
    void agregarValoracion(const Valoracion& val);
    string getCodigo() const { return codigo; }
    const map<string, Valoracion>& getValoraciones() const { return valoraciones; }
    bool tieneValoracion(const string& codigoCancion) const;
    Valoracion getValoracion(const string& codigoCancion) const;
    double calcularSimilaridad(const Usuario& otro) const;
};

#endif