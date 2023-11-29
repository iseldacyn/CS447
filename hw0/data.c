#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"
#include "sort.h"
#include "minmax.h"

int cost;

int main()
{
	FILE *mm = fopen( "minmax_output.csv", "w" );
	FILE *sort = fopen( "sort_output.csv", "w" );
	FILE *median = fopen( "median_output.csv", "w" );

	for( int size = 1; size < 1001; size++ )
	{
		char str[10];

		int s[size];
		init_array( s, size );
		shuffle_array( s, size );

		cost = 0;
		minmax_recursive( s, 0, size-1 );
		sprintf( str, "%d,", cost );
		fputs( str, mm );

		cost = 0;
		minmax_iterative( s, size );
		sprintf( str, "%d\n", cost );
		fputs( str, mm );

		if ( size > 128 ) 
			continue;

		int i[size], r[size], f[size], q[size], m[size];
		copy_array( s, i, size );
		copy_array( s, r, size );
		copy_array( s, f, size );
		copy_array( s, q, size );
		copy_array( s, m, size );

		cost = 0;
		select_sort( s, size );
		assert( is_sorted( s, size ) );
		sprintf( str, "%d,", cost );
		fputs( str, sort );

		cost = 0;
		insert_sort( i, size );
		assert( is_sorted( i, size ) );
		sprintf( str, "%d,", cost );
		fputs( str, sort );

		cost = 0;
		merge_sort( r, 0, size-1 );
		assert( is_sorted( r, size ) );
		sprintf( str, "%d,", cost );
		fputs( str, sort );

		cost = 0;
		qsort_fixed( f, size );
		assert( is_sorted( f, size ) );
		sprintf( str, "%d,", cost );
		fputs( str, sort );

		cost = 0;
		qsort_mid( q, size ); 
		assert( is_sorted( q, size ) );
		sprintf( str, "%d\n", cost );
		fputs( str, sort );

		cost = 0;
		select_K( m, size, size/2 );
		sprintf( str, "%d\n", cost );
		fputs( str, median );
	}

	fclose( mm );
	fclose( sort );
	fclose( median );
}
