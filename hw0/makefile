data: data.o sort.o minmax.o array.o
	gcc -g -o data data.o sort.o minmax.o array.o

main: main.o sort.o minmax.o array.o
	gcc -g -o main main.o sort.o minmax.o array.o

data.o: data.c
	gcc -g -c data.c -std=c99

main.o: main.c
	gcc -g -c main.c -std=c99

sort.o: sort.c
	gcc -g -c sort.c -std=c99

minmax.o: minmax.c
	gcc -g -c minmax.c -std=c99

array.o: array.c
	gcc -g -c array.c -std=c99

clean: 
	rm -f main data *.o *.csv
