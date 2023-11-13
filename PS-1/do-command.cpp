#include <iostream>
#include <sys/times.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void do_command(char** argv)
{
    //Variables to store start and end times.
    struct tms start_time,end_time;

    //Get the start time using the times function.
    clock_t startTime = times(&start_time);

    //Fork a new process.
    pid_t pid = fork();

    //Check for fork failure.
    if(pid < 0)
    {
        //Print error message and exit if fork fails.
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    //For the child process.
    if(pid == 0)
    {
        //Execute the command in the child process
        if(execvp(argv[0],argv) == -1)
        {
        //Print error message and exit if execvp fails.
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
        }
    }

    //For parent process.
    if(pid > 0)
    {
        int status;

        //Wait  for the child process to complete.
        int waitResult = waitpid(pid, &status, 0);

        if(waitResult == -1)
        {
        //Print error message and exit if waitpid fails.
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
        }

        //Get the end time using the times function.
        clock_t endTime = times(&end_time);

        //Calculate the duration of the command execution in seconds.
        double duration = static_cast<double>(endTime - startTime) / sysconf(_SC_CLK_TCK);

        //Print the exit status and duration of the command execution.
        std::cout << "Command completed with " << WEXITSTATUS(status) << " exit code and took " << duration << " seconds." << std::endl;
    }
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        //Print error message  and exit if there are not enough arguments.
        std::cerr << strerror(errno) << std::endl;
        exit(1);
    }
    
    //Call the do_command function with command-line arguments starting from the second argument.
    do_command(argv + 1);

return 0; 
}
