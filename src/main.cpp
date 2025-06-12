#include "../../include/gestor_musica.h"
#include <iostream>
using namespace std;
int main(){
    cout<<"Bienvenido a Sistema lector de canciones y consultas"<<endl;
    //Conseguir canciones leer archivo
    GestorMusica gestor;
    string archivo;
    cout << "Ingrese el nombre del archivo CSV: ";
    getline(cin, archivo);
    if (gestor.cargarCSV(archivo)) {        
        gestor.mostrarEstadisticas();
        gestor.mostrarEstadisticasBTree();
        
    //Menu para hacer consultar
    //Mostrar 10 mejores canciones
    //Mostrar 10 peores canciones
    //Buscar valoraciones por cancion (codigo) y recuperar su promedio y numero de valoraciones
    //opcion de recomendar uan cancion segun usuario consiguiendo usuarios con gustos parecidos..(aun no implementada solo imprimor usaremos Priprity queue)
    return 0;

}
