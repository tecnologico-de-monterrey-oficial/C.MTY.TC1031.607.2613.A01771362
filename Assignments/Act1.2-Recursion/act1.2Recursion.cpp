//Pamela Hernández Camacho
//A01771362

#include <iostream>
using namespace std;

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n-1);
}

int sumIterative(int n) {
    int suma = 0;
    for (int i=1; i <= n; i++) {
        suma += i;
    }
    return suma;
}

int sumRecursive(int n){
    if (n == 1) {
        return 1;
    }
    return n + sumRecursive(n-1);
}

int sumFormula(int n) {
    return n * (n+1) / 2;
}

int fibonacciIterative(int n) {
    int a = 1;
    int b = 1;
    int c;
    for (int i = 3; i <= n; i++) {
        c = a + b;  
        a = b;
        b = c;
    }
    return b;
}

int fibonacciRecursive(int n) {
    if (n <= 2) {
        return 1;
    }
    return fibonacciRecursive(n-1) + fibonacciRecursive(n-2);
}

int bacteriaIterative(int n) {
    double born = 3.78;
    double died = 2.34;
    int sum = 1;
    for (int i=1; i<=n; i++) {
        int bacBorn = sum * born;
        int bacDied = sum * died; 
        sum += bacBorn - bacDied; 
    }
    return sum;
}

int bacteriaRecursive(int n) {
    if (n==0) {
        return 1;
    }
    int bacteria = bacteriaRecursive(n-1);
    int born = bacteria * 3.78;
    int died = bacteria * 2.34;
    return bacteria + born - died;
}

double investmentIterative(double capital, int n) {
    double monto = capital;
    for (int i=1; i<=n; i++) {
        monto = monto + monto * 0.1875;
    }
    return monto;
}

double investmentRecursive(double capital, int n) {
    if (n == 0) {
        return capital;
    }
    double montoAnterior = investmentRecursive(capital, n-1);
    return montoAnterior + montoAnterior * 0.1875;
}

int powIterative(int base, int exp) {
    int resultado = 1;
    for (int i=1; i<=exp; i++) {
        resultado *= base;
    }
    return resultado;
}

int powRecursive(int base, int exp) {
    if (exp == 0) {
        return 1;
    }
    return base * powRecursive(base, exp-1);
}

int main() {

    cout << "El factorial de 7 es: " << factorial(6) << endl;
    // suma Iterativa
    cout << "La suma iterativa de 5 es: " << sumIterative(5) << endl;
    // suma Recusiva
    cout << "La suma recursiva de 5 es: " << sumRecursive(5) << endl;
    // suma formula
    cout << "La suma con formula de 5 es: " << sumFormula(5) << endl;
    // fibonacci iterativa
    cout << "La fibonnacci iterativa de 8 es: " << fibonacciIterative(8) << endl;
    // fibonacci recursive
    cout << "La fibonnacci recursiva de 8 es: " << fibonacciRecursive(8) << endl;
    // bacteria iterativa
    cout << "La bacteraia iterativa de 5 es: " << bacteriaIterative(5) << endl;
    // bacteria recursiva
    cout << "La bacteraia recursiva de 5 es: " << bacteriaRecursive(5) << endl;
    // inversion iterativa
    cout << "La inversion iterativa de $1000 a 6 meses es: " << investmentIterative(1000, 6) << endl;
    // inversion recursiva
    cout << "La inversion recursiva de $1000 a 6 meses es: " << investmentRecursive(1000, 6) << endl;
    // potencia iterativa
    cout << "2 elevado a la 10 (iterativo) es: " << powIterative(2, 10) << endl;
    // potencia recursiva
    cout << "2 elevado a la 10 (recursivo) es: " << powRecursive(2, 10) << endl;

    return 0;
}


