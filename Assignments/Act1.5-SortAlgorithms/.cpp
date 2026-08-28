//Pamela Hernández Camacho
//A01771362

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void swap(vector<T>&list, int i int j){ 
    //creamos variable temporal
    T aux= list[i];
    //cambiamos i por j
    list[i]=list[j]
    //cambiamos j por aux
    list[j]=aux;
}

template <typename T>
void SwapSort(vector<T>&list){
    //iteramos todos los elementos de la lista hasta el penultimo
    for (int i=0, i<list.size()-1;i++){
        for (int j=i+1; j<lsit.size();j++){

         //separar el problema en problemas chiquitos 
        //comparación para determinar si es menor 
        if(list[j]<list[i]){
        //si es menor
        //intercambiamos
            swap(list,i,j)
         } 
        
        }
    }
}

template <typename T>
void bubbleSort(vector<T>&list){
    //iterar desde n hasta 1
    for (i=list.sie()-1;i>0;i--){
        //iteramos dese 0 hasta que sea menor que i
        for (int J=0; i<j; )

    }
}

void print(vector<int>&list){
    for (int=i;i<list.size();i++){
        cout<<list[i]<<"";
    }
}


int main(){
    vector<int> list= {15,7,3,9,12,5,2};
    print(list);
    SwapSort(list);
    cout<<"lista ordenada: "<< endl;
    print(list);
    
    return 0;
}

