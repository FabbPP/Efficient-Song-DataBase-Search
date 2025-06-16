#ifndef VALORACION_H
#define VALORACION_H

#include <string>
using namespace std;

struct Valoracion {
    string codigoUsuario;
    string codigoCancion;
    double valoracion;
    double coordenadaX;

    Valoracion() : valoracion(0.0), coordenadaX(0.0) {}
    Valoracion(const string& usuario, const string& cancion, 
               double val, double x) :
        codigoUsuario(usuario), codigoCancion(cancion),
        valoracion(val), coordenadaX(x) {}
};

#endif