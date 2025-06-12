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
    int num_valoraciones; // Para calcular promedio

public:
    Cancion();
    Cancion(const std::string& cod, double val, double x);
    Cancion(const Cancion& other);
    ~Cancion();
    
    // Getters y Setters
    std::string getCodigo() const { return codigo; }
    double getValoracion() const { return valoracion; }
    double getCoordenadaX() const { return coordenada_x; }
    int getNumValoraciones() const { return num_valoraciones; }
    void setCodigo(const std::string& cod) { codigo = cod; }
    void setValoracion(double val) { valoracion = val; }
    void setCoordenadaX(double x) { coordenada_x = x; }
    void incrementarValoraciones() { num_valoraciones++; }
    Cancion& operator=(const Cancion& other);
    bool operator==(const Cancion& other) const;
    bool operator<(const Cancion& other) const;  // Para B-Tree (por valoración)
    bool operator>(const Cancion& other) const;
    double distanciaManhattan(const Cancion& other) const;
    void actualizarValoracion(double nueva_val, int total_valoraciones);


    void print() const;
    std::string toString() const;
};

struct ValoracionCancion {
    std::string codigo_cancion;
    double suma_valoraciones;
    int num_valoraciones;
    double promedio;
    
    ValoracionCancion() : codigo_cancion(""), suma_valoraciones(0.0), 
                         num_valoraciones(0), promedio(0.0) {}
    
    ValoracionCancion(const std::string& cod, double val) 
        : codigo_cancion(cod), suma_valoraciones(val), num_valoraciones(1), promedio(val) {}
    
    void agregarValoracion(double val) {
        suma_valoraciones += val;
        num_valoraciones++;
        promedio = suma_valoraciones / num_valoraciones; //Para basarnos para las 10 mejores canciones segun la cantidad de valoraciones tmb
    }
    
    bool operator<(const ValoracionCancion& other) const {
        return promedio < other.promedio;
    }
    
    bool operator>(const ValoracionCancion& other) const {
        return promedio > other.promedio;
    }
};
#endif // CANCION_H