bobo: pizzaOven.o conveyorBelt.o conveyor.o
	gcc pizzaOven.o conveyorBelt.o conveyor.o -o bobo -pthread

pizzaOven.o: pizzaOven.c conveyorBelt.h conveyor.h
	gcc -c pizzaOven.c

conveyorBelt.o: conveyorBelt.c conveyorBelt.h conveyor.h
	gcc -c conveyorBelt.c

conveyor.o: conveyor.c conveyor.h
	gcc -c conveyor.c