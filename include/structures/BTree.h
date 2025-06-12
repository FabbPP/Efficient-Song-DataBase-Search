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
    std::vector<T> getTop(int n) const; // Obtener los primeros elementos del árbol
    int getCount() const { return count; }
    ~BTree();
};