// include/models/cancion.h
#ifndef CANCION_H
#define CANCION_H

#include <string>
#include <iostream>
#include <cmath>

class Cancion {
private:
    std::string codigo;
    double valoracion;
    double coordenada_x;

public:
    // Constructores
    Cancion();
    Cancion(const std::string& cod, double val, double x);
    Cancion(const Cancion& other);
    
    // Destructor
    ~Cancion();
    
    // Getters
    std::string getCodigo() const { return codigo; }
    double getValoracion() const { return valoracion; }
    double getCoordenadaX() const { return coordenada_x; }
    
    // Setters
    void setCodigo(const std::string& cod) { codigo = cod; }
    void setValoracion(double val) { valoracion = val; }
    void setCoordenadaX(double x) { coordenada_x = x; }
    
    // Operadores
    Cancion& operator=(const Cancion& other);
    bool operator==(const Cancion& other) const;
    bool operator<(const Cancion& other) const;  // Para B-Tree (por valoración)
    bool operator>(const Cancion& other) const;
    
    // Funciones de distancia
    double distanciaManhattan(const Cancion& other) const;
    
    // Utilidades
    void print() const;
    std::string toString() const;
};
#endif // CANCION_H