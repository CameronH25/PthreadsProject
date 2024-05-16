BOO! (Hopefully the program is not as scary...)

Mutex rationale:
    Mutual exclusion is, I think, ensured in my program as each shared resource (notably the conveyor belts and the associates countes for pizzas) are protected by mutexes. Further, when a pizza is being added to a conveyor belt, the "conveyorBeltThread" function locks the mutex. This prevents race conditions and ensures that the shared data is consistent. 

Bounded Wait rationale:
    Bounded wait is ensured due to semaphore usage -- these control access to the conveyor belts. When a conveyor belt is full, the "conveyorBeltThread" function will block until the "processFullTrays" function signals that a tray has been processed. Further, looking at the output, each pizza type is getting its turn in a finite amount of time (we can not know for sure, for sure -- halting problem. Maybe the veggie 
pizzas won't be serviced after a while, for example -- which sounds good to me.) 
Also, in the sample output in the notes, each pizza type is getting two trays each
before it switches. This means that no matter what, each pizza type will be serviced.

Progress:
    Progress is ensured because no thread is being locked indefinitely. The "conveyorBeltThread" function only holds the lock while it is updating the state of the conveyor belt and releases it afterwards. Additionally, the "processFullTrays" function
is always able to make progress so long as there are full trays to process. Since pizzas are continuously being added and trays are continually being processed, the 
system overall makes progress. 

Notes:

(1):
    When calling the program via the terminal, it takes in three arguments:

    1. ./bobo       2. num of trays     3. num of pizzas

    Sample output wherein num of trays = 10, num of pizzas = 20:

        Meat pizza added. Current pizzas: 1
        Meat pizza added. Current pizzas: 2
        Tray is full. Sending through conveyor belt...
        Meat pizza added. Current pizzas: 1
        Meat pizza added. Current pizzas: 2
        Tray is full. Sending through conveyor belt...
        Veggie pizza added. Current pizzas: 1
        Veggie pizza added. Current pizzas: 2
        Tray is full. Sending through conveyor belt...
        Veggie pizza added. Current pizzas: 1
        Veggie pizza added. Current pizzas: 2
        Tray is full. Sending through conveyor belt...
        Processing full tray...
        Processing full tray...

    This sample output demonstrates that each pizza type gets two trays full, 
    then moves onto the next tray, for a different pizza type.

(2): 
    The capacity of the tray is calculated by the line:
        int trayCapacity = numberOfPizzas / numberOfTrays;
    Within the conveyor.c file, within the runConveyorBelts function. 
    I thought it important to include this note since it impacts the functionality
    of the program. 

Happy Halloween! 

