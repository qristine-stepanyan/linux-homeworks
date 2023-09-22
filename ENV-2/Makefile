all:main

main:main.o complex.o
        g++ -o main main.o complex.o

complex.o:complex.cpp complex.h
        g++ complex.cpp -c

main.o:main.cpp
        g++ main.cpp -c

clean:
        rm *.o 
