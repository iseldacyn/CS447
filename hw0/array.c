#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"
#include "sort.h"

/* initializes array */
void init_array( int buffer[], int size)
{
	for ( int i = 0; i < size; i++ )
		buffer[i] = i;
}

/* print function */
void show_array( int buffer[], int size )
{
	printf( "[ " );
	for ( int i = 0; i < size; i++ )
		printf( "%d ", buffer[i] );
	printf( "]\n" );
}

/* copy function */
void copy_array( int old[], int new[], int size )
{
	for ( int i = 0; i < size; i++ )
		new[i] = old[i];
}

/* randomly shuffle generated array */
void shuffle_array( int buffer[], int size )
{
	srand( time(0) ); // seed the random generator
	for ( int i = size; i > 0; i-- ) {
		int index = rand() % i; // index is in the range of [0,i-1]
		if ( index < i-1 )
			swap( buffer[index], buffer[i-1] );
	}
}

/* check if an array is sorted */
int is_sorted( int buffer[], int size )
{
	for ( int i = 0; i < size-1; i++ )
		if ( buffer[i] > buffer[i+1] )
			return 0;
	return 1;
}
