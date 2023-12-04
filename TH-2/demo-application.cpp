#include "parallel_scheduler.h"    
#include <iostream>                
#include <unistd.h>                

// Function to be executed as a task in the thread pool
void taskFunction(void* arg)
{
    // Retrieve the task argument
    int task_arg = *static_cast<int*>(arg); 

    // Display task information
    std::cout << "Task performed with arg: " << task_arg << std::endl; 
    // Simulate some work with a sleep function
    sleep(1);   
}

int main()
{
    const int TASK_COUNT = 20;  

    // Create a thread pool with a capacity of 5 threads 
    ParallelScheduler scheduler(5);    

    // Enqueue various functions for execution
    for (int i = 0; i < TASK_COUNT; ++i)
    {
        // Create an argument for the task
        int* arg = new int(i);

        // Enqueue the task with its argument
        scheduler.enqueue(taskFunction, arg);  
    }

    // Allow some time for tasks to complete (just for demonstration purposes)
    // Wait for 10 seconds (simulating the application running)
    sleep(10);  

    return 0;   
}
