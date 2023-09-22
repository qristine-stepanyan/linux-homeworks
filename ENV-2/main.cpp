#include <iostream>
#include <vector>
#include "complex.h"
#include "sort.cpp"  
int main(){
    // Create three ComplexNumber objects
    ComplexNumber v1(78,51);
    ComplexNumber v2(2,5);
    ComplexNumber v3(30,12);
    std::cout<<v1+v2<<std::endl;
    std::cout<<v1-v2<<std::endl;
    std::cout<<v3*3<<std::endl;
    std::cout<<v1.absolutevalue()<<std::endl;
    // Create a vector of ComplexNumber objects and add the previously created objects to it
    std::vector<ComplexNumber>Vec;
    Vec.push_back(v1);
    Vec.push_back(v2);
    Vec.push_back(v3);
    // Call the bubblesort function to sort the vector of ComplexNumber objects
    bubblesort<ComplexNumber>(Vec,3);
return 0;
}
