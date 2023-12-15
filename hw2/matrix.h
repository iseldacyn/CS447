#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix_s
{
	int row, col;
	int **data;
} matrix_t;

matrix_t *make_matrix();
void add_row( matrix_t * );
void add_col( matrix_t * );
void insert( matrix_t *, int, int, int );

#endif
