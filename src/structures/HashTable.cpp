#include "../../include/structures/HashTable.h"
#include <iostream>

template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size) : table_size(size), num_elements(0) {
    table.resize(table_size);
}

template<typename K, typename V>
size_t HashTable<K, V>::hash(const K& key) const {
    return std::hash<K>{}(key) % table_size;
}

template<typename K, typename V>
void HashTable<K, V>::rehash() {
    if (num_elements > table_size * 0.75) {
        std::vector<std::list<HashNode>> old_table = table;
        size_t old_size = table_size;
        
        table_size *= 2;
        table.clear();
        table.resize(table_size);
        num_elements = 0;
        
        for (auto& bucket : old_table) {
            for (auto& node : bucket) {
                insert(node.key, node.value);
            }
        }
        
        std::cout << "HashTable rehashed from " << old_size << " to " << table_size << std::endl;
    }
}

template<typename K, typename V>
void HashTable<K, V>::insert(const K& key, const V& value) {
    size_t index = hash(key);
    auto& bucket = table[index];
    for (auto& node : bucket) {
        if (node.key == key) {
            node.value = value; 
            return;
        }
    }
    bucket.emplace_back(key, value);
    num_elements++;
    rehash();
}

template<typename K, typename V>
bool HashTable<K, V>::find(const K& key, V& value) const {
    size_t index = hash(key);
    const auto& bucket = table[index];
    
    for (const auto& node : bucket) {
        if (node.key == key) {
            value = node.value;
            return true;
        }
    }
    return false;
}
template<typename K, typename V>
bool HashTable<K, V>::remove(const K& key) {
    size_t index = hash(key);
    auto& bucket = table[index];
    
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->key == key) {
            bucket.erase(it);
            num_elements--;
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
void HashTable<K, V>::clear() {
    for (auto& bucket : table) {
        bucket.clear();
    }
    num_elements = 0;
}

template<typename K, typename V>
void HashTable<K, V>::print() const {
    std::cout << "HashTable Stats:" << std::endl;
    std::cout << "Size: " << num_elements << std::endl;
    std::cout << "Table Size: " << table_size << std::endl;
    std::cout << "Load Factor: " << (double)num_elements / table_size << std::endl;
    
    int used_buckets = 0;
    for (const auto& bucket : table) {
        if (!bucket.empty()) {
            used_buckets++;
        }
    }
    std::cout << "Used Buckets: " << used_buckets << "/" << table_size << std::endl;
}

template class HashTable<std::string, class ValoracionCancion>;
template class HashTable<std::string, std::vector<std::string>>;
