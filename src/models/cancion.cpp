#include "../../include/models/cancion.h"
#include <sstream>

Cancion::Cancion() : codigo(""), valoracion(0.0), coordenada_x(0.0) {}

Cancion::Cancion(const std::string& cod, double val, double x) 
    : codigo(cod), valoracion(val), coordenada_x(x) {}
Cancion::Cancion(const Cancion& other) 
    : codigo(other.codigo), valoracion(other.valoracion), coordenada_x(other.coordenada_x) {}
Cancion::~Cancion() {}
Cancion& Cancion::operator=(const Cancion& other) {
    if (this != &other) {
        codigo = other.codigo;
        valoracion = other.valoracion;
        coordenada_x = other.coordenada_x;
    }
    return *this;
}
bool Cancion::operator==(const Cancion& other) const {
    return codigo == other.codigo; //getCodigo
}
bool Cancion::operator<(const Cancion& other) const {
    return valoracion < other.valoracion; //getValoracion
}
double Cancion::distanciaManhattan(const Cancion& other) const {
    return std::abs(valoracion - other.valoracion);
}

void Cancion::print() const {
    std::cout << "Código: " << codigo 
              << ", Valoración: " << valoracion 
              << ", Coordenada X: " << coordenada_x << std::endl;
}

std::string Cancion::toString() const {
    std::stringstream ss;
    ss << codigo << "," << valoracion << "," << coordenada_x;
    return ss.str();
}
