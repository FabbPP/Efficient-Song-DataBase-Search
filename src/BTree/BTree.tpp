#ifndef BTREE_TPP
#define BTREE_TPP

template<class T, int Order>
Node<T, Order>::Node(int order) {
    this->order = order;
    this->number_of_keys = 0;
    this->position = -1;
    this->keys = new T[this->order];
    this->children = new Node*[this->order + 1];
    for (int i = 0; i <= this->order; ++i)
        this->children[i] = nullptr;
}

template<class T, int Order>
int Node<T, Order>::Insert(T value) {
    if (this->children[0] == nullptr) {
        this->keys[++this->position] = value;
        ++this->number_of_keys;
        for(int i = this->position; i > 0; i--)
            if (this->keys[i] < this->keys[i-1])
                swap(this->keys[i], this->keys[i-1]);
    } else {
        int i = 0;
        for(; i < this->number_of_keys && value > this->keys[i]; i++);

        int check = this->children[i]->Insert(value);
        if(check) {
            T mid;
            int TEMP = i;
            Node<T, Order>* newNode = split(this->children[i], &mid);
            for(; i < this->number_of_keys && mid > this->keys[i]; i++);

            for (int j = this->number_of_keys; j > i; j--)
                this->keys[j] = this->keys[j - 1];
            this->keys[i] = mid;
            ++this->number_of_keys;
            ++this->position;

            int k;
            for (k = this->number_of_keys; k > TEMP + 1; k--)
                this->children[k] = this->children[k - 1];
            this->children[k] = newNode;
        }
    }
    return (this->number_of_keys == this->order) ? 1 : 0;
}

template<class T, int Order>
Node<T, Order>* Node<T, Order>::split(Node* node, T* med) {
    int NumberOfKeys = node->number_of_keys;
    auto* newNode = new Node<T, Order>(order);
    int midValue = NumberOfKeys / 2;
    *med = node->keys[midValue];
    int i;
    for (i = midValue + 1; i < NumberOfKeys; ++i) {
        newNode->keys[++newNode->position] = node->keys[i];
        newNode->children[newNode->position] = node->children[i];
        ++newNode->number_of_keys;
        --node->position;
        --node->number_of_keys;
        node->children[i] = nullptr;
    }
    newNode->children[newNode->position + 1] = node->children[i];
    node->children[i] = nullptr;
    --node->number_of_keys;
    --node->position;
    return newNode;
}

template<class T, int Order>
void Node<T, Order>::Print() {
    int height = this->getHeight();
    for (int i = 1; i <= height; ++i) {
        if(i == 1) PrintUtil(i, true);
        else PrintUtil(i, false);
        cout << endl;
    }
    cout << endl;
}

template<class T, int Order>
void Node<T, Order>::PrintUtil(int height, bool checkRoot) {
    if (height == 1 || checkRoot) {
        for (int i = 0; i < this->number_of_keys; i++) {
            if(i == 0) cout << "|";
            cout << this->keys[i];
            if(i != this->number_of_keys - 1) cout << "|";
            if(i == this->number_of_keys - 1) cout << "| ";
        }
    } else {
        for (int i = 0; i <= this->number_of_keys; i++)
            this->children[i]->PrintUtil(height - 1, false);
    }
}

template<class T, int Order>
int Node<T, Order>::getHeight() {
    int COUNT = 1;
    Node<T, Order>* Current = this;
    while(true) {
        if(Current->children[0] == nullptr) return COUNT;
        Current = Current->children[0];
        COUNT++;
    }
}

template<class T, int Order>
void Node<T, Order>::collectInOrder(vector<T>& result) {
    if (this->children[0] == nullptr) {
        for (int i = 0; i < this->number_of_keys; i++)
            result.push_back(this->keys[i]);
    } else {
        for (int i = 0; i <= this->number_of_keys; i++) {
            if (this->children[i] != nullptr)
                this->children[i]->collectInOrder(result);
            if (i < this->number_of_keys)
                result.push_back(this->keys[i]);
        }
    }
}

