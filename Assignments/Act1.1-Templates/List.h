//Creamos clase que se llame list para guardar cualquier tipo de elementos
#ifndef List_h //si la funcion no esta definida la defina
#define List_h
#include <vector>


template <typename T>  //esta clase puede utilizar templates
class List {
private:
    vector<T> list;
    int size;
public:
    List();
    void insert(T data);
};

template <typename T>
List<T>::List() { //el constructor pertenece a tal clase
    size = 0;
}

template <typename T>
void List<T>::insert(T data) {
    list.push_back(data);
    size++;
}


#endif /* List_h */

//comando ndef 