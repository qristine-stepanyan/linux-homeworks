#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void interactiveShell(std::string command)
{
    //Check for "exit" command.
    if(command == "exit")
    {
        exit(0);
    }

    //Fork a new process.
    pid_t pid = fork();

    //If pid < 0 ,print the error.
    if(pid < 0)
    {
        std::cerr << strerror(errno) << std::endl ;
        exit(errno);
    }
    //For child process.
    if(pid == 0)
    {
        //Converting the command variable into a null-terminated string.(c_str() member function returns pointer to an array that contains a null-terminated sequence of characters representing the current value of the std::string.)
        const char* cmd = command.c_str();
        //Check for "silent" command and redirect output if necessary
        size_t silentPos = command.find("silent");
        if(silentPos == 0)
        {
            //Create a log file.
            int logFile = creat("PID.log",0644);
            int logFd = open("PID.log",O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            //Redirect standart output to the log file.
            dup2(logFd,1);
            //Redirect standart error to the log file.
            dup2(logFd,2);
            //Close the file descriptor.
            close(logFd);
            //Move the pointer past "silent".
            cmd += 6;
        }
        //Execute the command with the current directory in the path.
        int result = execlp("/bin/sh","sh","-c",cmd,nullptr);
        if(result < 0)
        {
            std::cerr << strerror(errno) <<std::endl;
            exit(errno);
        }
    }
    
    //For parent process.
    if(pid > 0)
    {
        int status;
        //Wait for the child process to finish.
        int waitResult = waitpid(pid, &status, 0);
    }
}

int main()
{
    //Initialize an empty string.
    std::string  command = "";
    while(true)
    {
    std::cin >> command;
    //Call the interactiveShell function to process the entered command.
    interactiveShell(command);
    }

return 0;
}
