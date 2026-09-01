//buscamos minimo en todos lados
//Pamela Hernández Camacho
//A01771362


template <typename T>

void selectionSort(vecto<T>&list){
    //iteramos toda la lista desde el principio hasta uno antes del final
    //PRIMER FOR
    for (int=0; i<list.size()-1; i++){
        //SEGUNDO FOR; no empezamos en la primera posición
        //iteramos desde el siguiente indice hasta el final
        //hacemos elindice de la posición j como el más chico
        int min = i; //cambiamos como el valor a tomar de i
        for (int j=i+1;j<list.size();j++){
            //comparamos el valor de j contra min
            if (list[j]< list[min]){
                // si es menor 
                // actualizamos el valor de min min=j
                min=j;
        
            }
        }
        //intercambiamos el valor de min por 
    }
    
}; //no regresamos nada es como solo checar


//selection sort
template <typename T>

void insertionSort(vector<T>&list){
    //iteramos la liste desde la sedunda posicipin hasta el final
    for(int i=1; i<list.size;i++){
        //iteramos desde i hasta 0
        // declaramos un contador para ver donde vamos
        int j=i;
        while (list[j]<lair[j-1]&&j>0);
        //intercambiamos j con j-1
        swap(list,j,j-1)
        //decrementamos j
        j--;

    }
};