template<class T, int Order>
void Node<T, Order>::collectReverseOrder(vector<T>& result) {
    if (this->children[0] == nullptr) {
        for (int i = this->number_of_keys - 1; i >= 0; i--)
            result.push_back(this->keys[i]);
    } else {
        for (int i = this->number_of_keys; i >= 0; i--) {
            if (i < this->number_of_keys)
                result.push_back(this->keys[i]);
            if (this->children[i] != nullptr)
                this->children[i]->collectReverseOrder(result);
        }
    }
}

template<class T, int Order>
void Node<T, Order>::collectTopN(vector<T>& result, int n) {
    if (result.size() >= n) return;
    if (this->children[0] == nullptr) {
        for (int i = this->number_of_keys - 1; i >= 0 && result.size() < n; i--)
            result.push_back(this->keys[i]);
    } else {
        for (int i = this->number_of_keys; i >= 0 && result.size() < n; i--) {
            if (i < this->number_of_keys && result.size() < n)
                result.push_back(this->keys[i]);
            if (this->children[i] != nullptr && result.size() < n)
                this->children[i]->collectTopN(result, n);
        }
    }
}

template<class T, int Order>
void Node<T, Order>::collectBottomN(vector<T>& result, int n) {
    if (result.size() >= n) return;
    if (this->children[0] == nullptr) {
        for (int i = 0; i < this->number_of_keys && result.size() < n; i++)
            result.push_back(this->keys[i]);
    } else {
        for (int i = 0; i <= this->number_of_keys && result.size() < n; i++) {
            if (this->children[i] != nullptr && result.size() < n)
                this->children[i]->collectBottomN(result, n);
            if (i < this->number_of_keys && result.size() < n)
                result.push_back(this->keys[i]);
        }
    }
}

template<class T, int Order>
Node<T, Order>::~Node() {
    delete[] keys;
    for (int i = 0; i <= this->number_of_keys; ++i)
        delete children[i];
    delete[] children;
}

template<class T, int Order>
BTree<T, Order>::BTree() {
    this->order = Order;
    this->root = nullptr;
    this->count = 0;
}

template<class T, int Order>
void BTree<T, Order>::Insert(T value) {
    count++;
    if (this->root == nullptr) {
        this->root = new Node<T, Order>(this->order);
        this->root->keys[++this->root->position] = value;
        this->root->number_of_keys = 1;
    } else {
        int check = root->Insert(value);
        if(check) {
            T mid;
            Node<T, Order>* splitNode = this->root->split(this->root, &mid);
            auto* newNode = new Node<T, Order>(this->order);
            newNode->keys[++newNode->position] = mid;
            newNode->number_of_keys = 1;
            newNode->children[0] = root;
            newNode->children[1] = splitNode;
            this->root = newNode;
        }
    }
}

template<class T, int Order>
void BTree<T, Order>::Print() const {
    if (root != nullptr) root->Print();
    else cout << "The B-Tree is Empty" << endl;
}

template<class T, int Order>
vector<T> BTree<T, Order>::getTopN(int n) {
    vector<T> allElements;
    if (root != nullptr) root->collectReverseOrder(allElements);
    vector<T> result;
    for (int i = 0; i < min(n, (int)allElements.size()); i++)
        result.push_back(allElements[i]);
    return result;
}

template<class T, int Order>
vector<T> BTree<T, Order>::getBottomN(int n) {
    vector<T> allElements;
    if (root != nullptr) root->collectInOrder(allElements);
    vector<T> result;
    for (int i = 0; i < min(n, (int)allElements.size()); i++)
        result.push_back(allElements[i]);
    return result;
}

template<class T, int Order>
vector<T> BTree<T, Order>::getTopNOptimized(int n) {
    vector<T> result;
    if (root != nullptr) {
        result.reserve(n);
        root->collectTopN(result, n);
    }
    return result;
}

template<class T, int Order>
vector<T> BTree<T, Order>::getBottomNOptimized(int n) {
    vector<T> result;
    if (root != nullptr) {
        result.reserve(n);
        root->collectBottomN(result, n);
    }
    return result;
}

template<class T, int Order>
Node<T, Order>* BTree<T, Order>::getRoot() { 
    return root; 
}

template<class T, int Order>
BTree<T, Order>::~BTree() {
    delete root;
}

#endif