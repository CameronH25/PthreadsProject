#ifndef CONVEYOR_BELT_H
#define CONVEYOR_BELT_H

#include <semaphore.h>
#include <pthread.h>

#define PROCESSING_T 1
#define PROCESSING_TIME 2

typedef enum {
    MEAT,
    VEGGIE,
    MIXED
} PizzaType;

typedef struct {
    sem_t emptySlots;
    sem_t fullTrays;
    pthread_mutex_t mutex;
    int currentPizzas;
    int trayCapacity;
    PizzaType type; 
} ConveyorBelt;

void initializeBelt(ConveyorBelt* belt, int trayCapacity, PizzaType type);
void* conveyorBeltThread(void* arg);
void* processFullTrays(void* arg);

#endif // CONVEYOR_BELT_H