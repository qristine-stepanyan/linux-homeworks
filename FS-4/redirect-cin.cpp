#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 100

void initialize(int argc, char** argv){
    if(argc < 2){ 
        std::cout<< "No file path argument is provided."<< std::endl; 
        exit(1);
    }
    char* FilePath = argv[1]; 
    ssize_t FileDescriptor = open(FilePath, O_RDWR); 
    if(FileDescriptor < 0){ 
        std::cerr<< strerror(errno) << std::endl;
        exit(errno);
    }
    ssize_t new_cin = dup2(FileDescriptor,0); 
    ssize_t closed = close(FileDescriptor); 
    if(closed < 0){
        std::cerr<< strerror(errno) << std::endl;
        exit(errno);
    }
}

int main(int argc, char** argv){

    initialize(argc, argv); 

    std::string input;
    std::cin >> input; 
    std::string reversed(input.size() + 1, 'a'); 

    ssize_t n = input.size(); 
    for(int i = 0; i <= n; i++){
        reversed[i] = input[n - i];
    }
    reversed[n + 1] = '\0'; 
    
    std::cout<< reversed << std::endl; 

return 0;
}