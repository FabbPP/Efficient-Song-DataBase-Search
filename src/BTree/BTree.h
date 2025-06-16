#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <iostream>
using namespace std;

template<class T, int Order>
struct Node {
    int number_of_keys;
    int order;
    int position;
    T* keys;
    Node** children;

    explicit Node(int order);
    int Insert(T value);
    Node* split(Node* node, T* med);
    void Print();
    void PrintUtil(int height, bool checkRoot);
    int getHeight();
    void collectInOrder(vector<T>& result);
    void collectReverseOrder(vector<T>& result);
    void collectTopN(vector<T>& result, int n);
    void collectBottomN(vector<T>& result, int n);
    ~Node();
};

template<class T, int Order>
class BTree {
private:
    Node<T, Order>* root;
    int order;
    int count;
public:
    BTree();
    void Insert(T value);
    void Print() const;
    vector<T> getTopN(int n);
    vector<T> getBottomN(int n);
    vector<T> getTopNOptimized(int n);
    vector<T> getBottomNOptimized(int n);
    Node<T, Order>* getRoot();
    ~BTree();
};

#include "BTree.tpp"
#endif