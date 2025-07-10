#include "Cancion.h"

void Cancion::calcularPromedio() {
    if (valoraciones.empty()) {
        promedioValoracion = 0.0;
        return;
    }
    double suma = 0.0;
    for (const auto& val : valoraciones) {
        suma += val.valoracion;
    }
    promedioValoracion = suma; 
    //suma/valoraciones.size()
}

void Cancion::agregarValoracion(const Valoracion& val) {
    valoraciones.push_back(val);
    calcularPromedio();
}
