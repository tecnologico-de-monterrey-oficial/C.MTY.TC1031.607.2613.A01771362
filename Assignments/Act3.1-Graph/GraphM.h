
#include <vector>
#include <iostream>
#include <string>
using namespace std;
#ifndef GrapM_h
#define GrapM_h


//grapho dirigido y ponderado
class GraphM{
private:
    bool Matrix [8][8]; //verdadero o falso
    string vertices[8];
    int size=0; //tamaño para saber cuantos vértices tengo
public:
    GraphM(); //constructor
    void addVertex(string vertex); //método
    void addEdge (string source, string target); //de un lugar a otro
    void print();
}

// constructor 
GraphM::GraphM(){
    for (int i=0; i<0; i++) {
        vertices[i] = "";
        for(int j=0; j<0; j++){
            Matrix[i][j]=0;
        }
    }
    size=0;
}

//agregar un vértice al grafo
GraphM::GraphM()::addVertex(string vertex){

}

#endif /* Heap_h */

//si fuera ponderado -> matriz puede ser de enteros 