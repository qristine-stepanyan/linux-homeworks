#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int main(int argc, char** argv)
{
    //Check if a file path argument is provided
    if(argc < 2)
    {
        std::cerr<< "No file path provided." <<std::endl;
        exit(1);
    }
    //Get the file path from the command-line argument
    char* FilePath = argv[1]; 
    //Open the file
    int FileDescriptor = open(FilePath, O_RDONLY);
    if(FileDescriptor < 0)
    {
        std::cerr<< strerror(errno) <<std::endl;
        exit(errno);
    }
    
    char buf[BUFFER_SIZE];
    //Read and print the content of the file 
    while(true)
    {
        ssize_t ReadBytes = read(FileDescriptor, buf, BUFFER_SIZE);
        if(ReadBytes < 0)
        {
            std::cerr<< strerror(errno)<< std::endl;
            exit(errno);
        }
        //Check if we have reached the end of the file
        if(ReadBytes == 0)
        {
            break;
        }
        buf[ReadBytes] = '\0';
        //Print the portion of the file read
        std::cout<< buf <<std::endl;
    }
    //Close the file
    int CloseFile = close(FileDescriptor); 
    if(CloseFile < 0)
    {
    std::cerr<< strerror(errno)<<std::endl;
    }
return 0;
}
