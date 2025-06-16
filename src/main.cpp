#include <iostream>
#include "Sistema/SistemaRecomendacion.h"

void mostrarMenu() {
    cout << "\n===========================================" << endl;
    cout << "    SISTEMA DE RECOMENDACION MUSICAL" << endl;
    cout << "===========================================" << endl;
    cout << "1. Cargar archivo CSV" << endl;
    cout << "2. Mostrar mejores N canciones" << endl;
    cout << "3. Mostrar peores N canciones" << endl;
    cout << "4. Encontrar canciones similares" << endl;
    cout << "5. Recomendar canciones para usuario" << endl;
    cout << "6. Mostrar estadisticas y B-Tree" << endl;
    cout << "7. Salir" << endl;
    cout << "===========================================" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    SistemaRecomendacion sistema;
    int opcion;
    bool archivosCargados = false;

    do {
        mostrarMenu();
        cin >> opcion;

        switch(opcion) {
            case 1: {
                string nombreArchivo;
                cout << "Ingrese el nombre del archivo CSV: ";
                cin >> nombreArchivo;
                archivosCargados = sistema.leerCSV(nombreArchivo);
                break;
            }
            case 2: {
                if (!archivosCargados) {
                    cout << "Primero cargue un archivo CSV (opcion 1)." << endl;
                    break;
                }
                int cantidad;
                cout << "Cuantas canciones desea ver? ";
                cin >> cantidad;
                vector<string> mejores = sistema.mejoresCanciones(cantidad);
                cout << "\nTop " << cantidad << " mejores canciones:" << endl;
                for (const auto& cancion : mejores) {
                    cout << "- " << cancion << endl;
                }
                break;
            }
            case 3: {
                if (!archivosCargados) {
                    cout << "Primero cargue un archivo CSV (opcion 1)." << endl;
                    break;
                }
                int cantidad;
                cout << "Cuantas canciones desea ver? ";
                cin >> cantidad;
                vector<string> peores = sistema.peoresCanciones(cantidad);
                cout << "\nTop " << cantidad << " peores canciones:" << endl;
                for (const auto& cancion : peores) {
                    cout << "- " << cancion << endl;
                }
                break;
            }
            case 4: {
                if (!archivosCargados) {
                    cout << "Primero cargue un archivo CSV (opcion 1)." << endl;
                    break;
                }
                string codigoCancion;
                cout << "Ingrese el codigo de la cancion: ";
                cin >> codigoCancion;
                vector<string> similares = sistema.cancionesSimilares(codigoCancion);
                cout << "\nCanciones similares a " << codigoCancion << ":" << endl;
                for (const auto& cancion : similares) {
                    cout << "- " << cancion << endl;
                }
                break;
            }
            case 5: {
                if (!archivosCargados) {
                    cout << "Primero cargue un archivo CSV (opcion 1)." << endl;
                    break;
                }
                string codigoUsuario;
                cout << "Ingrese el codigo del usuario: ";
                cin >> codigoUsuario;
                vector<string> recomendaciones = sistema.recomendarCanciones(codigoUsuario);
                cout << "\nRecomendaciones para " << codigoUsuario << ":" << endl;
                for (const auto& cancion : recomendaciones) {
                    cout << "- " << cancion << endl;
                }
                break;
            }
            case 6: {
                if (!archivosCargados) {
                    cout << "Primero cargue un archivo CSV (opcion 1)." << endl;
                    break;
                }
                sistema.mostrarEstadisticas();
                break;
            }
            case 7: {
                cout << "Saliendo del sistema..." << endl;
                break;
            }
            default: {
                cout << "Opcion no valida. Intente de nuevo." << endl;
            }
        }
    } while(opcion != 7);

    return 0;
}