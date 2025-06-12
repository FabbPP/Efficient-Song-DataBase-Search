// GESTOR PRINCIPAL
#ifndef GESTOR_MUSICA_H
#define GESTOR_MUSICA_H

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include "../../include/structures/HashTable.h"
#include "../models/cancion.h"
#include "../../include/structures/BTree.h"
#include "../../include/structures/Node.h"

class GestorMusica {
private:
    // Hash table para  valoraciones
    HashTable<std::string, ValoracionCancion> valoraciones_por_cancion;
    HashTable<std::string, std::vector<std::string>> usuarios;
    
    // B-Trees para rankings 
    BTree<CancionMejor, 20> mejores_canciones;  // Orden descendente
    BTree<CancionPeor, 20> peores_canciones;    // Orden ascendente
    
    void actualizarRankings(const std::string& codigo_cancion, 
                           const ValoracionCancion& valoracion_anterior,
                           const ValoracionCancion& valoracion_nueva);

public:
    GestorMusica();
    ~GestorMusica();
    
    bool cargarCSV(const std::string& archivo);
    void agregarValoracion(const std::string& usuario, const std::string& cancion, 
                          double valoracion, double coordenada_x);
    
    // Consultas principales con B-Tree
    std::vector<CancionMejor> getMejores10();
    std::vector<CancionPeor> getPeores10();
    
    // Estadísticas
    void mostrarEstadisticas() const;
    void mostrarEstadisticasBTree() const;
};

#endif