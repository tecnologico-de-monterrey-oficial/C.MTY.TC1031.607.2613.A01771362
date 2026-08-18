//Creamos clase que se llame list para guardar cualquier tipo de elementos
#ifndef List_h //si la funcion no esta definida la defina
#define List_h

#include <iostream>
#include <vector>

using namespace std;

template <typename T>  //esta clase puede utilizar templates
class List {
private:
    vector<T> data; //aquí el "data" es el nombre del vector
    int size; //entero llamado size que tenga los datos almacenados del vector

public:
    List();
    void insert(T data); //decimos que funciones tenemos
    void removeLast();
    T getData(int pos);
    int getSize();
    T getMax();
    void print();
    void insertAt(int pos, T data);
    void removeAt(int pos);
};

template <typename T>
List<T>::List() { //el constructor pertenece a tal clase
    size = 0;
}

template <typename T>
void List<T>::insert(T data) {
    this->data.push_back(data);
    size++;
}

template <typename T>
void List<T>::removeLast() {
    if (size == 0) {
        cout << "NO HAY ELEMENTOS" << endl;
    }
    else {
        cout << data[size - 1] << endl;
        data.pop_back();
        size--;
    }
}

template <typename T>
T List<T>::getData(int pos) {
    return data[pos];
}

template <typename T>
int List<T>::getSize() {
    return size;
}

template <typename T>
T List<T>::getMax() {
    T max = data[0];

    for (int i = 1; i < size; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }

    return max;
}

template <typename T>
void List<T>::print() {
    for (int i = 0; i < size; i++) {
        cout << "[" << i << "] - " << data[i] << endl;
    }
}

template <typename T>
void List<T>::insertAt(int pos, T value) {
    if (pos < 0 || pos > size) {
        cout << "POSICIÓN INVÁLIDA" << endl;
        return;
    }

    data.push_back(value);              // agranda el vector en 1 (valor temporal al final)

    for (int i = size; i > pos; i--) {
        data[i] = data[i - 1];          // recorre todo a la derecha
    }

    data[pos] = value;                  // coloca el valor en su posición
    size++;
}

template <typename T>
void List<T>::removeAt(int pos) {
    if (size == 0) {
        cout << "NO HAY ELEMENTOS" << endl;
        return;
    }

    if (pos < 0 || pos >= size) {
        cout << "POSICIÓN INVÁLIDA" << endl;
        return;
    }

    cout << data[pos] << endl;

    for (int i = pos; i < size - 1; i++) {
        data[i] = data[i + 1];
    }

    data.pop_back();
    size--;
}

#endif /* List_h */

//comando ndef