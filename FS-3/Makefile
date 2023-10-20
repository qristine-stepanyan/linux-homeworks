all:read-file

read-file:read-file.o
	g++ read-file.o

read-file.o:read-file.cpp
	g++ read-file.cpp -o read-file.o

clean:rm *.o read-file
