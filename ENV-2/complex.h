#include <iostream>
#include <math.h>

class  ComplexNumber{
public:
    int real;  // Real part of the complex number
    int imaginary;  // Imaginary part of the complex number
    // Default constructor
    ComplexNumber():real(0),imaginary(0){};
    // Parameterized constructor
    ComplexNumber(int _real,int _imaginary):real(_real),imaginary(_imaginary){};
    // Overload the addition operator
    ComplexNumber operator+(const ComplexNumber& x);
    // Overload the subtraction operator
    ComplexNumber operator-(const ComplexNumber& x);
    // Overload the multiplication operator
    ComplexNumber operator*(int num);
    // Member function to calculate the absolute value of the complex number
    int absolutevalue();
    // Friend function to overload the << operator for ComplexNumber objects
    friend std::ostream& operator<<(std::ostream& output,const ComplexNumber& x)
   {
    output<<"("<<x.real<<","<<x.imaginary<<")";
    return output;
   }
};
