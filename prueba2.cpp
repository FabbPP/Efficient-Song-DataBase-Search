#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

// Implementacion de B-Tree
template<class T,int Order>
struct Node
{
    int number_of_keys;
    int order;
    int position=-1;
    T* keys;
    Node** children;

    explicit Node (int order);
    int Insert (T value);
    Node* split (Node* node, T* med);
    void Print () ;
    void PrintUtil (int height,bool checkRoot);
    int getHeight () ;
    void collectInOrder(vector<T>& result);
    void collectReverseOrder(vector<T>& result);
    ~Node ();
};

template <class T,int Order>
Node<T,Order>::Node (int order)
{
    this->order = order;
    this->number_of_keys = 0;
    this->keys = new T[this->order];
    this->children = new Node*[this->order + 1];
    for (int i = 0; i <= this->order; ++i)
        this->children[i] = nullptr;
}

template <class T,int Order>
int Node<T,Order>::Insert (T value)
{
    if (this->children[0] == nullptr)
    {
        this->keys[++this->position] = value;
        ++this->number_of_keys;
        for(int i=this->position; i>0 ; i--)
            if (this->keys[i] < this->keys[i-1])
                std::swap(this->keys[i],this->keys[i-1]);
    }
    else
    {
        int i=0;
        for(; i<this->number_of_keys && value > this->keys[i];)
            i++;

        int check=this->children[i]->Insert(value);
        if(check)
        {
            T mid;
            int TEMP = i;
            Node<T,Order> *newNode = split(this->children[i], &mid);
            for(; i<this->number_of_keys && mid > this->keys[i];)
                i++;

            for (int j = this->number_of_keys; j > i ; j--)
                this->keys[j] = this->keys[j - 1];
            this->keys[i] = mid;
            ++this->number_of_keys;
            ++this->position;

            int k;
            for (k = this->number_of_keys; k > TEMP + 1; k--)
                this->children[k] = this->children[k - 1];
            this->children[k] = newNode;
        }
    }
    if(this->number_of_keys == this->order)
        return 1;
    else return 0;
}

template <class T,int Order>
Node<T,Order>* Node<T,Order>::split (Node *node, T *med)
{
    int NumberOfKeys = node->number_of_keys;
    auto *newNode = new Node<T,Order>(order);
    int midValue = NumberOfKeys / 2;
    *med = node->keys[midValue];
    int i;
    for (i = midValue + 1; i < NumberOfKeys; ++i)
    {
        newNode->keys[++newNode->position] = node->keys[i];
        newNode->children[newNode->position] = node->children[i];
        ++newNode->number_of_keys;
        --node->position;
        --node->number_of_keys;
        node->children[i] = nullptr;
    }
    newNode->children[newNode->position + 1] = node->children[i];
    node->children[i] = nullptr;

    --node->number_of_keys;
    --node->position;
    return newNode;
}

template <class T,int Order>
void Node<T,Order>::Print ()
{
    int height = this->getHeight();
    for (int i = 1; i <= height; ++i)
    {
        if(i==1)PrintUtil(i,true);
        else PrintUtil(i,false);
        cout<<endl;
    }
    cout<<endl;
}

template <class T,int Order>
void Node<T,Order>::PrintUtil (int height,bool checkRoot)
{
    if (height==1 || checkRoot)
    {
        for (int i = 0; i < this->number_of_keys; i++){
             if(i==0) cout << "|";
             cout<< this->keys[i];
             if(i!=this->number_of_keys-1) cout<<"|";
             if(i==this->number_of_keys-1) cout << "|"<<" ";
        }
    }
    else
    {
        for (int i = 0; i <= this->number_of_keys; i++)
            this->children[i]->PrintUtil(height - 1, false);
    }
}

template <class T,int Order>
int Node<T,Order>::getHeight ()
{
    int COUNT=1;
    Node<T,Order>* Current=this;
    while(true){
        if(Current->children[0] == nullptr)
            return COUNT;
        Current=Current->children[0];
        COUNT++;
    }
}

