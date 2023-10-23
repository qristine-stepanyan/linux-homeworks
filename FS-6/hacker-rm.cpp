#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 300

int main(int argc, char** argv){
    if(argc < 2){
        std::cerr<< "No file path provided."<< std::endl;
        exit(1);        
    }
    char* FilePath = argv[1]; 
    
    int FileDescriptor = open(FilePath, O_RDONLY);
    if(FileDescriptor < 0){
        std::cerr<< strerror(errno)<< std::endl;  
        exit(errno);
    }
    
    char buf[BUFFER_SIZE];  
    for(int i = 0; i < BUFFER_SIZE; i++){ 
        buf[i] = '\0';
    }
    
    struct stat StatBuffer; 
    ssize_t FileInfo = stat(FilePath, &StatBuffer); 
    if(FileInfo  < 0){
        std::cerr<< strerror(errno)<< std::endl;
        exit(1);
    }

    ssize_t Len = StatBuffer.st_size; 
    
    ssize_t SeekedBytes = lseek(FileDescriptor, 0, SEEK_SET); 
    if(SeekedBytes < 0){
        std::cerr<< strerror(errno) << std::endl;
        exit(1);
    }
    
    ssize_t WrittenBytes, count = 0;
    while(count < Len){ 
         WrittenBytes = write(FileDescriptor, buf, BUFFER_SIZE);
         if(WrittenBytes < 0){
             std::cerr<< strerror(errno) << std::endl;
         }
         count += WrittenBytes;
    }

    ssize_t Removed = unlink(FilePath); 
    if(Removed  < 0){
        std::cerr<< strerror(errno)<< std::endl;
        exit(errno);
    }

return 0;
}
