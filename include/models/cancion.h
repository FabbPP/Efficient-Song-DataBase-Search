// include/models/cancion.h
#ifndef CANCION_H
#define CANCION_H

#include <string>
#include <iostream>
#include <cmath>
using namespace std;

class Cancion {
private:
    std::string codigo;
    double valoracion;
    double coordenada_x;
    int num_valoraciones; // Para calcular promedio
    double suma_valoraciones;
public:
    Cancion();
    Cancion(const string& cod, double val, double x);
    Cancion(const Cancion& other);
    ~Cancion();
    
    // Getters y Setters
    string getCodigo() const { return codigo; }
    double getValoracion() const { return valoracion; }
    double getCoordenadaX() const { return coordenada_x; }
    int getNumValoraciones() const { return num_valoraciones; }
    void setCodigo(const string& cod) { codigo = cod; }
    void setValoracion(double val) { valoracion = val; }
    void setCoordenadaX(double x) { coordenada_x = x; }
    void incrementarValoraciones() { num_valoraciones++; }
    double distanciaManhattan(const Cancion& other) const;
    void actualizarValoracion(double nueva_val, int total_valoraciones);

// Operadores para B-Tree. Comparacion entre elementos objetos Cancion, se comparan por la valorcion
    bool operator<(const Cancion& other) const {
        return valoracion < other.valoracion;
    }
    bool operator>(const Cancion& other) const {
        return valoracion > other.valoracion;
    }
    bool operator==(const Cancion& other) const {
        return codigo == other.codigo;
    }
    bool operator<=(const Cancion& other) const {
        return valoracion <= other.valoracion;
    }
    bool operator>=(const Cancion& other) const {
        return valoracion >= other.valoracion;
    }
    
    void print() const;
    string toString() const;
};
/*
//Valoracion Cancion para Hash Table 
// Estructura para almacenar en hash table
struct ValoracionCancion {
    string codigo_cancion;
    double suma_valoraciones;
    int num_valoraciones;
    double promedio;
    
    ValoracionCancion() : codigo_cancion(""), suma_valoraciones(0.0), //Constructor vacio
                         num_valoraciones(0), promedio(0.0) {}
    
    ValoracionCancion(const std::string& cod, double val)  //Constructor
        : codigo_cancion(cod), suma_valoraciones(val), num_valoraciones(1), promedio(val) {}
    
    void agregarValoracion(double val) {
        suma_valoraciones += val;
        num_valoraciones++;
        promedio = suma_valoraciones / num_valoraciones; //promedio por la cantidad de valoraciones
    }
};
*/

#endif // CANCION_H