// Metodos añadidos para recolectar elementos en orden
template <class T,int Order>
void Node<T,Order>::collectInOrder(vector<T>& result)
{
    if (this->children[0] == nullptr) // Es hoja
    {
        for (int i = 0; i < this->number_of_keys; i++)
            result.push_back(this->keys[i]);
    }
    else // No es hoja
    {
        for (int i = 0; i <= this->number_of_keys; i++)
        {
            if (this->children[i] != nullptr)
                this->children[i]->collectInOrder(result);
            if (i < this->number_of_keys)
                result.push_back(this->keys[i]);
        }
    }
}

template <class T,int Order>
void Node<T,Order>::collectReverseOrder(vector<T>& result)
{
    if (this->children[0] == nullptr) // Es hoja
    {
        for (int i = this->number_of_keys - 1; i >= 0; i--)
            result.push_back(this->keys[i]);
    }
    else // No es hoja
    {
        for (int i = this->number_of_keys; i >= 0; i--)
        {
            if (i < this->number_of_keys)
                result.push_back(this->keys[i]);
            if (this->children[i] != nullptr)
                this->children[i]->collectReverseOrder(result);
        }
    }
}

template <class T,int Order>
Node<T,Order>::~Node ()
{
    delete[]keys;
    for (int i = 0; i <= this->number_of_keys; ++i)
        delete children[i];
    delete[] children;
}

template <class T,int Order>
class BTree
{
private:
    Node<T,Order> *root;
    int order;
    int count=0;

public:
    BTree ();
    void Insert (T value);
    void Print () const;
    vector<T> getTopN(int n); // Mejores n elementos
    vector<T> getBottomN(int n); // Peores n elementos
    ~BTree ();
};

template <class T,int Order>
BTree<T,Order>::BTree()
{
    this->order = Order;
    this->root  = nullptr;
    this->count=0;
}

template <class T,int Order>
void BTree<T,Order>::Insert (T value)
{
    count++;
    if (this->root == nullptr)
    {
        this->root = new Node<T,Order>(this->order);
        this->root->keys[++this->root->position]=value;
        this->root->number_of_keys=1;
    }
    else
    {
        int check=root->Insert(value);
        if(check){
            T mid;
            Node<T,Order> *splitNode = this->root->split(this->root, &mid);
            auto *newNode = new Node<T,Order>(this->order);
            newNode->keys[++newNode->position]=mid;
            newNode->number_of_keys=1;
            newNode->children[0] = root;
            newNode->children[1] = splitNode;
            this->root = newNode;
        }
    }
}

template <class T,int Order>
void BTree<T,Order>::Print () const
{
    if (root != nullptr)
        root->Print();
    else cout<<"The B-Tree is Empty"<<endl;
}

template <class T,int Order>
vector<T> BTree<T,Order>::getTopN(int n)
{
    vector<T> allElements;
    if (root != nullptr)
        root->collectReverseOrder(allElements); // Orden descendente para mejores
    
    vector<T> result;
    for (int i = 0; i < min(n, (int)allElements.size()); i++)
        result.push_back(allElements[i]);
    
    return result;
}

template <class T,int Order>
vector<T> BTree<T,Order>::getBottomN(int n)
{
    vector<T> allElements;
    if (root != nullptr)
        root->collectInOrder(allElements); // Orden ascendente para peores
    
    vector<T> result;
    for (int i = 0; i < min(n, (int)allElements.size()); i++)
        result.push_back(allElements[i]);
    
    return result;
}

template <class T,int Order>
BTree<T,Order>::~BTree ()
{
    delete root;
}
//Hasta aquie es Btree-------------------------------------------------------------------

// Estructura para almacenar cancion con su valoracion promedio
struct CancionValoracion {
    string codigoCancion;
    double valoracionPromedio;
    
