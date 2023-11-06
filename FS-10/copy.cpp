#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 100

int main(int argc, char** argv)
{
    //Check if file path arguments is provided.
    if(argc < 3)
    {
        std::cerr << "File path arguments is not provided." << std::endl;
        exit(1);
    }

    char* sourceFile = argv[1];
    char* destinationFile = argv[2];

    //Open the source file for reading.
    int fileDescriptorSourceFile = open(sourceFile, O_RDONLY);

    if(fileDescriptorSourceFile < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    //Open the destination file for writing,create if it does not exist,truncate to zero size.
    int fileDescriptorDestinationFile = open(destinationFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if(fileDescriptorDestinationFile < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    char buf[BUFFER_SIZE];

    while(true)
    {
        //Read from the source file into the buffer.
        ssize_t readBytes = read(fileDescriptorSourceFile, buf, BUFFER_SIZE);

        if(readBytes < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
        if(readBytes == 0)
        {
            //Exit the loop.
            break;
        }

        //Write data from the buffer to the destination file.
        ssize_t writeBytes = write(fileDescriptorDestinationFile, buf, readBytes);  

        if(writeBytes < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

    }

    //Set the file position indicator to the beginning of the destination file.
    off_t offset = lseek(fileDescriptorDestinationFile, 0, SEEK_SET);
    if(offset < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    //Get the size of the destination file.
    off_t fileSize = lseek(fileDescriptorDestinationFile, 0, SEEK_END);
    if(fileSize < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int dataBytes = 0;
    int holeBytes = 0;

    while(fileSize > offset)
    {

        //Find the next hole in the file.
        dataBytes = lseek(fileDescriptorDestinationFile, offset, SEEK_HOLE);
        if(dataBytes < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        //Find the next data region in the file.
        holeBytes = lseek(fileDescriptorDestinationFile, offset, SEEK_DATA);
        if(holeBytes < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        //Move the file position indicator forward by BUFFER_SIZE.
        offset = lseek(fileDescriptorDestinationFile, BUFFER_SIZE, SEEK_CUR);
        if(offset < 0)
        {
            std::cerr << strerror(errno) <<std::endl;
            exit(errno);
        }
    }
    //Close the source and destination files.
    int closeResult = close(fileDescriptorSourceFile);
    if(closeResult < 0)
    {
        std::cerr << strerror(errno) << std::endl;
    }
    
    closeResult = close(fileDescriptorDestinationFile);
    if(closeResult < 0)
    {
        std::cerr << strerror(errno) << std::endl;
    }

    //Print a result message.
    std::cout << "Successfully copied " << dataBytes+holeBytes << " bytes (data: " << dataBytes << ", hole: " << holeBytes << ")." << std::endl;

    return 0;  
}