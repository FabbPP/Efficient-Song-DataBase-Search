#ifndef SISTEMA_RECOMENDACION_H
#define SISTEMA_RECOMENDACION_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../Models/Usuario.h"
#include "../Models/Cancion.h"
#include "../Models/CancionValoracion.h"
#include "../BTree/BTree.h"

class SistemaRecomendacion {
private:
    unordered_map<string, Usuario> usuarios;
    unordered_map<string, Cancion> canciones;
    BTree<CancionValoracion, 5> btreeValoraciones;

    bool procesarLinea(const string& linea);
    double calcularDistanciaManhattan(const Cancion& c1, const Cancion& c2);
public:
    bool leerCSV(const string& nombreArchivo);
    void actualizarBTree();
    vector<string> mejoresCanciones(int cantidad = 10);
    vector<string> peoresCanciones(int cantidad = 10);
    vector<string> cancionesSimilares(const string& codigoCancion, int cantidad = 10);
    vector<string> recomendarCanciones(const string& codigoUsuario, int cantidad = 5);
    void mostrarEstadisticas();
};

#endif