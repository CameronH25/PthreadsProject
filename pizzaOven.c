/* Horine, Cameron
Operating Systems | Fall 2023
Professor Moorman | Pthreads assignment

Pizza Oven using threads! 
Ensures bounded wait, mutex,
and progress on 3 conveyer belts
that handles a baffling three
types of pizza! 

What works: I think overall the 
program works in what it sets out
to do. Read the README.txt file
for more clarification. Program
seems to run indefinitely. */

#include "conveyor.h" 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number of trays> <number of pizzas>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int numberOfTrays = atoi(argv[1]);
    int numberOfPizzas = atoi(argv[2]);

    if (numberOfTrays <= 0 || numberOfPizzas <= 0) {
        fprintf(stderr, "Number of trays and pizzas must be positive ints\n");
        return EXIT_FAILURE;
    }

    runConveyorBelts(numberOfTrays, numberOfPizzas); 
    while (1) {
    }
    return 0; 
}

/* REFERENCES:
https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
https://www.geeksforgeeks.org/use-posix-semaphores-c/
https://www.tutorialspoint.com/c_standard_library/c_function_atoi.htm
https://www.geeksforgeeks.org/sleep-function-in-c/ */