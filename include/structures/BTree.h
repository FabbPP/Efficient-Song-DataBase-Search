#ifndef BTREE_H
#define BTREE_H
#include "../include/structures/Node.h"
#include <vector>  // Asegúrate de incluir vector
using namespace std;

template <class T, int Order>
class BTree {
private:
    Node<T, Order>* root;
    int order;
    int count = 0;

public:
    BTree();
    void Insert(T value);
    void Print() const;
    vector<T> getTop(int n) const; // Obtener los primeros elementos del árbol
    vector<T> getBottom(int n) const; //Obtener los ultimos elementos (peores)
    int getCount() const { return count; }
    ~BTree();
};
#endif  // BTREE_H
