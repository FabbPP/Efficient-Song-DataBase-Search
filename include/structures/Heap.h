// Heap.h
#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <queue>
#include "../models/cancion.h"

class Heap {
private:
    std::vector<Cancion> canciones;
    
public:
    Heap(const std::vector<Cancion>& canciones) : canciones(canciones) {}
    
    // Retorna las K canciones más similares a 'consulta' usando distancia Manhattan
    std::vector<Cancion> obtenerKMasSimilares(const Cancion& consulta, int k);
    
    // Ordena las canciones por valoración (mayor a menor)
    void heapSort();
    
    // Obtener canciones
    const std::vector<Cancion>& getCanciones() const { return canciones; }
};

#endif // HEAP_H