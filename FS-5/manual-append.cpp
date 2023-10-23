#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv){
    if(argc < 2){
        std::cerr << "No file path provided."<< std::endl; 
        exit(1);
    }
    char* FilePath = argv[1];  
    
    int FileDescriptor = open(FilePath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 
    if(FileDescriptor < 0){ 
        std::cerr<< strerror(errno)<< std::endl;
        exit(errno);
    }
    std::string s1 = "first line\n";
    std::string s2 = "second line\n";

    ssize_t WrittenBytes = write(FileDescriptor, s1.c_str(), s1.size()); 
    if(WrittenBytes < 0){
        std::cerr<< strerror(errno) << std::endl;
        exit(errno);
    }
    int SecondFileDescriptor =dup(FileDescriptor); 
    if(SecondFileDescriptor < 0){
        std::cerr<< strerror(errno) << std::endl;
        exit(errno);
    }
    
    WrittenBytes = write(SecondFileDescriptor, s2.c_str(), s2.size()); 
    if(WrittenBytes < 0){
        std::cerr<< strerror(errno)<< std::endl;
        exit(errno);
    }
    
close(FileDescriptor);
close(SecondFileDescriptor);
    
return 0;
} 