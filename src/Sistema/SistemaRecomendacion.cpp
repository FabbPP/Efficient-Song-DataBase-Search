#include "../include/structures/BTree.h"
#include "../include/gestor_musica.h"
#include <fstream>
#include <sstream>
#include <iostream>

GestorMusica::GestorMusica() {}

GestorMusica::~GestorMusica() {}

bool GestorMusica::cargarCSV(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        return false;
    }
    
    string linea;
    int lineas_procesadas = 0;
    
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        
        stringstream ss(linea);
        string codigo_usuario, codigo_cancion, valoracion_str, coordenada_str;
        
        if (getline(ss, codigo_usuario, ',') &&
            getline(ss, codigo_cancion, ',') &&
            getline(ss, valoracion_str, ',') &&
            getline(ss, coordenada_str)) {
            
            try {
                double valoracion = stod(valoracion_str);
                double coordenada = stod(coordenada_str);
                
                procesarRegistro(codigo_usuario, codigo_cancion, valoracion, coordenada);
                lineas_procesadas++;
            } catch (const exception& e) {
                cerr << "Error procesando línea: " << linea << " - " << e.what() << endl;
            }
        }
    }
    
    file.close();
    cout << "Archivo cargado exitosamente. Líneas procesadas: " << lineas_procesadas << endl;
    
    // Reconstruir B-Tree después de cargar todos los datos
    reconstruirBTree();
    return true;
}

vector<Cancion> GestorMusica::getMejores10() {
    return btree_canciones.getTop(10);
}

vector<Cancion> GestorMusica::getPeores10() {
    return btree_canciones.getBottom(10);
}



void GestorMusica::mostrarEstadisticas() {
    cout << "\n=== ESTADISTICAS DEL GESTOR MUSICAL ===" << endl;
    cout << "Elementos en B-Tree: " << btree_canciones.getCount() << endl;
    
    cout << "\n=== TOP 10 MEJORES CANCIONES ===" << endl;
    auto mejores = getMejores10();
    for (size_t i = 0; i < mejores.size(); i++) {
        cout << (i + 1) << ". ";
        mejores[i].print();
    }
    
    cout << "\n=== TOP 10 PEORES CANCIONES ===" << endl;
    auto peores = getPeores10();
    for (size_t i = 0; i < peores.size(); i++) {
        cout << (i + 1) << ". ";
        peores[i].print();
    }
}

void GestorMusica::mostrarBTree() {
    cout << "\n=== CONTENIDO DEL B-TREE (Orden de insercion) ===" << endl;
    btree_canciones.Print();
}
