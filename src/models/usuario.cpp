#include "../../include/models/usuario.h"
#include <algorithm>
#include <cmath>

Usuario::Usuario() : codigo("") {}

Usuario::Usuario(const std::string& cod) : codigo(cod) {}

Usuario::Usuario(const Usuario& other) : codigo(other.codigo) {
    for (Cancion* cancion : other.canciones_valoradas) {
        canciones_valoradas.push_back(new Cancion(*cancion));
    }
}

Usuario::~Usuario() {
    for (Cancion* cancion : canciones_valoradas) {
        delete cancion;
    }
    canciones_valoradas.clear();
}

bool Usuario::agregarCancion(Cancion* cancion) {
    if (!cancion) return false;
    
    // Verificar si ya existe
    for (Cancion* c : canciones_valoradas) {
        if (c->getCodigo() == cancion->getCodigo()) {
            return false; // Ya existe
        }
    }
    
    canciones_valoradas.push_back(new Cancion(*cancion));
    return true;
}

bool Usuario::eliminarCancion(const std::string& codigo_cancion) {
    auto it = std::find_if(canciones_valoradas.begin(), canciones_valoradas.end(),
        [&codigo_cancion](const Cancion* c) {
            return c->getCodigo() == codigo_cancion;
        });
    
    if (it != canciones_valoradas.end()) {
        delete *it;
        canciones_valoradas.erase(it);
        return true;
    }
    return false;
}

Cancion* Usuario::buscarCancion(const std::string& codigo_cancion) const {
    for (Cancion* cancion : canciones_valoradas) {
        if (cancion->getCodigo() == codigo_cancion) {
            return cancion;
        }
    }
    return nullptr;
}

Usuario& Usuario::operator=(const Usuario& other) {
    if (this != &other) {
        // Limpiar canciones existentes
        for (Cancion* cancion : canciones_valoradas) {
            delete cancion;
        }
        canciones_valoradas.clear();
        
        // Copiar datos
        codigo = other.codigo;
        for (Cancion* cancion : other.canciones_valoradas) {
            canciones_valoradas.push_back(new Cancion(*cancion));
        }
    }
    return *this;
}

bool Usuario::operator==(const Usuario& other) const {
    return codigo == other.codigo;
}

void Usuario::print() const {
    std::cout << "Usuario: " << codigo << " (" << canciones_valoradas.size() << " canciones)" << std::endl;
    for (const Cancion* cancion : canciones_valoradas) {
        std::cout << "  ";
        cancion->print();
    }
}

double Usuario::getValoracionPromedio() const {
    if (canciones_valoradas.empty()) return 0.0;
    
    double suma = 0.0;
    for (const Cancion* cancion : canciones_valoradas) {
        suma += cancion->getValoracion();
    }
    return suma / canciones_valoradas.size();
}
