main: main.o graph.o
	gcc -g -o main graph.o main.o

main.o: main.c
	gcc -g -c main.c

graph.o: graph.c
	gcc -g -c graph.c

clean: 
	rm -f main *.o
