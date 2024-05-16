#include "conveyor.h"
#include "conveyorBelt.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pthread_t meatThread, veggieThread, mixedThread;
static pthread_t meatProcessor, veggieProcessor, mixedProcessor;
static ConveyorBelt meatBelt, veggieBelt, mixedBelt;

/* Main driver function. It initializes the conveyor belts and creates the threads.
It ensures that all parts of the system are running and interacitng as they should. */
void runConveyorBelts(int numberOfTrays, int numberOfPizzas) {
    int trayCapacity = numberOfPizzas / numberOfTrays;
    initializeBelt(&meatBelt, trayCapacity, MEAT);
    initializeBelt(&veggieBelt, trayCapacity, VEGGIE);
    initializeBelt(&mixedBelt, trayCapacity, MIXED);

    pthread_create(&meatThread, NULL, conveyorBeltThread, (void*)&meatBelt);
    pthread_create(&veggieThread, NULL, conveyorBeltThread, (void*)&veggieBelt);
    pthread_create(&mixedThread, NULL, conveyorBeltThread, (void*)&mixedBelt);

    pthread_create(&meatProcessor, NULL, processFullTrays, (void*)&meatBelt);
    pthread_create(&veggieProcessor, NULL, processFullTrays, (void*)&veggieBelt);
    pthread_create(&mixedProcessor, NULL, processFullTrays, (void*)&mixedBelt);

    while (1) {
        sleep(PROCESSING_T);
    }
}