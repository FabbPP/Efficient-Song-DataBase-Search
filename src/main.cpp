// main.cpp
#include "../include/gestor_musica.h"
#include <iostream>
#include <string>

int main() {
    cout << "=== GESTOR MUSICAL ===" << endl;
    GestorMusica gestor;
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo CSV. Ingresa ratings.csv: ";
    getline(cin, nombreArchivo);
    if (gestor.cargarCSV(nombreArchivo)) {
        gestor.mostrarEstadisticas();
        char opcion;
        do {
            cout << "\n=== MENÚ ===" << endl;
            cout << "1. Mostrar mejores 10 canciones" << endl;
            cout << "2. Mostrar peores 10 canciones" << endl;
            cout << "3. Buscar canción por código" << endl;
            cout << "4. Mostrar estadísticas completas" << endl;
            cout << "5. Mostrar contenido del B-Tree" << endl;
            cout << "0. Salir" << endl;
            cout << "Seleccione una opción: ";
            cin >> opcion;
            cin.ignore(); // Limpiar buffer
            
            switch (opcion) {
                case '1': {
                    cout << "\n=== MEJORES 10 CANCIONES ===" << endl;
                    auto mejores = gestor.getMejores10();
                    for (size_t i = 0; i < mejores.size(); i++) {
                        cout << (i + 1) << ". ";
                        mejores[i].print();
                    }
                    break;
                }
                case '2': {
                    cout << "\n=== PEORES 10 CANCIONES ===" << endl;
                    auto peores = gestor.getPeores10();
                    for (size_t i = 0; i < peores.size(); i++) {
                        cout << (i + 1) << ". ";
                        peores[i].print();
                    }
                    break;
                }
                case '3': {
                    cout<<"Falta implemnetar";
                }
                case '4':
                    gestor.mostrarEstadisticas();
                    break;
                case '5':
                    gestor.mostrarBTree();
                    break;
                case '0':
                    cout << "Gracias Bornas" << endl;
                    break;
                default:
                    cout << "Vuelve a ingresar la opcion correcta" << endl;
            }
        } while (opcion != '0');
        
    } else {
        cout << "error, jalaste"<<endl;
    }

    return 0;
}