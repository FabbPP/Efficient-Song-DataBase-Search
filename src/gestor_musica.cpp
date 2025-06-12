#include "../../include/gestor_musica.h"
#include <iostream>
//Aca se lee el archivo
GestorMusica::GestorMusica() {}
GestorMusica::~GestorMusica() {}

bool GestorMusica::cargarCSV(const std::string& archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << archivo << std::endl;
        return false;
    }
    
    std::string linea;
    int linea_num = 0;
    
    while (std::getline(file, linea)) {
        linea_num++;
        if (linea.empty()) continue;
        
        std::stringstream ss(linea);
        std::string usuario, cancion, valoracion_str, coordenada_str;
        
        if (std::getline(ss, usuario, ',') &&
            std::getline(ss, cancion, ',') &&
            std::getline(ss, valoracion_str, ',') &&
            std::getline(ss, coordenada_str, ',')) { 
            try {
                double valoracion = std::stod(valoracion_str);
                double coordenada_x = std::stod(coordenada_str); // Cuando la carga supera 75%
                if (linea_num % 10000 == 0) {
                    std::cout << "Procesadas " << linea_num << " líneas..." << std::endl;
                }
                
            } catch (const std::exception& e) {
                std::cerr << "Error en línea " << linea_num << ": " << e.what() << std::endl;
            }
        }
    }
    file.close();
    std::cout << "Lineas procesadas: " << linea_num << std::endl;
    return true;
}
/*
void GestorMusica::agregarValoracion(const std::string& usuario, const std::string& cancion, 
                                   double valoracion, double coordenada_x) {
    // Buscar valoración existente
    ValoracionCancion val_actual;
    bool existe = valoraciones_por_cancion.find(cancion, val_actual);
    
    ValoracionCancion val_anterior = val_actual;
    
    if (existe) {
        val_actual.agregarValoracion(valoracion);
    } else {
        val_actual = ValoracionCancion(cancion, valoracion);
    }
    
    // Actualizar hash table
    valoraciones_por_cancion.insert(cancion, val_actual);
    
    // Actualizar B-Trees
    // Para mejores canciones
    CancionMejor mejor = val_actual.toCancionMejor();
    mejores_canciones.Insert(mejor);
    
    // Para peores canciones
    CancionPeor peor = val_actual.toCancionPeor();
    peores_canciones.Insert(peor);
    
    // Manejar usuarios
    std::vector<std::string> canciones_usuario;
    if (usuarios.find(usuario, canciones_usuario)) {
        if (std::find(canciones_usuario.begin(), canciones_usuario.end(), cancion) == canciones_usuario.end()) {
            canciones_usuario.push_back(cancion);
            usuarios.insert(usuario, canciones_usuario);
        }
    } else {
        canciones_usuario.push_back(cancion);
        usuarios.insert(usuario, canciones_usuario);
    }
}

std::vector<CancionMejor> GestorMusica::getMejores10() {
    return mejores_canciones.getTop(10);
}

std::vector<CancionPeor> GestorMusica::getPeores10() {
    return peores_canciones.getTop(10);
}

void GestorMusica::mostrarEstadisticas() const {
    std::cout << "\n=== ESTADÍSTICAS DEL GESTOR DE MÚSICA ===" << std::endl;
    std::cout << "Total de canciones en sistema: " << valoraciones_por_cancion.size() << std::endl;
    std::cout << "Total de usuarios: " << usuarios.size() << std::endl;
    
    std::cout << "\n--- TOP 10 MEJORES CANCIONES ---" << std::endl;
    auto mejores = const_cast<GestorMusica*>(this)->getMejores10();
    for (size_t i = 0; i < mejores.size(); i++) {
        std::cout << (i+1) << ". " << mejores[i].codigo_cancion 
                  << " - Promedio: " << mejores[i].promedio 
                  << " (" << mejores[i].num_valoraciones << " valoraciones)" << std::endl;
    }
    
    std::cout << "\n--- TOP 10 PEORES CANCIONES ---" << std::endl;
    auto peores = const_cast<GestorMusica*>(this)->getPeores10();
    for (size_t i = 0; i < peores.size(); i++) {
        std::cout << (i+1) << ". " << peores[i].codigo_cancion 
                  << " - Promedio: " << peores[i].promedio 
                  << " (" << peores[i].num_valoraciones << " valoraciones)" << std::endl;
    }
}

void GestorMusica::mostrarEstadisticasBTree() const {
    std::cout << "\n=== ESTADÍSTICAS B-TREE ===" << std::endl;
    std::cout << "Elementos en B-Tree mejores: " << mejores_canciones.getCount() << std::endl;
    std::cout << "Elementos en B-Tree peores: " << peores_canciones.getCount() << std::endl;
}

// Instanciaciones explícitas para el template
template class HashTable<std::string, ValoracionCancion>;
template class HashTable<std::string, std::vector<std::string>>;
template class BTree<CancionMejor, 20>;
template class BTree<CancionPeor, 20>;
template class Node<CancionMejor, 20>;
template class Node<CancionPeor, 20>;
*/
