#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<typename T>//siempre definir el template

//búsqueda Binaria (la lista ya está ordenada)
int binarySearch(vector<T>&List, T data){
    //obtenemos left
    left=0;
    //obtenemos right
    right=list.size()-1;
    //buscamos el elemento mientras left <== right
    while (left <= right){
        //Obtenemos la mitad
        int mid =(left+right)/2;
        //comparamos el valor buscado con el valor de la mitad 
        if (data== list([mid]){
            //regresamos el valor de mid que es el indicce del valor encontrado
            return mid;
        } else{
            //preguntamos si el valor buscado es menor que el valor de mid
            if (data< list[mid]){
                right =mid-1;
            } else {
                //es mayor
                left=mid +1;
            }
        }
    }
    //no lo encontramos
    return -1;
}

int main(){
    vector<int> list= {3,5,6,8,11,12,13,16,27,35};

    int index =binarySearch(list,15);
    cout<< "el valor se encuentra en: " << index << endl;

}