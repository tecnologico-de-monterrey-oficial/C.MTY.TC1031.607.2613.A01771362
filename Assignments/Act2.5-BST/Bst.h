// Pamela Hernandez Camacho
// A01771362

#ifndef BST_h
#define BST_h

#include "Node.h"
#include <iostream>
#include <queue>
#include <vector>
#include <stdexcept>

using namespace std;

// Arbol Binario de Busqueda (BST) generico.
// Convenciones: la raiz esta en el nivel 1, la altura es el numero de
// niveles (arbol vacio = 0) y no se permiten datos repetidos.
template <typename T>
class BST {

private:

    Node<T>* root;

    // Funciones auxiliares recursivas
    Node<T>* insert(Node<T>* node, const T& data);
    Node<T>* remove(Node<T>* node, const T& data);
    Node<T>* minNode(Node<T>* node) const;
    void destroy(Node<T>* node);
    void print(Node<T>* node, int space) const;
    void preorder(Node<T>* node) const;
    void inorder(Node<T>* node) const;
    void postorder(Node<T>* node) const;
    void levelByLevel() const;
    int height(Node<T>* node) const;

public:

    BST() : root(nullptr) {}
    ~BST();

    // Evita copias que compartirian los mismos nodos
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(const T& data);
    void remove(const T& data);
    void print() const;
    bool find(const T& data) const;
    void visit(int tipo) const;
    int height() const;
    void ancestors(const T& data) const;
    int whatLevelAml(const T& data) const;
    bool empty() const;
};


// Destructor
template <typename T>
BST<T>::~BST() {
    destroy(root);
    root = nullptr;
}

template <typename T>
void BST<T>::destroy(Node<T>* node) {
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}


// INSERT
// Complejidad: O(h)
template <typename T>
void BST<T>::insert(const T& data) {
    root = insert(root, data);
}

template <typename T>
Node<T>* BST<T>::insert(Node<T>* node, const T& data) {

    // Encontramos el lugar donde va el nuevo nodo
    if (node == nullptr) {
        return new Node<T>(data);
    }

    if (data < node->data) {
        node->left = insert(node->left, data);
    }
    else if (node->data < data) {
        node->right = insert(node->right, data);
    }
    // Si es igual, no se inserta (no hay repetidos)

    return node;
}


// DELETE
// Complejidad: O(h)
template <typename T>
void BST<T>::remove(const T& data) {
    root = remove(root, data);
}

template <typename T>
Node<T>* BST<T>::minNode(Node<T>* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <typename T>
Node<T>* BST<T>::remove(Node<T>* node, const T& data) {

    // El dato no esta en el arbol
    if (node == nullptr) {
        return nullptr;
    }

    if (data < node->data) {
        node->left = remove(node->left, data);
    }
    else if (node->data < data) {
        node->right = remove(node->right, data);
    }
    else {
        // Caso 1: hoja o con un solo hijo
        if (node->left == nullptr) {
            Node<T>* aux = node->right;
            delete node;
            return aux;
        }
        if (node->right == nullptr) {
            Node<T>* aux = node->left;
            delete node;
            return aux;
        }

        // Caso 2: dos hijos. Se reemplaza por el sucesor inorder
        // (el menor del subarbol derecho)
        Node<T>* sucesor = minNode(node->right);
        node->data = sucesor->data;
        node->right = remove(node->right, sucesor->data);
    }

    return node;
}


// PRINT
// Imprime el arbol de lado: la raiz a la izquierda y las ramas
// hacia la derecha (el hijo derecho arriba, el izquierdo abajo)
template <typename T>
void BST<T>::print() const {

    if (root == nullptr) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    print(root, 0);
}

template <typename T>
void BST<T>::print(Node<T>* node, int space) const {

    if (node == nullptr) return;

    print(node->right, space + 6);

    cout << string(space, ' ') << node->data << endl;

    print(node->left, space + 6);
}


// FIND
// Complejidad: O(h)
template <typename T>
bool BST<T>::find(const T& data) const {

    Node<T>* curr = root;

    while (curr != nullptr) {
        if (data < curr->data) {
            curr = curr->left;
        }
        else if (curr->data < data) {
            curr = curr->right;
        }
        else {
            return true;
        }
    }

    return false;
}


// VISIT
// 1 = Preorder, 2 = Inorder, 3 = Postorder, 4 = Level by level
template <typename T>
void BST<T>::visit(int tipo) const {

    if (root == nullptr) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    switch (tipo) {
        case 1: preorder(root);   break;
        case 2: inorder(root);    break;
        case 3: postorder(root);  break;
        case 4: levelByLevel();   break;
        default:
            cout << "Tipo de recorrido invalido (1-4)";
    }

    cout << endl;
}

template <typename T>
void BST<T>::preorder(Node<T>* node) const {
    if (node == nullptr) return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void BST<T>::inorder(Node<T>* node) const {
    if (node == nullptr) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

template <typename T>
void BST<T>::postorder(Node<T>* node) const {
    if (node == nullptr) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

// Recorrido por niveles con una cola
template <typename T>
void BST<T>::levelByLevel() const {

    queue<Node<T>*> cola;
    cola.push(root);

    while (!cola.empty()) {
        Node<T>* curr = cola.front();
        cola.pop();

        cout << curr->data << " ";

        if (curr->left != nullptr)  cola.push(curr->left);
        if (curr->right != nullptr) cola.push(curr->right);
    }
}


// HEIGHT
// Numero de niveles del arbol (vacio = 0, un nodo = 1)
template <typename T>
int BST<T>::height() const {
    return height(root);
}

template <typename T>
int BST<T>::height(Node<T>* node) const {

    if (node == nullptr) return 0;

    int izq = height(node->left);
    int der = height(node->right);

    return 1 + (izq > der ? izq : der);
}


// ANCESTORS
// Muestra los ancestros del dato, desde la raiz hasta su padre
template <typename T>
void BST<T>::ancestors(const T& data) const {

    vector<T> camino;
    Node<T>* curr = root;

    // Recorremos el camino hacia el dato guardando cada nodo visitado
    while (curr != nullptr) {
        if (data < curr->data) {
            camino.push_back(curr->data);
            curr = curr->left;
        }
        else if (curr->data < data) {
            camino.push_back(curr->data);
            curr = curr->right;
        }
        else {
            break;
        }
    }

    if (curr == nullptr) {
        cout << "El dato " << data << " no se encuentra en el arbol" << endl;
        return;
    }

    if (camino.empty()) {
        cout << "El dato " << data << " es la raiz y no tiene ancestros" << endl;
        return;
    }

    cout << "Ancestros de " << data << ": ";
    for (size_t i = 0; i < camino.size(); i++) {
        cout << camino[i] << " ";
    }
    cout << endl;
}


// WHATLEVELAML
// Nivel del dato (la raiz es el nivel 1) o -1 si no esta
template <typename T>
int BST<T>::whatLevelAml(const T& data) const {

    Node<T>* curr = root;
    int nivel = 1;

    while (curr != nullptr) {
        if (data < curr->data) {
            curr = curr->left;
        }
        else if (curr->data < data) {
            curr = curr->right;
        }
        else {
            return nivel;
        }
        nivel++;
    }

    return -1;
}


template <typename T>
bool BST<T>::empty() const {
    return root == nullptr;
}

#endif