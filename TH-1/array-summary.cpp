#include <iostream>
#include <pthread.h>
#include <algorithm>
#include <string.h>
#include <ctime>
#include <cstdlib>

struct local_sum_arg
{
    int* array;

    // Start index for the portion of the array.
    int start;

    // End index for the portion of the array.
    int end;

    // Result sum of the portion.
    int result;
};

void* local_sum(void* arg)
{
    // Casting the void pointer to the appropriate struct pointer.
    local_sum_arg* part = (local_sum_arg*) arg;

    int sum = 0;
    for(int i = part->start; i < part->end; ++i)
    {
        sum += part->array[i];
    }

    part->result = sum;
    return nullptr;
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        std::cerr << "Not enough arguments" << std::endl;
        return -1; 
    }

    // Extracting the size of the array from command line argument.
    int size = std::stoi(argv[1]);

    // Extracting the number of threads from command line argument.
    int threads_count = std::stoi(argv[2]);

    // Allocating memory for the array.
    int* array = new int[size];

    // Variable to store the sum of the whole array.
    int global_sum = 0;

    // Initialize the array with random values
    srand(time(0));

    for(int i = 0; i < size; ++i)
    {   
        // Initialize with random values between 0 and 99.
        array[i] = rand() % 100; 
    }

    // Sequential sum calculation.

    // Start measuring time for sequential sum calculation.
    clock_t start_time = clock();

    for(int i = 0; i < size; ++i)
    {
        global_sum += array[i];
    }

    // End measuring time for sequential sum calculation.
    clock_t end_time = clock();

    // Calculate time taken for sequential sum,converting the difference to seconds using CLOCKS_PER_SEC(It denotes the number of clock ticks per second).
    double sequential_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    
    // Multi-threaded sum calculation.

    // Array to hold thread identifiers.
    pthread_t* threads = new pthread_t[threads_count];

    // Array of struct pointers to hold arguments for threads.
    local_sum_arg** array_of_args = new local_sum_arg*[threads_count];

    // Start measuring time for multi-threaded sum calculation.
    start_time = clock();

    for(int i = 0; i < threads_count; ++i)
    {
        // Alocate memory for each struct in the array.
        array_of_args[i] = new local_sum_arg;

        array_of_args[i]->array = array;

        // Calculate the start index for each thread's portion.
        array_of_args[i]->start = i * (size / threads_count);

        // Calculate the end index for each thread's portion.
        array_of_args[i]->end = std::min(array_of_args[i]->start + (size / threads_count), size);

        int result = pthread_create(&threads[i], NULL, local_sum, array_of_args[i]);
        if(result != 0)
        {
            std::cerr << strerror(result) << std::endl;
            exit(result);
        }
    }

    for(int i = 0; i < threads_count; ++i)
    {
        // Wait for each thread to complete.
        pthread_join(threads[i], nullptr);
        global_sum += array_of_args[i]->result;
        delete array_of_args[i];
    }

    // End measuring time for multi-threaded sum calculation.
    end_time = clock();
    
    // Calculate time taken for multi-threaded sum,converting the difference to seconds using CLOCKS_PER_SEC.
    double threaded_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    delete[] array_of_args;
    delete[] array;
    delete[] threads;

    std::cout << "Time spent without threads: " << sequential_time << std::endl;
    std::cout << "Time spent with " << threads_count << " threads: " << threaded_time << std::endl;

    return 0;
}
