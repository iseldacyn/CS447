#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sort.h"

extern int cost;

/* insertion sort algorithm */
void insert_sort( int buffer[], int size )
{
	if ( size <= 1 ) return;

	for ( int i = 1; i < size; i++ )
	{
		int curr = i;
		int j = i-1;
		// swap elements until current is the left-most
	while ( (j >= 0) && (buffer[curr] < buffer[j]) )
	{
			cost++;
			swap( buffer[curr], buffer[j] );
			j--;
			curr--;
		}
		cost++;
	}
}

/* selection sort algorithm */
void select_sort( int buffer[], int size )
{
	if ( size <= 1 ) return;

	for ( int curr_size = size; curr_size > 0; curr_size-- )
	{
		int max = buffer[0];
		int index = 0;
		for( int i = 0; i < curr_size; i++ )
		{
			cost++;
			if ( buffer[i] > max )
			{
				max = buffer[i];
				index = i;
			}
		}
		swap( buffer[index], buffer[curr_size-1] );
	}
}

/* merge sort algorithm */
void merge_sort( int buffer[], int low, int high )
{
	if ( low == high ) return;

	int mid = (low + high) / 2;
	merge_sort( buffer, low, mid );
	merge_sort( buffer, mid+1, high );
	merge( buffer, low, mid, high );
}

/* supplementary merge function in linear time */
void merge( int buffer[], int low, int mid, int high )
{
	// initialize left and right subarrays
	int size_a1 = mid - low + 1;
	int size_a2 = high - mid;
	int a1[size_a1];
	int a2[size_a2];

	for ( int i = 0; i < size_a1; i++ )
		a1[i] =  buffer[low+i];
	for ( int i = 0; i < size_a2; i++ )
		a2[i] =  buffer[mid+i+1];

	// indexing through left and right subarrays
	int i, j;
	i = 0;
	j = 0;

	// merge the arrays
	int k = low;
	while( (i<size_a1) && (j<size_a2) )
	{
		cost++;
		if( a1[i] <= a2[j] )
		{
			buffer[k] = a1[i];
			i++;
		}
		else
		{
			buffer[k] = a2[j];
			j++;
		}
		k++;
	}

	// add any remaining elements to array
	while( i < size_a1 )
	{
		buffer[k] = a1[i];
		i++;
		k++;
	}
	while( j < size_a2 )
	{
		buffer[k] = a2[j];
		j++;
		k++;
	}
}

/* quick sort with fixed pivot */
void qsort_fixed( int buffer[], int size )
{
	if ( size <= 1 ) return;

	if ( size == 2 )
	{
		cost++;
		if ( buffer[0] > buffer[1] )
			swap( buffer[0], buffer[1] );
		return;
	}

	// set pivot as first element and move aside
	int pivot = buffer[0];
	swap( buffer[0], buffer[size-1] );

	// sort around the pivot
	int l = 0,r = 0;
	int *left = (int *)malloc( sizeof(int) );
	assert( left != NULL );
	int *right = (int *)malloc( sizeof(int) );
	assert( right != NULL );

	for ( int i = 0; i < size-1; i++ )
	{
		cost++;
		if ( buffer[i] < pivot )
		{
			l++;
			left = (int *)realloc( left, sizeof(int) * l );
			assert( left != NULL );
			left[l-1] = buffer[i];
		}
		else
		{
			r++;
			right = (int *)realloc( right, sizeof(int) * r ); 
			assert( right != NULL );
			right[r-1] = buffer[i];
		}
	}

	// replace into array
	int ptr = 0;
	for ( int i = 0; i < l; i++ )
		buffer[ptr++] = left[i];
	buffer[ptr++] = pivot;
	for ( int i = 0; i < r; i++ )
		buffer[ptr++] = right[i];

	// recurse through subarrays
	qsort_fixed( buffer, l );
	qsort_fixed( buffer+l+1, r );
}

/* quick sort with median pivot */
void qsort_mid( int buffer[], int size )
{
	if ( size <= 1 ) return;

	if ( size == 2 )
	{
		cost++;
		if ( buffer[0] > buffer[1] )
			swap( buffer[0], buffer[1] );
		return;
	}

	// find median for pivot and its index
	int pivot = select_K( buffer, size, size/2 );
	int index = 0;
	for ( int i = 0; i < size; i++ )
		if ( buffer[i] == pivot )
		{
			index = i;
			break;
		}

	// move pivot aside
	swap( buffer[index], buffer[size-1] );

	// sort around the pivot
	int l = 0,r = 0;
	int *left = (int *)malloc( sizeof(int) );
	assert( left != NULL );
	int *right = (int *)malloc( sizeof(int) );
	assert( right != NULL );

	for ( int i = 0; i < size-1; i++ )
	{
		cost++;
		if ( buffer[i] <= pivot )
		{
			l++;
			left = (int *)realloc( left, sizeof(int) * l );
			assert( left != NULL );
			left[l-1] = buffer[i];
		}
		else
		{
			r++;
			right = (int *)realloc( right, sizeof(int) * r ); 
			assert( right != NULL );
			right[r-1] = buffer[i];
		}
	}

	// replace into array
	int ptr = 0;
	for ( int i = 0; i < l; i++ )
		buffer[ptr++] = left[i];
	buffer[ptr++] = pivot;
	for ( int i = 0; i < r; i++ )
		buffer[ptr++] = right[i];

	// recurse through subarrays
	qsort_mid( buffer, l );
	qsort_mid( buffer+l+1, r );
}

/* find Kth smallest element in an array */
int select_K( int buffer[], int size, int K )
{
	// base case
	if ( size < 5 )
	{
		assert( 0<=K && K<5 );
		bubble_sort( buffer, size );
		return buffer[K];
	}

	// sort blocks of 5
	for ( int i = 0; i+5<size; i+=5 )
		bubble_sort( buffer+i, 5 );

	// make subarray of medians
	int num_medians = size/5;
	int medians[num_medians];
	
	for ( int i = 0; i < num_medians; i++ )
		medians[i] = buffer[i+2];

	// find the median of medians
	int pivot = select_K( medians, num_medians, num_medians/2 );

	// find the index of the pivot
	int index = 0;
	for ( int i = 0; i < size; i++ )
	{
		if ( buffer[i] == pivot ) 
		{
			index = i;
			break;
		}
	}

	// set the pivot aside
	swap( buffer[index], buffer[size-1] );

	// partition around the pivot
	int l = 0, r = 0;
	int *left = (int *)malloc( sizeof(int) );
	assert( left != NULL );
	int *right = (int *)malloc( sizeof(int) );
	assert( right != NULL );

	for ( int i = 0; i < size-1; i++ )
	{
		cost++;
		if ( buffer[i] <= pivot )
		{
			l++;
			left = (int *)realloc( left, sizeof(int) * l );
			assert( left != NULL );
			left[l-1] = buffer[i];
		}
		else
		{
			r++;
			right = (int *)realloc( right, sizeof(int) * r ); 
			assert( right != NULL );
			right[r-1] = buffer[i];
		}
	}

	// recurse through left subarray
	if ( K < l )
		return select_K( left, l, K );
	// answer is pivot
	else if ( K == l )
		return pivot;
	// recurse through right subarray
	else
		return select_K( right, r, K-(l+1) );
}

/* bubble sort algorithm for select */
void bubble_sort( int buffer[], int size )
{
	for ( int i = size-1; i > 0; i-- )
	{
		for ( int j = 0; j < i; j++ )
		{
			cost++;
			if ( buffer[j] > buffer[j+1] )
				swap( buffer[j], buffer[j+1] );
		}
	}
}
