// include/structures/hash_table.h
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <string>
#include <functional>
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

// Especialización para strings (función hash)
template<>
size_t HashTable<std::string, Cancion*>::hash_function(const std::string& key) const;


class MusicHashTable {
private:
    HashTable<std::string, Cancion*> codigo_table;  // codigo cancion
    HashTable<std::string, std::vector<Cancion*>*> usuario_table;  // codigo usuario
    
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
    
    // Estadísticas
    size_t numCancionesPorCodigo() const { return codigo_table.size(); }
    size_t numUsuarios() const { return usuario_table.size(); }
};

#endif // HASH_TABLE_H