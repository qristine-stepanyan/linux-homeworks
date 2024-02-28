#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/ucontext.h>
#include <pwd.h>

// Signal handler for SIGUSR1
void sigusr1_handler(int sig, siginfo_t *info,void *ucontext)
{
    // Extract sender's PID
    pid_t sender_pid = info->si_pid;

    // Extract sender's UID and username
    uid_t sender_uid = info->si_uid;

    struct passwd *pwd = getpwuid(sender_uid);
    const char *sender_username = (pwd != NULL) ? pwd->pw_name : "Unknown";

    // Extract register values

    // Cast void pointer to ucontext_t pointer
    ucontext_t *context = (ucontext_t *)ucontext;

    unsigned long eip = context->uc_mcontext.gregs[REG_RIP];
    unsigned long eax = context->uc_mcontext.gregs[REG_RAX];
    unsigned long ebx = context->uc_mcontext.gregs[REG_RBX];

    // Print
    std::cout << "Received a SIGUSR1 signal from process " << sender_pid << " executed by " << sender_uid << " (" << sender_username << ")." << std::endl;
    std::cout << "State of the context: EIP= " << std::hex << eip << ", EAX= " << eax << ", EBX= " << ebx << "." << std::endl;
}

int main()
{
    // Set up signal handling for SIGUSR1

    // Define a struct for signal handling
    struct sigaction action;
    
    // Initialize the struct to zero
    memset(&action, 0, sizeof(action));

    // Set the flag to indicate we want to use a siginfo_t structure for more signal information
    action.sa_flags = SA_SIGINFO;

    // Set the handler function for SIGUSR1
    action.sa_sigaction = sigusr1_handler;

    // Register the signal handler
    
    // Check if the signal registration was successful
    if (sigaction(SIGUSR1, &action, NULL) < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
 
    // Print the PID of the process
    std::cout << "PID: " << getpid() << std::endl;

    // Enter an infinite loop with a sleep delay
    while(true)
    {
        // Sleep for 10 second
        sleep(10);
    }
    return 0;
}