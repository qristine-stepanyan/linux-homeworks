#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 500

int main(int argc, char** argv)
{
    if(argc < 3){
       std::cerr<< "No file path provided."<< std::endl;
       exit(1);
    }

    char* FilePath = argv[1];
    char* SecondFile = argv[2];

    int FileDescriptor = open(FilePath, O_RDONLY);
    if(FileDescriptor < 0)
    {
        std::cerr<< strerror(errno)<< std::endl;
        exit(errno);
    }
    
    int SecondFileDescriptor = open(SecondFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(SecondFileDescriptor < 0)
    {
        std::cerr<< strerror(errno)<< std::endl;
        exit(errno);
    }

    char buf[BUFFER_SIZE];

    while(true)
    {
        ssize_t ReadBytes = read(FileDescriptor, buf, BUFFER_SIZE);
        if(ReadBytes < 0)
        {
            std::cerr<< strerror(errno)<< std::endl;
            exit(errno);
        }
        if(ReadBytes == 0)
        {
            break;
        }

        buf[ReadBytes] = '\0';

        ssize_t WrittenBytes = write(SecondFileDescriptor, buf, ReadBytes);
        if(WrittenBytes < 0){
            std::cerr<< strerror(errno)<< std::endl;
            exit(errno);
        }
    }
    int CloseFile = close(FileDescriptor);
    if(CloseFile < 0)
    {
        std::cerr<< strerror(errno)<< std::endl;
        exit(errno);
    }
    int SecondCloseFile = close(SecondFileDescriptor);
    if(SecondCloseFile < 0)
    {
        std::cerr<< strerror(errno)<< std::endl;
        exit(errno);
    }
return 0;
}
