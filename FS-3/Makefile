all:read-file

read-file:read-file.o
	g++ read-file.o -o read-file

read-file.o:read-file.cpp
	g++ -c read-file.cpp

clean:rm *.o read-file
