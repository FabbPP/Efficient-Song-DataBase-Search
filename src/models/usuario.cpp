#include "Usuario.h"
#include <cmath>

void Usuario::agregarValoracion(const Valoracion& val) {
    valoraciones[val.codigoCancion] = val;
    cacheSimilaridad.clear();
}

bool Usuario::tieneValoracion(const string& codigoCancion) const {
    return valoraciones.find(codigoCancion) != valoraciones.end();
}

Valoracion Usuario::getValoracion(const string& codigoCancion) const {
    return valoraciones.at(codigoCancion);
}

double Usuario::calcularSimilaridad(const Usuario& otro) const {
    auto it = cacheSimilaridad.find(otro.codigo);
    if (it != cacheSimilaridad.end()) return it->second;

    double distanciaManhattan = 0.0;
    int cancionesComunes = 0;

    for (const auto& par : valoraciones) {
        const string& codigoCancion = par.first;
        const Valoracion& valoracion1 = par.second;

        if (otro.tieneValoracion(codigoCancion)) {
            const Valoracion& valoracion2 = otro.getValoracion(codigoCancion);
            distanciaManhattan += abs(valoracion1.valoracion - valoracion2.valoracion);
            cancionesComunes++;
        }
    }

    if (cancionesComunes == 0) {
        cacheSimilaridad[otro.codigo] = 0.0;
        return 0.0;
    }

    double respuesta = 1.0 / (1.0 + distanciaManhattan / cancionesComunes);
    cacheSimilaridad[otro.codigo] = respuesta;
    return respuesta;
}