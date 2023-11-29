main: main.o graph.o
	gcc -g -o main graph.o main.o

main.o: main.c
	gcc -g -c main.c -std=c99

graph.o: graph.c
	gcc -g -c graph.c -std=c99

clean: 
	rm -f main *.o
