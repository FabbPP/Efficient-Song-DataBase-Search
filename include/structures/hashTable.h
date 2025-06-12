#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <functional>

template<typename K, typename V>
class HashTable {
private:
    struct HashNode {
        K key;
        V value;
        HashNode(const K& k, const V& v) : key(k), value(v) {}
    };
    std::vector<std::list<HashNode>> table;
    size_t table_size;
    size_t num_elements;
    size_t hash(const K& key) const;
    void rehash();

public:
    HashTable(size_t size = 101);
    void insert(const K& key, const V& value);
    bool find(const K& key, V& value) const;
    bool remove(const K& key);
    
    size_t size() const { return num_elements; }
    bool empty() const { return num_elements == 0; }
    void clear();
    void print() const;
};

#endif