#include "parallel_scheduler.h"  
#include <string.h>

ParallelScheduler::ParallelScheduler(size_t capacity) : stop(false)
{
    // Initialize mutex and condition variables; handle initialization errors
    if (pthread_mutex_init(&mutex, nullptr) != 0 || pthread_cond_init(&condition, nullptr) != 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Create worker threads based on the specified capacity
    for (size_t i = 0; i < capacity; ++i)
    {
        pthread_t thread;
        if (pthread_create(&thread, nullptr, &ParallelScheduler::workerThread, this) != 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
        // Store the thread IDs in the vector
        threads.push_back(thread);  
    }
}

ParallelScheduler::~ParallelScheduler()
{
    // Set the stop flag to terminate threads
    stop = true; 

    // Signal threads to stop waiting
    pthread_cond_broadcast(&condition); 

    // Wait for each thread in the pool to finish
    for (auto& thread : threads)
    {
        pthread_join(thread, nullptr);
    }

    // Destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);
}

void ParallelScheduler::enqueue(void (*func)(void*), void* arg)
{
    {
        // Lock the mutex for accessing the task queue
        pthread_mutex_lock(&mutex);    

        // Add the task and its argument to the queue
        tasks.emplace(func, arg);  

        // Release the mutex
        pthread_mutex_unlock(&mutex);  
    }

    // Signal the availability of a new task
    pthread_cond_signal(&condition);   
}

void* ParallelScheduler::workerThread(void* arg)
{
    ParallelScheduler* scheduler = static_cast<ParallelScheduler*>(arg);

    while (true)
    {
        // Lock the mutex for accessing shared resources
        pthread_mutex_lock(&scheduler->mutex);   

        // Wait until there is a task or stop signal received
        while (scheduler->tasks.empty() && !scheduler->stop)
        {
            pthread_cond_wait(&scheduler->condition, &scheduler->mutex);
        }

        // Exit if stop signal is received and task queue is empty
        if (scheduler->stop && scheduler->tasks.empty())
        {
            // Release the mutex before exiting
            pthread_mutex_unlock(&scheduler->mutex); 
            break;
        }

        // Retrieve and execute a task from the queue
        void (*task)(void*) = scheduler->tasks.front().first;
        void* task_arg = scheduler->tasks.front().second;

        // Remove the executed task from the queue
        scheduler->tasks.pop(); 

        // Release the mutex after task execution
        pthread_mutex_unlock(&scheduler->mutex);   

        if (task)
        {
            // Execute the retrieved task with its argument
            task(task_arg); 
        }
    }

    return nullptr;
}
