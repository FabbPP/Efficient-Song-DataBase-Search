// Heap.cpp
#include "../../include/structures/heap.h"
#include <algorithm>
#include <functional>

std::vector<Cancion> Heap::obtenerKMasSimilares(const Cancion& consulta, int k) {
    // Max-heap: mantiene las K más cercanas (máxima distancia al tope)
    auto cmp = [&](const Cancion& a, const Cancion& b) {
        return consulta.distanciaManhattan(a) < consulta.distanciaManhattan(b);
    };

    std::priority_queue<Cancion, std::vector<Cancion>, decltype(cmp)> maxHeap(cmp);

    for (const auto& cancion : canciones) {
        if (cancion == consulta) continue;

        maxHeap.push(cancion);
        if ((int)maxHeap.size() > k) {
            maxHeap.pop();
        }
    }

    std::vector<Cancion> resultado;
    while (!maxHeap.empty()) {
        resultado.push_back(maxHeap.top());
        maxHeap.pop();
    }

    std::reverse(resultado.begin(), resultado.end());
    return resultado;
}

void Heap::heapSort() {
    auto cmp = [](const Cancion& a, const Cancion& b) {
        return a.getValoracion() < b.getValoracion();
    };

    std::priority_queue<Cancion, std::vector<Cancion>, decltype(cmp)> heap(cmp, canciones);
    
    canciones.clear();
    while (!heap.empty()) {
        canciones.push_back(heap.top());
        heap.pop();
    }
}