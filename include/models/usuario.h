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
    // Constructores
    Usuario();
    Usuario(const std::string& cod);
    Usuario(const Usuario& other);
    
    // Destructor
    ~Usuario();
    
    // Getters
    std::string getCodigo() const { return codigo; }
    const std::vector<Cancion*>& getCancionesValoradas() const { return canciones_valoradas; }
    size_t getNumCanciones() const { return canciones_valoradas.size(); }
    
    // Setters
    void setCodigo(const std::string& cod) { codigo = cod; }
    
    // Operaciones con canciones
    bool agregarCancion(Cancion* cancion);
    bool eliminarCancion(const std::string& codigo_cancion);
    Cancion* buscarCancion(const std::string& codigo_cancion) const;
    
    // Operadores
    Usuario& operator=(const Usuario& other);
    bool operator==(const Usuario& other) const;
    
    // Utilidades
    void print() const;
    double getValoracionPromedio() const;
    
    // Para recomendaciones (similitud entre usuarios)
    double similitudCon(const Usuario& other) const;
};

#endif // USUARIO_H