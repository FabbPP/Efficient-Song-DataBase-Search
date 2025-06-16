#include "SistemaRecomendacion.h"
#include <cmath>

bool SistemaRecomendacion::procesarLinea(const string& linea) {
    stringstream ss(linea);
    string codigoUsuario, codigoCancion, valoracionStr, coordenadaStr;

    if (!getline(ss, codigoUsuario, ',') ||
        !getline(ss, codigoCancion, ',') ||
        !getline(ss, valoracionStr, ',') ||
        !getline(ss, coordenadaStr, ',')) {
        return false;
    }

    try {
        double valoracion = stod(valoracionStr);
        double coordenadaX = stod(coordenadaStr);

        Valoracion val(codigoUsuario, codigoCancion, valoracion, coordenadaX);

        if (usuarios.find(codigoUsuario) == usuarios.end()) {
            usuarios[codigoUsuario] = Usuario(codigoUsuario);
        }
        usuarios[codigoUsuario].agregarValoracion(val);

        if (canciones.find(codigoCancion) == canciones.end()) {
            canciones[codigoCancion] = Cancion(codigoCancion);
        }
        canciones[codigoCancion].agregarValoracion(val);

        return true;
    } catch (const exception& e) {
        return false;
    }
}

double SistemaRecomendacion::calcularDistanciaManhattan(const Cancion& c1, const Cancion& c2) {
    const auto& vals1 = c1.getValoraciones();
    const auto& vals2 = c2.getValoraciones();

    if (vals1.empty() || vals2.empty()) {
        return numeric_limits<double>::max();
    }

    double sumaDistancias = 0.0;
    int comparaciones = 0;

    for (const auto& val1 : vals1) {
        for (const auto& val2 : vals2) {
            if (val1.codigoUsuario == val2.codigoUsuario) {
                sumaDistancias += abs(val1.valoracion - val2.valoracion);
                comparaciones++;
            }
        }
    }

    return comparaciones > 0 ? sumaDistancias / comparaciones : 
                               numeric_limits<double>::max();
}

bool SistemaRecomendacion::leerCSV(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir archivo: " << nombreArchivo << endl;
        return false;
    }

    string linea;
    size_t lineasProcesadas = 0;

    while (getline(archivo, linea)) {
        if (!procesarLinea(linea)) {
            cerr << "Error procesando linea: " << linea << endl;
        } else {
            lineasProcesadas++;
        }
    }

    archivo.close();
    actualizarBTree();
    return true;
}

void SistemaRecomendacion::actualizarBTree() {
    btreeValoraciones = BTree<CancionValoracion, 5>();
    for (const auto& par : canciones) {
        CancionValoracion cv(par.first, par.second.getPromedioValoracion());
        btreeValoraciones.Insert(cv);
    }
}

vector<string> SistemaRecomendacion::mejoresCanciones(int cantidad) {
    vector<CancionValoracion> mejores = btreeValoraciones.getTopN(cantidad);
    vector<string> resultado;
    for (const auto& cv : mejores) {
        resultado.push_back(cv.codigoCancion);
    }
    return resultado;
}

vector<string> SistemaRecomendacion::peoresCanciones(int cantidad) {
    vector<CancionValoracion> peores = btreeValoraciones.getBottomN(cantidad);
    vector<string> resultado;
    for (const auto& cv : peores) {
        resultado.push_back(cv.codigoCancion);
    }
    return resultado;
}

vector<string> SistemaRecomendacion::cancionesSimilares(const string& codigoCancion, int cantidad) {
    if (canciones.find(codigoCancion) == canciones.end()) {
        return {};
    }

    const Cancion& cancionBase = canciones[codigoCancion];
    vector<pair<string, double>> distancias;

    for (const auto& par : canciones) {
        if (par.first == codigoCancion) continue;
        double distancia = calcularDistanciaManhattan(cancionBase, par.second);
        if (distancia != numeric_limits<double>::max()) {
            distancias.push_back({par.first, distancia});
        }
    }

    sort(distancias.begin(), distancias.end(), 
         [](const auto& a, const auto& b) { return a.second < b.second; });

    vector<string> resultado;
    for (int i = 0; i < min(cantidad, (int)distancias.size()); i++) {
        resultado.push_back(distancias[i].first);
    }

    return resultado;
}

vector<string> SistemaRecomendacion::recomendarCanciones(const string& codigoUsuario, int cantidad) {
    if (usuarios.find(codigoUsuario) == usuarios.end()) {
        return {};
    }

    const Usuario& usuarioBase = usuarios[codigoUsuario];
    vector<pair<string, double>> usuariosSimilares;

    for (const auto& par : usuarios) {
        if (par.first == codigoUsuario) continue;
        double similaridad = usuarioBase.calcularSimilaridad(par.second);
        if (similaridad > 0) {
            usuariosSimilares.push_back({par.first, similaridad});
        }
    }

    sort(usuariosSimilares.begin(), usuariosSimilares.end(),
         [](const auto& a, const auto& b) { return a.second > b.second; });

    map<string, double> cancionesRecomendadas;
    int usuariosConsiderados = min(10, (int)usuariosSimilares.size());

    for (int i = 0; i < usuariosConsiderados; i++) {
        const Usuario& usuarioSimilar = usuarios[usuariosSimilares[i].first];
        double pesoSimilaridad = usuariosSimilares[i].second;

        for (const auto& valPar : usuarioSimilar.getValoraciones()) {
            const string& codigoCancion = valPar.first;
            if (!usuarioBase.tieneValoracion(codigoCancion)) {
                cancionesRecomendadas[codigoCancion] += valPar.second.valoracion * pesoSimilaridad;
            }
        }
    }

    vector<pair<string, double>> ranking(cancionesRecomendadas.begin(), cancionesRecomendadas.end());
    sort(ranking.begin(), ranking.end(),
         [](const auto& a, const auto& b) { return a.second > b.second; });

    vector<string> resultado;
    for (int i = 0; i < min(cantidad, (int)ranking.size()); i++) {
        resultado.push_back(ranking[i].first);
    }

    return resultado;
}

void SistemaRecomendacion::mostrarEstadisticas() {
    cout << "\n------- ESTADISTICAS DEL SISTEMA -------" << endl;
    cout << "Total de usuarios: " << usuarios.size() << endl;
    cout << "Total de canciones: " << canciones.size() << endl;
    cout << "\nEstructura del B-Tree de valoraciones:" << endl;
    btreeValoraciones.Print();
}