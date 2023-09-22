#include <iostream>
#include <math.h>
#include "complex.h"
// Overload the addition operator
ComplexNumber ComplexNumber::operator +(const ComplexNumber& x){
return ComplexNumber(real+x.real,imaginary+x.imaginary);
};
// Overload the subtraction operator
ComplexNumber ComplexNumber::operator -(const ComplexNumber& x){
return ComplexNumber(real-x.real,imaginary-x.imaginary);
};
// Overload the multiplication operator
ComplexNumber ComplexNumber::operator *(int n){
return ComplexNumber(real*n,imaginary*n);
};
// Member function for calculating the absolute value of a ComplexNumber
int ComplexNumber::absolutevalue(){
return sqrt(real*real+imaginary*imaginary);
};
