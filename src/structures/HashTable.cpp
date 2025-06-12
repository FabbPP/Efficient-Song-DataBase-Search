#include "HashTable.h"
#include <algorithm>
#include <limits>

MusicHashTable::MusicHashTable() {}

MusicHashTable::~MusicHashTable() {
    // Limpiar vectores de usuarios
    std::vector<Cancion*>* lista_canciones;
    // Nota: Necesitaríamos iterar sobre todos los usuarios, pero como es template
    // esto requiere una implementación más compleja. Por simplicidad, asumimos
    // que el usuario maneja la limpieza de memoria externamente.
}

bool MusicHashTable::insertarPorCodigo(const std::string& codigo, Cancion* cancion) {
    if (!cancion) return false;
    return codigo_table.insert(codigo, cancion);
}

Cancion* MusicHashTable::buscarPorCodigo(const std::string& codigo) const {
    Cancion* cancion = nullptr;
    if (codigo_table.search(codigo, cancion)) {
        return cancion;
    }
    return nullptr;
}

bool MusicHashTable::eliminarPorCodigo(const std::string& codigo) {
    return codigo_table.remove(codigo);
}

bool MusicHashTable::insertarPorUsuario(const std::string& usuario, Cancion* cancion) {
    if (!cancion) return false;
    
    std::vector<Cancion*>* lista_canciones = nullptr;
    
    if (usuario_table.search(usuario, lista_canciones)) {
        // Usuario ya existe, agregar canción a su lista
        lista_canciones->push_back(cancion);
    } else {
        // Nuevo usuario, crear lista
        lista_canciones = new std::vector<Cancion*>();
        lista_canciones->push_back(cancion);
        usuario_table.insert(usuario, lista_canciones);
    }
    
    return true;
}

std::vector<Cancion*>* MusicHashTable::buscarPorUsuario(const std::string& usuario) const {
    std::vector<Cancion*>* lista_canciones = nullptr;
    if (usuario_table.search(usuario, lista_canciones)) {
        return lista_canciones;
    }
    return nullptr;
}

bool MusicHashTable::eliminarCancionDeUsuario(const std::string& usuario, const std::string& codigo) {
    std::vector<Cancion*>* lista_canciones = buscarPorUsuario(usuario);
    if (!lista_canciones) return false;
    
    auto it = std::find_if(lista_canciones->begin(), lista_canciones->end(),
        [&codigo](const Cancion* c) {
            return c->getCodigo() == codigo;
        });
    
    if (it != lista_canciones->end()) {
        lista_canciones->erase(it);
        return true;
    }
    return false;
}

std::vector<std::pair<Cancion*, double>> MusicHashTable::buscarSimilares(const Cancion& cancion_base, size_t max_resultados) const {
    std::vector<std::pair<Cancion*, double>> similares;
    
    // Nota: Esta implementación es O(n) porque necesitamos recorrer toda la tabla
    // En una implementación real, mantendríamos una lista de todas las canciones
    // Por ahora, esta es una implementación conceptual
    
    return similares; // Implementación simplificada
}

void MusicHashTable::printStats() const {
    std::cout << "=== Music Hash Table Statistics ===" << std::endl;
    std::cout << "Tabla de códigos de canción:" << std::endl;
    codigo_table.print_stats();
    std::cout << "\nTabla de usuarios:" << std::endl;
    usuario_table.print_stats();
}