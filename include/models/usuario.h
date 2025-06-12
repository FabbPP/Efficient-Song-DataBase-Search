#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>
#include "cancion.h"

class Usuario {
private:
    std::string codigo;
    std::vector<Cancion*> canciones_valoradas;

public:
    Usuario();
    Usuario(const std::string& cod);
    Usuario(const Usuario& other);
    ~Usuario();
    // Getters y Setters
    std::string getCodigo() const { return codigo; }
    const std::vector<Cancion*>& getCancionesValoradas() const { return canciones_valoradas; }
    size_t getNumCanciones() const { return canciones_valoradas.size(); }
    void setCodigo(const std::string& cod) { codigo = cod; }

    bool agregarCancion(Cancion* cancion);
    bool eliminarCancion(const std::string& codigo_cancion);
    Cancion* buscarCancion(const std::string& codigo_cancion) const;
    Usuario& operator=(const Usuario& other);
    bool operator==(const Usuario& other) const;

    void print() const;
    double getValoracionPromedio() const;
    // Posible para heap Priority queue 
    // double similitudCon(const Usuario& other) const;
};

#endif // USUARIO_H