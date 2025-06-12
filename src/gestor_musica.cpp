#include "../../include/gestor_musica.h"
#include <iostream>
using namespace std;
//Aca se lee el archivo
GestorMusica::GestorMusica() {}
GestorMusica::~GestorMusica() {}

bool GestorMusica::cargarCSV(const std::string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "No se puede encontrar/abrir el archivo " << archivo << std::endl;
        return false;
    }
    string linea;
    int linea_num = 0;
    while (getline(file, linea)) {
        linea_num++;
        if (linea.empty()) continue;
        
        stringstream ss(linea);
        string usuario, cancion, valoracion_str, coordenada_str;
        if (getline(ss, usuario, ',') &&
            getline(ss, cancion, ',') &&
            getline(ss, valoracion_str, ',') &&
            getline(ss, coordenada_str, ',')) { 
            try {
                double valoracion = stod(valoracion_str);
                double coordenada_x = stod(coordenada_str); //Convierte los double en string 
                if (linea_num % 10000 == 0) {// Cuando la carga supera 75%
                    cout << "Procesadas " << linea_num << std::endl;
                }
            } catch (const std::exception& e) {
                cerr << "Error " << linea_num << ": " << e.what() << std::endl;
            }
        }
    }
    file.close();
    cout << "Lineas procesadas, proceso terminado : " << linea_num << std::endl;
    return true;
}

void GestorMusica::agregarValoracion(const string& usuario, const string& cancion, 
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
    valoraciones_por_cancion.insert(cancion, val_actual);
    // Actualizar B-Trees
    // Para mejores canciones
    CancionMejor mejor = val_actual.toCancionMejor();
    mejores_canciones.Insert(mejor);
    
    // Para peores canciones
    CancionPeor peor = val_actual.toCancionPeor();
    peores_canciones.Insert(peor);
    
    // Manejar usuarios
    vector<string> canciones_usuario;
    if (usuarios.find(usuario, canciones_usuario)) {
        if (find(canciones_usuario.begin(), canciones_usuario.end(), cancion) == canciones_usuario.end()) {
            canciones_usuario.push_back(cancion);
            usuarios.insert(usuario, canciones_usuario);
        }
    } else {
        canciones_usuario.push_back(cancion);
        usuarios.insert(usuario, canciones_usuario);
    }
}

vector<CancionMejor> GestorMusica::getMejores10() {
    return mejores_canciones.getTop(10);
}

vector<CancionPeor> GestorMusica::getPeores10() {
    return peores_canciones.getTop(10);
}

void GestorMusica::mostrarEstadisticas() const {
    cout << "\n=== ESTADÍSTICAS DEL GESTOR DE MÚSICA ===" <<endl;
    cout << "Total de canciones en sistema: " << valoraciones_por_cancion.size() << endl;
    cout << "Total de usuarios: " << usuarios.size() << endl;
    
    cout << "\n--- TOP 10 MEJORES CANCIONES ---" << endl;
    auto mejores = const_cast<GestorMusica*>(this)->getMejores10();
    for (size_t i = 0; i < mejores.size(); i++) {
        cout << (i+1) << ". " << mejores[i].codigo_cancion 
                  << " - Promedio: " << mejores[i].promedio 
                  << " (" << mejores[i].num_valoraciones << " valoraciones)" << endl;
    }
    
    cout << "\n--- TOP 10 PEORES CANCIONES ---" << endl;
    auto peores = const_cast<GestorMusica*>(this)->getPeores10();
    for (size_t i = 0; i < peores.size(); i++) {
        cout << (i+1) << ". " << peores[i].codigo_cancion 
                  << " - Promedio: " << peores[i].promedio 
                  << " (" << peores[i].num_valoraciones << " valoraciones)" << endl;
    }
}

void GestorMusica::mostrarEstadisticasBTree() const {
    cout << "\n=== ESTADÍSTICAS B-TREE ===" << endl;
    cout << "Elementos en B-Tree mejores: " << mejores_canciones.getCount() << endl;
    cout << "Elementos en B-Tree peores: " << peores_canciones.getCount() << endl;
}

// Instanciaciones explícitas para el template
template class HashTable<string, ValoracionCancion>;
template class HashTable<string, vector<string>>;
template class BTree<CancionMejor, 20>;
template class BTree<CancionPeor, 20>;
template class Node<CancionMejor, 20>;
template class Node<CancionPeor, 20>;
