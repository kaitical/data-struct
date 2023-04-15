#include <iostream>
#include<cmath>
#include <cstdlib>
#include <ctime>
#include"vector.h"
#include "Vector_fun.h"

class Complex {
public:
    Complex(double r = 0, double i = 0) : _real(r), _imag(i) {}
    Complex(const Complex& c) : _real(c._real), _imag(c._imag) {}
    Complex& operator=(const Complex& c) {
        _real = c._real;
        _imag = c._imag;
        return *this;
    }
    double getModulus() const { return sqrt(_real * _real + _imag * _imag); } // ģ
    bool operator==(const Complex& c) const { return _real == c._real && _imag == c._imag; }
    bool operator!=(const Complex& c) const { return !(*this == c); }
    bool operator<(const Complex& c) const { return getModulus() < c.getModulus() || (getModulus() == c.getModulus() && _real < c._real); }
    bool operator>(const Complex& c) const { return getModulus() > c.getModulus() || (getModulus() == c.getModulus() && _real > c._real); }
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c._real << "+" << c._imag << "i";
        return os;
    }
    double _real, _imag;

};

