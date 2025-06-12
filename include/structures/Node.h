#ifndef NODE_H
#define NODE_H
#include <vector>
using namespace std;

template<class T,int Order>
struct Node
{
    // Node *Padre;
    int number_of_keys;// numero de claves actuales
    int order;
    int position=-1; // para asignar valor en el lugar apropiado
    T* keys;
    Node** children;

    explicit Node (int order);
    int Insert (T value);
    Node* split (Node* node, T* med);
    void Print () ;
    void PrintUtil (int height,bool checkRoot);
    int getHeight () ;
//para obetenr los elemnetos en orden ascendente descendebte, valoracion
    void collectInOrder(vector<T>& result);
    void collectReverseOrder(vector<T>& result);

    ~Node ();
};
#endif  // NODE_H
