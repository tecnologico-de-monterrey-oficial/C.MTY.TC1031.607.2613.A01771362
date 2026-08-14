#include <iostream>
using namespace std;

#include "List.h"

/* int sum(int a, int b){
    return a+b;
}

int sum(double a, double b){
    return a+b;
}

string sum(string a, string b){
    return a + b;
}  */

template<typename T>
T sum(T a, T b){
    return a + b;
    
}

int main(){

    string a="hola ";
    string b= "crayola";
    cout<< "Sum of " << a << " and "<< b << " is: "<< sum(a, b) << endl;
   
    int c=5;
    int d=10;

    List<int> list;

    return 0;
}
