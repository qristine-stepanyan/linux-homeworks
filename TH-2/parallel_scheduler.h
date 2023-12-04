#include <iostream> 
#include <vector>       
#include <queue>        
#include <pthread.h>    
#include <stdlib.h>    

class ParallelScheduler
{
public:
    // Constructor defining the thread pool with a given capacity
    ParallelScheduler(size_t capacity); 
     
    // Destructor to release resources  
    ~ParallelScheduler();  

    // Method to enqueue tasks for execution
    void enqueue(void (*func)(void*), void* arg);    

private:
    // Static method acting as the worker thread function
    static void* workerThread(void* arg); 

    // Vector to store thread IDs
    std::vector<pthread_t> threads; 

    // Queue to hold tasks and their arguments
    std::queue<std::pair<void (*)(void*), void*>> tasks; 

    // Mutex for thread synchronization
    pthread_mutex_t mutex; 

    // Condition variable for signaling task availability
    pthread_cond_t condition; 

    // Boolean to control termination of threads
    bool stop;                      
};
