/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"
#include "minmax.h"
#include "sort.h"

int cost; // track cost complexity

/* driver program */
int main( int argc, char **argv )
{
	assert( argc > 1 );
	int size;
	size = atoi( argv[1] );
	assert( size > 0 );
	printf( "Size = %d\n", size );

	int buffer[size];
	int alg_cost[9];

	init_array( buffer, size );
	show_array( buffer, size );
	shuffle_array( buffer, size );

	// minmax recursive call
	cost = 0;
	minmax rec = minmax_recursive( buffer, 0, size-1 );
	printf( "Min (rec) = %d\n", buffer[rec.min] );
	printf( "Max (rec) = %d\n", buffer[rec.max] );
	printf( "Cost of minmax (rec) = %d\n", cost );

	printf( "\n" );

	// minmax iterative call
	cost = 0;
	minmax iter = minmax_iterative( buffer, size );
	printf( "Min (iter) = %d\n", buffer[iter.min] );
	printf( "Max (iter) = %d\n", buffer[iter.max] );
	printf( "Cost of minmax (iter) = %d\n", cost );

	printf( "\n" );

	// insertion sort call
	cost = 0;
	insert_sort( buffer, size );
	if ( is_sorted( buffer, size ) == 0 )
		printf( "Sort did not work!\n" );
	else
		printf( "Array is sorted\n" );
	show_array( buffer, size );
	printf( "Cost of Insertion Sort: %d\n", cost );

	printf( "\n" );

	// selection sort call
	shuffle_array( buffer, size );
	cost = 0;
	select_sort( buffer, size );
	if ( is_sorted( buffer, size ) == 0 )
		printf( "Sort did not work!\n" );
	else
		printf( "Array is sorted\n" );
	show_array( buffer, size );
	printf( "Cost of Selection Sort: %d\n", cost );

	printf( "\n" );

	// merge sort call
	shuffle_array( buffer, size );
	cost = 0;
	merge_sort( buffer, 0, size-1 );
	if ( is_sorted( buffer, size ) == 0 )
		printf( "Sort did not work!\n" );
	else
		printf( "Array is sorted\n" );
	show_array( buffer, size );
	printf( "Cost of Merge Sort: %d\n", cost );

	printf( "\n" );

	// quick sort with fixed pivot
	shuffle_array( buffer, size );
	cost = 0;
	qsort_fixed( buffer, size );
	if ( is_sorted( buffer, size ) == 0 )
		printf( "Sort did not work!\n" );
	else
		printf( "Array is sorted\n" );
	show_array( buffer, size );
	printf( "Cost of Quick Sort (Fixed): %d\n", cost );

	printf( "\n" );

	// quick sort with median pivot
	shuffle_array( buffer, size );
	cost = 0;
	qsort_mid( buffer, size );
	if ( is_sorted( buffer, size ) == 0 )
		printf( "Sort did not work!\n" );
	else
		printf( "Array is sorted\n" );
	show_array( buffer, size );
	printf( "Cost of Quick Sort (Median): %d\n", cost );
}
