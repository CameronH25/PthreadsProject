#include "conveyorBelt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Initializes a conveyor belt. Sets up synchronization primitives (semaphores and
mutexes), init counters, and ensures that the belt is ready to accept pizzas. */
void initializeBelt(ConveyorBelt* belt, int trayCapacity, PizzaType type) {

    if (sem_init(&belt->emptySlots, 0, trayCapacity) != 0) {
        perror("Failed to initialize emptySlots semaphore");
        exit(EXIT_FAILURE);
    }

    if (sem_init(&belt->fullTrays, 0, 0) != 0) {
        perror("Failed to initialize fullTrays semaphore");
        exit(EXIT_FAILURE);
    }

    if (pthread_mutex_init(&belt->mutex, NULL) != 0) {
        perror("Failed to initialize mutex");
        exit(EXIT_FAILURE);
    }

    belt->currentPizzas = 0;
    belt->trayCapacity = trayCapacity;
    belt->type = type; 
}

/* Conveyor belt simulation thread. Continuously tries to add pizzas to the belt,
manages pizzaCount, and sends pizzas through the conveyor belt when a tray is full. */
void* conveyorBeltThread(void* arg) {
    ConveyorBelt* belt = (ConveyorBelt*)arg;
    
    while (1) {
        sem_wait(&belt->emptySlots);
        pthread_mutex_lock(&belt->mutex);

        belt->currentPizzas++;
        const char* pizzaType = belt->type == MEAT ? "Meat" : belt->type == VEGGIE ? "Veggie" : "Mixed";
        printf("%s pizza added. Current pizzas: %d\n", pizzaType, belt->currentPizzas);

        if (belt->currentPizzas == belt->trayCapacity) {
            printf("Tray is full. Sending through conveyor belt...\n");
            belt->currentPizzas = 0;
            sem_post(&belt->fullTrays);  // Signal that a tray is full
        } else {
            sem_post(&belt->emptySlots);  // Signal an empty slot only if the tray is not full
        }

        pthread_mutex_unlock(&belt->mutex);  // Release the mutex
    }
    
    return NULL;
}

/* Separate thread for simulating processing of full pizza trays. Once a tray is full and
sent through the conveyor belt, the function "processes" it, and then signals that the 
conveyor belt is ready to accept more pizzas. */
void* processFullTrays(void* arg) {
    ConveyorBelt* belt = (ConveyorBelt*)arg;
    while (1) {
        sem_wait(&belt->fullTrays);
        printf("Processing full tray...\n");
        sleep(PROCESSING_TIME);
        printf("Full tray processed. Ready for more pizzas.\n");
        for (int i = 0; i < belt->trayCapacity; i++) {
            sem_post(&belt->emptySlots);
        }
    }
    return NULL;
}