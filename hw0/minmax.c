#include <stdlib.h>
#include "minmax.h"

extern int cost;

/* linear time min algorithm */
int min( int buffer[] , int size )
{
	int i = 0;
	for ( int j = 0; j < size; j++ )
	{
		cost++;
		if ( buffer[j] < buffer[i] )
			i = j;
	}
	return i;
}

/* linear time max algorithm */
int max( int buffer[] , int size )
{
	int i = 0;
	for ( int j = 0; j < size; j++ )
	{
		cost++;
		if ( buffer[i] < buffer[j] )
			i = j;
	}
	return i;
}

/* minmax-recursive algorithm */
minmax minmax_recursive( int buffer[], int low, int high )
{
	minmax mm;
	// size = 1
	if ( low == high )
	{
		mm.min = low;
		mm.max = high;
		return mm;
	}

	// size = 2
	if ( high == low+1 )
	{
		cost++;
		if ( buffer[low] < buffer[high] )
		{
			mm.min = low;
			mm.max = high;
		}	
		else
		{
			mm.min = high;
			mm.max = low;
		}
		return mm;
	}

	// recursive call
	int mid = ( low + high ) / 2;
	minmax mm_left = minmax_recursive( buffer, low, mid );
	minmax mm_right = minmax_recursive( buffer, mid+1, high );

	cost++;
	if ( buffer[mm_left.min] < buffer[mm_right.min] )
		mm.min = mm_left.min;
	else
		mm.min = mm_right.min;

	cost++;
	if ( buffer[mm_left.max] > buffer[mm_right.max] )
		mm.max = mm_left.max;
	else
		mm.max = mm_right.max;

	return mm;
}

/* minmax-iterative algorithm */
minmax minmax_iterative( int buffer[], int size )
{
	minmax mm;
	int i;
	
	// if even, set start as 2
	if ( size % 2 == 0 )
	{
		cost++;
		if ( buffer[0] < buffer[1] )
		{
			mm.min = 0;
			mm.max = 1;
		}
		else
		{
			mm.min = 1;
			mm.max = 0;
		}
		i = 2;
	}
	// if odd, set start as 1
	else
	{
		mm.min = 0;
		mm.max = 0;
		i = 1;
	}

	// compare elements in a pair
	while ( i < size-1 )
	{
		cost++;
		if ( buffer[i] < buffer[i+1] )
		{
			cost++;
			if ( buffer[i] < buffer[mm.min] )
				mm.min = i;

			cost++;
			if ( buffer[i+1] > buffer[mm.max] )
				mm.max = i+1;
		}
		else
		{
			cost++;
			if ( buffer[i+1] < buffer[mm.min] )
				mm.min = i+1;

			cost++;
			if ( buffer[i] > buffer[mm.max] )
				mm.max = i;
		}

		// check next pair of elements
		i += 2;
	}

	return mm;
}
