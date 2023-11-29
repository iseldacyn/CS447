#ifndef SORT_H
#define SORT_H

// macro to swap a pair of elements
#define swap_unsafe(a,b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))
#define swap(a,b) ((&(a) == &(b)) ? (a) : swap_unsafe(a,b))

/* helper functions */
void merge( int[], int, int, int );
void bubble_sort( int[], int );
int select_K( int[], int, int );

/* sorting algorithms */
void insert_sort( int[], int );
void select_sort( int[], int );
void merge_sort( int[], int, int );
void qsort_fixed( int[], int );
void qsort_mid( int[], int );

#endif
