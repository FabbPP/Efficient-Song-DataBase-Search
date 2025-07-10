#ifndef SISTEMA_RECOMENDACION_H
#define SISTEMA_RECOMENDACION_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <thread>
#include <mutex>

#include "../Models/Usuario.h"
#include "../Models/Cancion.h"
#include "../Models/CancionValoracion.h"
#include "../BTree/BTree.h"

class SistemaRecomendacion {
private:
    std::unordered_map<std::string, Usuario> usuarios;
    std::unordered_map<std::string, Cancion> canciones;
    BTree<CancionValoracion, 5> btreeValoraciones;

    // Mutex para proteger el acceso a 'usuarios' y 'canciones'
    mutable std::mutex mtx_usuarios_canciones;

    bool procesarLinea(const string& linea);
    double calcularDistanciaManhattan(const Cancion& c1, const Cancion& c2);

    // Nueva función para procesar un bloque de líneas
    void procesarBloqueLineas(const std::vector<std::string>& lineas, 
                             std::unordered_map<string, Usuario>& usuarios_locales,
                             std::unordered_map<string, Cancion>& canciones_locales);

public:
    bool leerCSV(const string& nombreArchivo, unsigned int num_hilos = std::thread::hardware_concurrency());
    void actualizarBTree();
    vector<string> mejoresCanciones(int cantidad = 10);
    vector<string> peoresCanciones(int cantidad = 10);
    vector<string> cancionesSimilares(const string& codigoCancion, int cantidad = 10);
    vector<string> recomendarCanciones(const string& codigoUsuario, int cantidad = 5);
    void mostrarEstadisticas();
};

#endif
