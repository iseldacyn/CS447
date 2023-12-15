#include <stdlib.h>
#include "matrix.h"

/* 0x0 matrix with no data */
matrix_t *make_matrix()
{
	matrix_t *m;
	m->row = 0;
	m->col = 0;
	m->data = NULL;
}

/* add row to matrix */
void add_row( matrix_t *m )
{
	m->row++;
	m->data = realloc( m->data, sizeof(int *) * m->row );
}

/* add col to matrix */
void add_col( matrix_t *m )
{
	m->col++;
	for( int i = 0; i < m->row; i++ )
		m->data[i] = realloc( m->data[i], sizeof(int) * m->col );
}

/* insert d to position x,y in m */
void insert( matrix_t *m, int x, int y, int d )
{
	m->data[x][y] = d;
}
