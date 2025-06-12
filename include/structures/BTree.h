#include "Node.h"

template <class T,int Order>
class BTree
{
private:
    Node<T,Order> *root;
    int order;
    int count=0; // Contador para contar el número de elementos

public:
    BTree ();
    void Insert (T value);
    void Print () const;
    ~BTree ();
};