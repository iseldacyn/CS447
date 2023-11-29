#ifndef MINMAX_H
#define MINMAX_H

typedef struct minimummaximum
{
	int min;
	int max;
} minmax;

/* linear time minmax */
int min( int [], int );
int max( int [], int );

/* minmax in one */
minmax minmax_recursive( int[], int, int );
minmax minmax_iterative( int[], int );

#endif
