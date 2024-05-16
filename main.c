/* Horine, Cameron
Operating Systems | Fall 2023
Professor Moorman | Pthreads */

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
        fprintf(stderr, "Number of trays and pizzas must be positive integers\n");
        return EXIT_FAILURE;
    }

    runConveyorBelts(numberOfTrays, numberOfPizzas); 
    while (1) {
    }
    return 0; 
}

