#include "../../include/structures/Node.h"
#include <iostream>
using namespace std;

// Implementacion de Node
template <class T,int Order>
Node<T,Order>::Node (int order)
{
    this->order = order;
    this->number_of_keys = 0;
    // Asignar memoria DESPUES de establecer el orden
    this->keys = new T[this->order];
    this->children = new Node*[this->order + 1];

    // Inicializar los hijos en NULL
    for (int i = 0; i <= this->order; ++i)
        this->children[i] = nullptr;
}


template <class T,int Order>
int Node<T,Order>::Insert (T value)
{

    // Si el nodo es hoja
    if (this->children[0] == nullptr)
    {
        this->keys[++this->position] = value;
        ++this->number_of_keys;
        // Arreglar el arreglo de claves despues de poner el nuevo valor en el nodo
        for(int i=this->position; i>0 ; i--)
            if (this->keys[i] < this->keys[i-1])
                std::swap(this->keys[i],this->keys[i-1]);
    }
    // Si el nodo no es hoja
    else
    {
        // Contar para encontrar el lugar donde insertar el valor en el hijo
        int i=0;
        for(; i<this->number_of_keys && value > this->keys[i];)
            i++;

        // Verificar si el hijo esta lleno para dividirlo
        int check=this->children[i]->Insert(value);
        // Si el nodo esta lleno
        if(check)
        {
            T mid;
            int TEMP = i;
            Node<T,Order> *newNode = split(this->children[i], &mid); // Dividir el nodo
            // Para almacenar los valores y los hijos mayores que el valor medio
            // Asignar el valor medio al lugar correcto
            for(; i<this->number_of_keys && mid > this->keys[i];)
                i++;

            for (int j = this->number_of_keys; j > i ; j--)
                this->keys[j] = this->keys[j - 1];
            this->keys[i] = mid;
            ++this->number_of_keys;
            ++this->position;

            // Asignar el nuevo nodo dividido en el lugar correcto
            int k;
            for (k = this->number_of_keys; k > TEMP + 1; k--)
                this->children[k] = this->children[k - 1];
            this->children[k] = newNode;
        }

    }
    if(this->number_of_keys == this->order)
        return 1;// Para dividirlo
    else return 0;
}

template <class T,int Order>
Node<T,Order>* Node<T,Order>::split (Node *node, T *med) // mid para almacenar el valor medio y usarlo en la funcion Insertar
{
    int NumberOfKeys = node->number_of_keys;
    auto *newNode = new Node<T,Order>(order);
    //Node<T,Order> *newParentNode = new Node<T,Order>(order);
    int midValue = NumberOfKeys / 2;
    *med = node->keys[midValue];
    int i;
    // Tomar los valores despues del valor medio
    for (i = midValue + 1; i < NumberOfKeys; ++i)
    {
        newNode->keys[++newNode->position] = node->keys[i];
        newNode->children[newNode->position] = node->children[i];
        ++newNode->number_of_keys;
        --node->position;
        --node->number_of_keys;
        node->children[i] = nullptr;
    }
    newNode->children[newNode->position + 1] = node->children[i];
    node->children[i] = nullptr;

    --node->number_of_keys; // Porque tomamos el valor medio...
    --node->position;
    return newNode;
}


template <class T,int Order>
void Node<T,Order>::Print ()
{
    int height = this->getHeight(); // numero de niveles -> log (n)
    for (int i = 1; i <= height; ++i) // maximo 50 niveles
    {
        // O(n)
        if(i==1)PrintUtil(i,true);
        else PrintUtil(i,false);
        cout<<endl;
    }
    cout<<endl;
}

template <class T,int Order>
void Node<T,Order>::PrintUtil (int height,bool checkRoot)
{
    // Para imprimir todos los valores en el nivel
    if (height==1 || checkRoot)
    {
        for (int i = 0; i < this->number_of_keys; i++){
             if(i==0) cout << "|";
             cout<< this->keys[i];
             if(i!=this->number_of_keys-1) cout<<"|";
             if(i==this->number_of_keys-1) cout << "|"<<" ";
        }

    }

    else
    {
        for (int i = 0; i <= this->number_of_keys; i++)
            this->children[i]->PrintUtil(height - 1, false);
            //cout<<endl<<" ";
    }

}

template <class T,int Order>
int Node<T,Order>::getHeight ()
{
    int COUNT=1;
    Node<T,Order>* Current=this;//current apunta a la raiz
    while(true){
            // Si es hoja
        if(Current->children[0] == nullptr)
            return COUNT;
        Current=Current->children[0];
        COUNT++;
    }
}

// Desasignacion
template <class T,int Order>
Node<T,Order>::~Node ()
{
    delete[]keys;
    // Solo eliminar los punteros hijos que no sean NULL
    for (int i = 0; i <= this->number_of_keys; ++i)
        delete children[i];
    delete[] children;
}