    CancionValoracion() : codigoCancion(""), valoracionPromedio(0.0) {}
    CancionValoracion(const string& codigo, double val) 
        : codigoCancion(codigo), valoracionPromedio(val) {}
    
    // Operadores para el B-Tree
    bool operator<(const CancionValoracion& other) const {
        return valoracionPromedio < other.valoracionPromedio;
    }
    
    bool operator>(const CancionValoracion& other) const {
        return valoracionPromedio > other.valoracionPromedio;
    }
    
    friend ostream& operator<<(ostream& os, const CancionValoracion& cv) {
        os << cv.codigoCancion << "(" << fixed << setprecision(2) << cv.valoracionPromedio << ")";
        return os;
    }
};

struct Valoracion {
    string codigoUsuario;
    string codigoCancion;
    double valoracion;
    double coordenadaX;
    
    Valoracion() : valoracion(0.0), coordenadaX(0.0) {}
    Valoracion(const string& usuario, const string& cancion, 
               double val, double x) 
        : codigoUsuario(usuario), codigoCancion(cancion), 
          valoracion(val), coordenadaX(x) {}
};

class Usuario {
private:
    string codigo;
    map<string, Valoracion> valoraciones;
    
public:
    Usuario() = default;
    Usuario(const string& cod) : codigo(cod) {}
    
    void agregarValoracion(const Valoracion& val) {
        valoraciones[val.codigoCancion] = val;
    }
    
    string getCodigo() const { return codigo; }
    
    const map<string, Valoracion>& getValoraciones() const {
        return valoraciones;
    }
    
    bool tieneValoracion(const string& codigoCancion) const {
        return valoraciones.find(codigoCancion) != valoraciones.end();
    }
    
    Valoracion getValoracion(const string& codigoCancion) const {
        return valoraciones.at(codigoCancion);
    }
    
    double calcularSimilaridad(const Usuario& otro) const {
        double distanciaManhattan = 0.0;
        int cancionesComunes = 0;

        
  
        for (const auto& par : valoraciones) {
            const string& codigoCancion = par.first;
            const Valoracion& valoracion1 = par.second;

            if (otro.tieneValoracion(codigoCancion)) {
                const Valoracion& valoracion2 = otro.getValoracion(codigoCancion);
                double diff = abs(valoracion1.valoracion - valoracion2.valoracion);
                distanciaManhattan += diff;
                cancionesComunes++;
            }
        }
        
        
        if (cancionesComunes == 0) return 0.0;
        cout<<"caniconesComunes "<<cancionesComunes<<"distancia"<<distanciaManhattan<<"\n";
        double respuesta = 1.0 / (1.0 + distanciaManhattan / cancionesComunes);
        if (respuesta == 1 ){
            cout<<"caniconesComunes "<<cancionesComunes<<"distancia"<<distanciaManhattan<<"\n";
            cout<<"respuesta"<<respuesta<<"\n";
        }

        return respuesta;
    }
};

class Cancion {
private:
    string codigo;
    vector<Valoracion> valoraciones;
    double promedioValoracion;
    
public:
    Cancion() : promedioValoracion(0.0) {} 
    Cancion(const string& cod) : codigo(cod), promedioValoracion(0.0) {}
    
    void agregarValoracion(const Valoracion& val) {
        valoraciones.push_back(val);
        calcularPromedio();
    }
    
    string getCodigo() const { return codigo; }
    double getPromedioValoracion() const { return promedioValoracion; }
    
    const vector<Valoracion>& getValoraciones() const {
        return valoraciones;
    }
    
private:
    void calcularPromedio() {
        if (valoraciones.empty()) {
            promedioValoracion = 0.0;
            return;
        }
        
        double suma = 0.0;
        for (const auto& val : valoraciones) {
            suma += val.valoracion;
        }
        //promedioValoracion = suma / valoraciones.size();//promedio de valoraciones
        promedioValoracion = suma;// solo l asuma de las valoraciones para ordenar asi en el btree
    }
};

