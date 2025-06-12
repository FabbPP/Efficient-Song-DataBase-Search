// GESTOR PRINCIPAL
#ifndef GESTOR_MUSICA_H
#define GESTOR_MUSICA_H

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include "../../include/structures/HashTable.h"
#include "cancion.h"

class GestorMusica {
private:
    HashTable<std::string, ValoracionCancion> valoraciones_por_cancion;
/*
    HashTable<std::string, ValoracionCancion> valoraciones_por_cancion;
    HashTable<std::string, std::vector<std::string>> usuarios; // usuario -> canciones valoradas
    
    // Para mantener las mejores y peores canciones ordenadas
    std::multiset<ValoracionCancion, std::greater<ValoracionCancion>> mejores_canciones;
    std::multiset<ValoracionCancion> peores_canciones;
    
    void actualizarRankings(const ValoracionCancion& cancion_anterior, 
                           const ValoracionCancion& cancion_nueva);

public:
    GestorMusica();
    ~GestorMusica();
    
    bool cargarCSV(const std::string& archivo);
    void agregarValoracion(const std::string& usuario, const std::string& cancion, 
                          double valoracion, double coordenada_x);
    
    // Consultas principales
    std::vector<ValoracionCancion> getMejores10();
    std::vector<ValoracionCancion> getPeores10();
    
    // Consulta por similitud (preparación para siguiente meta)
    std::vector<std::string> getCancionesSimilares(const std::string& codigo_cancion, int limite = 5);
    
    void mostrarEstadisticas() const;
    void print() const;

*/
};
#endif