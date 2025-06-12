#include "models/cancion.h"
#include "structures/btree.h"
#include <map>
#include <string>
#include <vector>

class GestorMusica {
private:
    BTree<Cancion, 5> btree_canciones; // Usar tu B-Tree con orden 5

    
public:
    GestorMusica();
    ~GestorMusica();
    
    // Funciones principales
    bool cargarCSV(const string& archivo);
    void procesarRegistro(const string& codigo_usuario, const string& codigo_cancion, 
                         double valoracion, double coordenada);
    
    // Consultas usando tu B-Tree
    vector<Cancion> getMejores10();
    vector<Cancion> getPeores10();
    
    // Estadísticas
    void mostrarEstadisticas();
    void mostrarBTree();
    
    // Utilidades
    size_t getTotalCanciones() const;
    void reconstruirBTree(); // Reconstruir B-Tree con datos actualizados
};
