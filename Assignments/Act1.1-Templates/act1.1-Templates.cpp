#include <iostream>
#include <string>
#include "List.h"

using namespace std;

// int sum(int a, int b) {
//     return a + b;
// }

// double sum(double a, double b) {
//     return a + b;
// }

// string sum(string a, string b) {
//     return a + b;
// }

/* template <typename T>
T sum(T a, T b) {
    return a + b;
}

int main() {

    string a= "hola ";
    string b= "crayola";
    cout << "Sum of " << a << " and " << b << " is: " << sum(a, b) << endl;
    int c= 5;
    int d= 10;
    cout << "Sum of " << c << " and " << d << " is: " << sum(c, d) << endl;
    double e= 5.5;
    double f= 10.5;
    cout << "Sum of " << e << " and " << f << " is: " << sum(e, f) << endl;

    List<int> list;
    list.insert(5);
    list.insert(10);
    list.insert(15);

    List<string> things;
    things.insert("Laptop");
    things.insert("bottle");

    return 0; */


int main() {
    List<int> list;

    cout << "INSERT" << endl;
    list.insert(5);
    list.insert(10);
    list.insert(15);

    list.print();

    cout << endl;

    cout << "GET SIZE" << endl;
    cout << list.getSize() << endl;

    cout << endl;

    cout << "GET DATA" << endl;
    cout << list.getData(1) << endl;

    cout << endl;

    cout << "GET MAX" << endl;
    cout << list.getMax() << endl;

    cout << endl;

    cout << "INSERT AT" << endl;
    list.insertAt(1, 7);
    list.print();

    cout << endl;

    cout << "REMOVE AT" << endl;
    list.removeAt(2);
    list.print();

    cout << endl;

    cout << "REMOVE LAST" << endl;
    list.removeLast();
    list.print();

    cout << endl;

    cout << "PRUEBA DE STRING" << endl;

    List<string> things;

    things.insert("Laptop");
    things.insert("Bottle");
    things.insert("Notebook");

    things.print();

    return 0;
}