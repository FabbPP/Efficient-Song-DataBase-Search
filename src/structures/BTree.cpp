#include "BTree.h"
#include <iostream>
#include <vector>
using namespace std;

template <class T,int Order>
BTree<T,Order>::BTree()
{
    this->order = Order;    // establecer el orden del arbol B
    this->root  = nullptr;   // inicializar la raiz como nullptr
    this->count=0;
}

template <class T,int Order>
void BTree<T,Order>::Insert (T value)
{
    count++;
    //si el arbol esta vacio
    if (this->root == nullptr)
    {
        this->root = new Node<T,Order>(this->order);
        this->root->keys[++this->root->position]=value;
        this->root->number_of_keys=1;
    }
    //si el arbol no esta vacio
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

template <class T, int Order>
vector<T> BTree<T, Order>::getTop(int n) const {
    vector<T> result;
    if (root != nullptr) {
        root->getFirst(n, result); // Verifica que esta función existe en Node<T, Order>
    }
    return result;
}

template <class T,int Order>
BTree<T,Order>::~BTree ()
{
    delete root;
}