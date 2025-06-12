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
    Cancion& operator=(const Cancion& other);
    bool operator==(const Cancion& other) const;
    bool operator<(const Cancion& other) const;  // Para B-Tree (por valoración)
    bool operator>(const Cancion& other) const;
    double distanciaManhattan(const Cancion& other) const;
    void actualizarValoracion(double nueva_val, int total_valoraciones);


    void print() const;
    string toString() const;
};
// Hash Table 
// Estructura para almacenar en hash table
struct ValoracionCancion {
    string codigo_cancion;
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
        promedio = suma_valoraciones / num_valoraciones;
    }
    CancionMejor toCancionMejor() const {
        return CancionMejor(codigo_cancion, promedio, num_valoraciones);
    }
    CancionPeor toCancionPeor() const {
        return CancionPeor(codigo_cancion, promedio, num_valoraciones);
    }
};
//B Tree 10 mejores 10 peores
struct CancionMejor {
    string codigo_cancion;
    double promedio;
    int num_valoraciones;
    CancionMejor() : codigo_cancion(""), promedio(0.0), num_valoraciones(0) {}
    
    CancionMejor(const std::string& cod, double prom, int num) 
        : codigo_cancion(cod), promedio(prom), num_valoraciones(num) {}
    bool operator<(const CancionMejor& other) const {
        if (promedio != other.promedio) {
            return promedio > other.promedio; // Orden descendente por valoración
        }
        return codigo_cancion < other.codigo_cancion; // Desempate por código
    }  
    bool operator==(const CancionMejor& other) const {
        return codigo_cancion == other.codigo_cancion;
    }
    void print() const {
        std::cout << "Canción: " << codigo_cancion 
                  << ", Promedio: " << promedio 
                  << " (" << num_valoraciones << " valoraciones)" << std::endl;
    }
};
struct CancionPeor {
    string codigo_cancion;
    double promedio;
    int num_valoraciones;
    
    CancionPeor() : codigo_cancion(""), promedio(0.0), num_valoraciones(0) {}
    
    CancionPeor(const std::string& cod, double prom, int num) 
        : codigo_cancion(cod), promedio(prom), num_valoraciones(num) {}
    bool operator<(const CancionPeor& other) const {
        if (promedio != other.promedio) {
            return promedio < other.promedio; // Orden ascendente por valoración
        }
        return codigo_cancion < other.codigo_cancion; // Desempate por código
    }
    bool operator==(const CancionPeor& other) const {
        return codigo_cancion == other.codigo_cancion;
    }
    
    void print() const {
        std::cout << "Canción: " << codigo_cancion 
                  << ", Promedio: " << promedio 
                  << " (" << num_valoraciones << " valoraciones)" << std::endl;
    }
};
#endif // CANCION_H