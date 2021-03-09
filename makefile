main: main.o
	gcc -o knapsack main.o
main.o: main.c 
	gcc -c main.c
clean:
	rm knapsack main.o
