// Clase pequena de apoyo para la practica independiente de apuntadores.
#pragma once
#include <iostream>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;
public:
    Fraction(int numerator, int denominator)
        : numerator(numerator), denominator(denominator) {
        if (denominator == 0) throw std::invalid_argument("Denominador cero");
    }
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
    void print() const { std::cout << numerator << "/" << denominator << "\n"; }
};