#include <iostream>
#include <vector> 
#include <string> 
#include <chrono> 
#include "Sistema/SistemaRecomendacion.h"

void mostrarMenu() {
    std::cout << "\n===========================================" << std::endl;
    std::cout << "    SISTEMA DE RECOMENDACION MUSICAL" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "1. Cargar archivo CSV" << std::endl;
    std::cout << "2. Mostrar mejores N canciones" << std::endl;
    std::cout << "3. Mostrar peores N canciones" << std::endl;
    std::cout << "4. Encontrar canciones similares" << std::endl;
    std::cout << "5. Recomendar canciones para usuario" << std::endl;
    std::cout << "6. Mostrar estadisticas y B-Tree" << std::endl;
    std::cout << "7. Salir" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "Seleccione una opcion: ";
}

int main() {
    SistemaRecomendacion sistema;
    int opcion;
    bool archivosCargados = false;

    do {
        mostrarMenu();
        std::cin >> opcion;

        switch(opcion) {
            case 1: {
                std::string nombreArchivo;
                std::cout << "Ingrese el nombre del archivo CSV: ";
                std::cin >> nombreArchivo;

                // --- Medición de tiempo para Cargar archivo CSV ---
                auto start_load = std::chrono::high_resolution_clock::now();
                archivosCargados = sistema.leerCSV(nombreArchivo);
                auto end_load = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration_load = end_load - start_load;
                std::cout << "Tiempo de carga del CSV: " << duration_load.count() << " segundos." << std::endl;
                // --- Fin de medición ---

                if (archivosCargados) {
                    std::cout << "Archivo CSV cargado exitosamente." << std::endl;
                } else {
                    std::cout << "Error al cargar el archivo CSV." << std::endl;
                }
                break;
            }
            case 2: {
                if (!archivosCargados) {
                    std::cout << "Primero cargue un archivo CSV (opcion 1)." << std::endl;
                    break;
                }
                int cantidad;
                std::cout << "Cuantas canciones desea ver? ";
                std::cin >> cantidad;

                // --- Medición de tiempo para Mejores N canciones ---
                auto start_topN = std::chrono::high_resolution_clock::now();
                std::vector<std::string> mejores = sistema.mejoresCanciones(cantidad);
                auto end_topN = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration_topN = end_topN - start_topN;
                // --- Fin de medición ---

                std::cout << "\nTop " << cantidad << " mejores canciones (Tiempo: " << duration_topN.count() << "s):" << std::endl;
                for (const auto& cancion : mejores) {
                    std::cout << "- " << cancion << std::endl;
                }
                break;
            }
            case 3: {
                if (!archivosCargados) {
                    std::cout << "Primero cargue un archivo CSV (opcion 1)." << std::endl;
                    break;
                }
                int cantidad;
                std::cout << "Cuantas canciones desea ver? ";
                std::cin >> cantidad;

                // --- Medición de tiempo para Peores N canciones ---
                auto start_bottomN = std::chrono::high_resolution_clock::now();
                std::vector<std::string> peores = sistema.peoresCanciones(cantidad);
                auto end_bottomN = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration_bottomN = end_bottomN - start_bottomN;
                // --- Fin de medición ---

                std::cout << "\nTop " << cantidad << " peores canciones (Tiempo: " << duration_bottomN.count() << "s):" << std::endl;
                for (const auto& cancion : peores) {
                    std::cout << "- " << cancion << std::endl;
                }
                break;
            }
            case 4: {
                if (!archivosCargados) {
                    std::cout << "Primero cargue un archivo CSV (opcion 1)." << std::endl;
                    break;
                }
                std::string codigoCancion;
                std::cout << "Ingrese el codigo de la cancion: ";
                std::cin >> codigoCancion;
                int cantidad_similares; // Añadimos una variable para la cantidad
                std::cout << "Cuantas canciones similares desea ver? (Default 10): ";
                std::cin >> cantidad_similares;
                if (cantidad_similares <= 0) cantidad_similares = 10; // Asegurar un valor válido

                // --- Medición de tiempo para Canciones Similares ---
                auto start_similar = std::chrono::high_resolution_clock::now();
                std::vector<std::string> similares = sistema.cancionesSimilares(codigoCancion, cantidad_similares);
                auto end_similar = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration_similar = end_similar - start_similar;
                // --- Fin de medición ---

                std::cout << "\nCanciones similares a " << codigoCancion << " (Tiempo: " << duration_similar.count() << "s):" << std::endl;
                if (similares.empty()) {
                    std::cout << "No se encontraron canciones similares o la cancion no existe." << std::endl;
                } else {
                    for (const auto& cancion : similares) {
                        std::cout << "- " << cancion << std::endl;
                    }
                }
                break;
            }
            case 5: {
                if (!archivosCargados) {
                    std::cout << "Primero cargue un archivo CSV (opcion 1)." << std::endl;
                    break;
                }
                std::string codigoUsuario;
                std::cout << "Ingrese el codigo del usuario: ";
                std::cin >> codigoUsuario;
                int cantidad_recomendaciones; // Añadimos una variable para la cantidad
                std::cout << "Cuantas recomendaciones desea ver? (Default 5): ";
                std::cin >> cantidad_recomendaciones;
                if (cantidad_recomendaciones <= 0) cantidad_recomendaciones = 5; // Asegurar un valor válido

                // --- Medición de tiempo para Recomendar Canciones ---
                auto start_recommend = std::chrono::high_resolution_clock::now();
                std::vector<std::string> recomendaciones = sistema.recomendarCanciones(codigoUsuario, cantidad_recomendaciones);
                auto end_recommend = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration_recommend = end_recommend - start_recommend;
                // --- Fin de medición ---

                std::cout << "\nRecomendaciones para " << codigoUsuario << " (Tiempo: " << duration_recommend.count() << "s):" << std::endl;
                if (recomendaciones.empty()) {
                    std::cout << "No se encontraron recomendaciones para este usuario o el usuario no existe." << std::endl;
                } else {
                    for (const auto& cancion : recomendaciones) {
                        std::cout << "- " << cancion << std::endl;
                    }
                }
                break;
            }
            case 6: {
                if (!archivosCargados) {
                    std::cout << "Primero cargue un archivo CSV (opcion 1)." << std::endl;
                    break;
                }
                sistema.mostrarEstadisticas();
                break;
            }
            case 7: {
                std::cout << "Saliendo del sistema..." << std::endl;
                break;
            }
            default: {
                std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
            }
        }
    } while(opcion != 7);

    return 0;
}

//----------------------------------------------------//
// Medición de tiempo para diferentes configuraciones //
//----------------------------------------------------//

// void medirTiempoLectura(const string& archivo, SistemaRecomendacion& sistema) {
//     vector<unsigned int> config_hilos = {1, 2, 4, 8, 16};
    
//     for (unsigned int hilos : config_hilos) {
//         auto start = std::chrono::high_resolution_clock::now();
//         sistema.leerCSV(archivo, hilos);
//         auto end = std::chrono::high_resolution_clock::now();
        
//         std::chrono::duration<double> elapsed = end - start;
//         cout << "Hilos: " << hilos 
//              << " | Tiempo: " << elapsed.count() << "s" 
//              << endl;
//     }
// }

// int main() {
//     SistemaRecomendacion sistema;
//     medirTiempoLectura("ratings_large.csv", sistema);
//     return 0;
// }
