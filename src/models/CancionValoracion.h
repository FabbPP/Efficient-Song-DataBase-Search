#ifndef CANCION_VALORACION_H
#define CANCION_VALORACION_H

#include <string>
#include <iomanip>
using namespace std;

struct CancionValoracion {
    string codigoCancion;
    double valoracionPromedio;
    
    CancionValoracion() : codigoCancion(""), valoracionPromedio(0.0) {}
    CancionValoracion(const string& codigo, double val) :
        codigoCancion(codigo), valoracionPromedio(val) {}
    
    bool operator<(const CancionValoracion& other) const {
        return valoracionPromedio < other.valoracionPromedio;
    }
    
    bool operator>(const CancionValoracion& other) const {
        return valoracionPromedio > other.valoracionPromedio;
    }
    
    friend ostream& operator<<(ostream& os, const CancionValoracion& cv) {
        os << cv.codigoCancion << "(" << fixed << setprecision(2) << cv.valoracionPromedio << ")";
        return os;
    }
};

#endif