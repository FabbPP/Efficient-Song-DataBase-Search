#include "../../include/models/cancion.h"
#include <sstream>

#include <sstream>
using namespace std;

Cancion::Cancion() : codigo(""), valoracion(0.0), coordenada_x(0.0), 
                     num_valoraciones(0), suma_valoraciones(0.0) {}

Cancion::Cancion(const string& cod, double val, double x) 
    : codigo(cod), valoracion(val), coordenada_x(x), 
      num_valoraciones(1), suma_valoraciones(val) {}

Cancion::Cancion(const Cancion& other) 
    : codigo(other.codigo), valoracion(other.valoracion),
      coordenada_x(other.coordenada_x), num_valoraciones(other.num_valoraciones),
      suma_valoraciones(other.suma_valoraciones) {}

Cancion::~Cancion() {}

double Cancion::distanciaManhattan(const Cancion& other) const {
    return abs(coordenada_x - other.coordenada_x);
}
void Cancion::actualizarValoracion(double nueva_val, int total_valoraciones) {
    valoracion = ((valoracion * num_valoraciones) + nueva_val) / (num_valoraciones + 1);
    num_valoraciones = total_valoraciones;
}
void Cancion::print() const {
    cout << "Código: " << codigo 
              << ", Valoración: " << valoracion 
              << ", Coordenada X: " << coordenada_x 
              << ", Num Valoraciones: " << num_valoraciones << endl;
}

string Cancion::toString() const {
    stringstream ss;
    ss << codigo << "," << valoracion << "," << coordenada_x << "," << num_valoraciones;
    return ss.str();
}
