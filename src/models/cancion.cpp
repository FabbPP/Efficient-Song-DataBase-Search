#include "../../include/models/cancion.h"
#include <sstream>

#include <sstream>

Cancion::Cancion() : codigo(""), valoracion(0.0), coordenada_x(0.0), num_valoraciones(0) {}

Cancion::Cancion(const std::string& cod, double val, double x) 
    : codigo(cod), valoracion(val), coordenada_x(x), num_valoraciones(1) {}

Cancion::Cancion(const Cancion& other) 
    : codigo(other.codigo), valoracion(other.valoracion), 
      coordenada_x(other.coordenada_x), num_valoraciones(other.num_valoraciones) {}

Cancion::~Cancion() {}

Cancion& Cancion::operator=(const Cancion& other) {
    if (this != &other) {
        codigo = other.codigo;
        valoracion = other.valoracion;
        coordenada_x = other.coordenada_x;
        num_valoraciones = other.num_valoraciones;
    }
    return *this;
}

bool Cancion::operator==(const Cancion& other) const {
    return codigo == other.codigo;
}

bool Cancion::operator<(const Cancion& other) const {
    return valoracion < other.valoracion;
}

bool Cancion::operator>(const Cancion& other) const {
    return valoracion > other.valoracion;
}

double Cancion::distanciaManhattan(const Cancion& other) const {
    return std::abs(coordenada_x - other.coordenada_x);
}

void Cancion::print() const {
    std::cout << "Código: " << codigo 
              << ", Valoración: " << valoracion 
              << ", Coordenada X: " << coordenada_x 
              << ", Num Valoraciones: " << num_valoraciones << std::endl;
}

std::string Cancion::toString() const {
    std::stringstream ss;
    ss << codigo << "," << valoracion << "," << coordenada_x << "," << num_valoraciones;
    return ss.str();
}

void Cancion::actualizarValoracion(double nueva_val, int total_valoraciones) {
    // Calcular nuevo promedio
    valoracion = ((valoracion * num_valoraciones) + nueva_val) / (num_valoraciones + 1);
    num_valoraciones = total_valoraciones;
}