class SistemaRecomendacion {
private:
    unordered_map<string, Usuario> usuarios;
    unordered_map<string, Cancion> canciones;
    BTree<CancionValoracion, 5> btreeValoraciones; // B-Tree de orden 5
    
public:
    bool leerCSV(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cerr << "Error al abrir archivo: " << nombreArchivo << endl;
            return false;
        }
        
        string linea;
        while (getline(archivo, linea)) {
            if (!procesarLinea(linea)) {
                cerr << "Error procesando linea: " << linea << endl;
            }
        }
        
        archivo.close();
        actualizarBTree();
        return true;
    }
    
    bool procesarLinea(const string& linea) {
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
    
    void actualizarBTree() {
        for (const auto& par : canciones) {
            CancionValoracion cv(par.first, par.second.getPromedioValoracion());

            btreeValoraciones.Insert(cv);
        }
    }
    
    vector<string> mejoresCanciones(int cantidad = 10) {
        vector<CancionValoracion> mejores = btreeValoraciones.getTopN(cantidad);
        vector<string> resultado;
        for (const auto& cv : mejores) {
            resultado.push_back(cv.codigoCancion);
        }
        return resultado;
    }
    
    vector<string> peoresCanciones(int cantidad = 10) {
        vector<CancionValoracion> peores = btreeValoraciones.getBottomN(cantidad);
        vector<string> resultado;
        for (const auto& cv : peores) {
            resultado.push_back(cv.codigoCancion);
        }
        return resultado;
    }
    
    vector<string> cancionesSimilares(const string& codigoCancion, int cantidad = 10) {
        if (canciones.find(codigoCancion) == canciones.end()) {
            return {};
        }
        cout<<"entro a canciones similares\n";
        
        const Cancion& cancionBase = canciones[codigoCancion];
        vector<pair<string, double>> distancias;
        
        for (const auto& par : canciones) {
            cout<<"entro a canciones similares / for \n";
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
    
    vector<string> recomendarCanciones(const string& codigoUsuario, int cantidad = 5) {
        if (usuarios.find(codigoUsuario) == usuarios.end()) {//verificar que existe
            cout<<"No existe usuario";
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
                    cancionesRecomendadas[codigoCancion] += 
                        valPar.second.valoracion * pesoSimilaridad;
                }
            }
        }
        
        vector<pair<string, double>> ranking(
            cancionesRecomendadas.begin(), cancionesRecomendadas.end());
        
        sort(ranking.begin(), ranking.end(),
             [](const auto& a, const auto& b) { return a.second > b.second; });
        
        vector<string> resultado;
        for (int i = 0; i < min(cantidad, (int)ranking.size()); i++) {
            resultado.push_back(ranking[i].first);
        }
        
        return resultado;
    }
    
    void mostrarEstadisticas() {
        cout << "\n------- ESTADISTICAS DEL SISTEMA -------" << endl;
        cout << "Total de usuarios: " << usuarios.size() << endl;
        cout << "Total de canciones: " << canciones.size() << endl;
        cout << "\nEstructura del B-Tree de valoraciones:" << endl;
        btreeValoraciones.Print();
    }
    
private:
    double calcularDistanciaManhattan(const Cancion& c1, const Cancion& c2) {
        //obetnemos las valoraciones de las canciones a comparar
        const auto& vals1 = c1.getValoraciones();
        const auto& vals2 = c2.getValoraciones();
        
        if (vals1.empty() || vals2.empty()) {
            return numeric_limits<double>::max();
            //si es maxima es que es muy difrente
        }
        
        double sumaDistancias = 0.0;
        int comparaciones = 0;
        
        for (const auto& val1 : vals1) {
            for (const auto& val2 : vals2) {
                if (val1.codigoUsuario == val2.codigoUsuario) {
                    cout<<val1.codigoUsuario<<"-\n ";
                    sumaDistancias += abs(val1.valoracion - val2.valoracion);
                    comparaciones++;
                }
            }
        }
        
        return comparaciones > 0 ? sumaDistancias / comparaciones : 
                                   numeric_limits<double>::max();
    }
};

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
    
    cout << "Bienvenido al Sistema de Recomendacion Musical" << endl;
    
    do {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                string nombreArchivo;
                cout << "\nIngrese el nombre del archivo CSV: ";
                cin >> nombreArchivo;
                
                if (sistema.leerCSV(nombreArchivo)) {
                    cout << "Archivo cargado" << endl;
                    archivosCargados = true;
                } else {
                    cout << "Error al cargar el archivo." << endl;
                }
                break;
            }
            
            case 2: {
                if (!archivosCargados) {
                    cout << "Primero debe cargar un archivo CSV." << endl;
                    break;
                }
                
                int n;
                cout << "Cantidad de canciones que desea ver : ";
                cin >> n;
                
                auto mejores = sistema.mejoresCanciones(n);
                cout << "\n------- TOP " << n << " MEJORES CANCIONES -------" << endl;
                for (int i = 0; i < mejores.size(); i++) {
                    cout << (i+1) << ". " << mejores[i] << endl;
                }
                break;
            }
            
            case 3: {
                if (!archivosCargados) {
                    cout << "Primero debe cargar un archivo CSV." << endl;
                    break;
                }
                
                int n;
                cout << "Cantidad de canciones que desea ver : ";
                cin >> n;
                
                auto peores = sistema.peoresCanciones(n);
                cout << "\n------- TOP " << n << " PEORES CANCIONES -------" << endl;
                for (int i = 0; i < peores.size(); i++) {
                    cout << (i+1) << ". " << peores[i] << endl;
                }
                break;
            }
            
            case 4: {
                if (!archivosCargados) {
                    cout << "Primero debe cargar un archivo CSV." << endl;
                    break;
                }
                
                string codigoCancion;
                int n;
                cout << "Ingrese el codigo de la cancion: ";
                cin >> codigoCancion;
                cout << "Cantidad de canciones que desea ver : ";
                cin >> n;
                
                auto similares = sistema.cancionesSimilares(codigoCancion, n);
                if (similares.empty()) {
                    cout << "No se encontraron canciones similares o el codigo no existe." << endl;
                } else {
                    cout << "\n------- CANCIONES SIMILARES A " << codigoCancion << " -------" << endl;
                    for (int i = 0; i < similares.size(); i++) {
                        cout << (i+1) << ". " << similares[i] << endl;
                    }
                }
                break;
            }
            
            case 5: {
                if (!archivosCargados) {
                    cout << "Primero debe cargar un archivo CSV." << endl;
                    break;
                }
                
                string codigoUsuario;
                int n;
                cout << "Ingrese el codigo del usuario: ";
                cin >> codigoUsuario;
                cout << "Cantidad de canciones a recomendar : ";
                cin >> n;
                
                auto recomendaciones = sistema.recomendarCanciones(codigoUsuario, n);
                if (recomendaciones.empty()) {
                    cout << "No se encontro reomendaciones" << endl;
                } else {
                    cout << "\n------- RECOMENDACIONES PARA " << codigoUsuario << " -------" << endl;
                    for (int i = 0; i < recomendaciones.size(); i++) {
                        cout << (i+1) << ". " << recomendaciones[i] << endl;
                    }
                }
                break;
            }
            
            case 6: {
                if (!archivosCargados) {
                    cout << "Primero debe cargar un archivo CSV." << endl;
                    break;
                }
                
                sistema.mostrarEstadisticas();
                break;
            }
            
            case 7: {
                cout << "!Adios!" << endl;
                break;
            }
            
            default: {
                cout << "Opcion invalida. Por favor seleccione una opcion del 1-7." << endl;
                break;
            }
        }
        
        if (opcion != 7) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while (opcion != 7);
    
    return 0;
}
