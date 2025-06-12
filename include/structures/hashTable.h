// include/structures/hash_table.h
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include "../models/cancion.h"

template<typename K, typename V>
class HashTable {
private:
    struct HashNode {
        K key;
        V value;
        bool occupied;
        bool deleted;
        
        HashNode() : occupied(false), deleted(false) {}
        HashNode(const K& k, const V& v) : key(k), value(v), occupied(true), deleted(false) {}
    };
    
    std::vector<HashNode> table;
    size_t table_size;
    size_t num_elements;
    static const double MAX_LOAD_FACTOR;
    
    size_t hash_function(const K& key) const;
    size_t probe(const K& key, size_t attempt) const;
    void resize();
    bool need_resize() const;

public:
    HashTable(size_t initial_size = 16);
    ~HashTable();
    
    // Operaciones principales O(1) promedio
    bool insert(const K& key, const V& value);
    bool search(const K& key, V& value) const;
    bool remove(const K& key);
    bool update(const K& key, const V& value);
    
    // Utilidades
    size_t size() const { return num_elements; }
    bool empty() const { return num_elements == 0; }
    double load_factor() const { return static_cast<double>(num_elements) / table_size; }
    
    // Para debugging
    void print_stats() const;
};

// Definición de la constante estática
template<typename K, typename V>
const double HashTable<K, V>::MAX_LOAD_FACTOR = 0.75;

// Implementación de métodos template
template<typename K, typename V>
HashTable<K, V>::HashTable(size_t initial_size) : table_size(initial_size), num_elements(0) {
    table.resize(table_size);
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() {}

template<typename K, typename V>
size_t HashTable<K, V>::hash_function(const K& key) const {
    return std::hash<K>{}(key) % table_size;
}

template<typename K, typename V>
size_t HashTable<K, V>::probe(const K& key, size_t attempt) const {
    // Sondeo lineal
    return (hash_function(key) + attempt) % table_size;
}

template<typename K, typename V>
bool HashTable<K, V>::need_resize() const {
    return load_factor() > MAX_LOAD_FACTOR;
}

template<typename K, typename V>
void HashTable<K, V>::resize() {
    std::vector<HashNode> old_table = std::move(table);
    size_t old_size = table_size;
    
    table_size *= 2;
    num_elements = 0;
    table.clear();
    table.resize(table_size);
    
    // Reinsertar todos los elementos
    for (const auto& node : old_table) {
        if (node.occupied && !node.deleted) {
            insert(node.key, node.value);
        }
    }
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const K& key, const V& value) {
    if (need_resize()) {
        resize();
    }
    
    size_t attempt = 0;
    while (attempt < table_size) {
        size_t index = probe(key, attempt);
        
        if (!table[index].occupied || table[index].deleted) {
            table[index] = HashNode(key, value);
            num_elements++;
            return true;
        } else if (table[index].key == key) {
            // Clave ya existe
            return false;
        }
        attempt++;
    }
    return false; // Tabla llena
}

template<typename K, typename V>
bool HashTable<K, V>::search(const K& key, V& value) const {
    size_t attempt = 0;
    while (attempt < table_size) {
        size_t index = probe(key, attempt);
        
        if (!table[index].occupied) {
            return false; // No encontrado
        }
        
        if (table[index].key == key && !table[index].deleted) {
            value = table[index].value;
            return true;
        }
        attempt++;
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K& key) {
    size_t attempt = 0;
    while (attempt < table_size) {
        size_t index = probe(key, attempt);
        
        if (!table[index].occupied) {
            return false; // No encontrado
        }
        
        if (table[index].key == key && !table[index].deleted) {
            table[index].deleted = true;
            num_elements--;
            return true;
        }
        attempt++;
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::update(const K& key, const V& value) {
    size_t attempt = 0;
    while (attempt < table_size) {
        size_t index = probe(key, attempt);
        
        if (!table[index].occupied) {
            return false; // No encontrado
        }
        
        if (table[index].key == key && !table[index].deleted) {
            table[index].value = value;
            return true;
        }
        attempt++;
    }
    return false;
}

template<typename K, typename V>
void HashTable<K, V>::print_stats() const {
    std::cout << "Hash Table Stats:" << std::endl;
    std::cout << "  Size: " << table_size << std::endl;
    std::cout << "  Elements: " << num_elements << std::endl;
    std::cout << "  Load Factor: " << load_factor() << std::endl;
}

// Clase especializada para el gestor de música
class MusicHashTable {
private:
    HashTable<std::string, Cancion*> codigo_table;  // codigo cancion -> cancion
    HashTable<std::string, std::vector<Cancion*>*> usuario_table;  // codigo usuario -> lista canciones

public:
    MusicHashTable();
    ~MusicHashTable();
    
    // Operaciones para código de canción
    bool insertarPorCodigo(const std::string& codigo, Cancion* cancion);
    Cancion* buscarPorCodigo(const std::string& codigo) const;
    bool eliminarPorCodigo(const std::string& codigo);
    
    // Operaciones para usuario
    bool insertarPorUsuario(const std::string& usuario, Cancion* cancion);
    std::vector<Cancion*>* buscarPorUsuario(const std::string& usuario) const;
    bool eliminarCancionDeUsuario(const std::string& usuario, const std::string& codigo);
    
    // Búsqueda de similitud usando distancia Manhattan
    std::vector<std::pair<Cancion*, double>> buscarSimilares(const Cancion& cancion_base, size_t max_resultados = 10) const;
    
    // Estadísticas
    size_t numCancionesPorCodigo() const { return codigo_table.size(); }
    size_t numUsuarios() const { return usuario_table.size(); }
    void printStats() const;
};

#endif // HASH_TABLE_H
