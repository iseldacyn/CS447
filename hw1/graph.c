#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

void aux_print_graph( vertex_t *, int );
int solve_vertex( vertex_t * );
int solve_vertex_if_true( vertex_t * );

/* make and free functions */
vertex_t *make_vertex( char *name, int connect )
{
	vertex_t *v = (vertex_t *)malloc( sizeof(vertex_t) );
	assert( v != NULL );
	v->name = name;
	v->status = 0;
	v->can_reach = malloc( sizeof(int) * connect );
	v->can_reach_size = connect;
	v->can_change = 1;
	for( int i = 0; i < connect; i++ )
		v->can_reach[i] = 0;
	v->found_pointer = 0;
	v->connections = 0;
	v->edges = NULL;
	return v;
}

void free_vertex( vertex_t *v )
{
	if( v == NULL ) return;

	if( v->found_pointer != 1 )
	{
		v->found_pointer = 1;
		for( int i = 0; i < v->connections; i++ )
		{
			free_vertex( v->edges[i] );
		}
		free( v );
	}
}

/* additional utility functions */
void add_new_edge( vertex_t *v, char *name )
{
	v->connections++;
	v->edges = realloc( v->edges, sizeof(vertex_t *) * v->connections );
	// adds an edge to a newly created vertex
	v->edges[v->connections-1] = make_vertex( name, v->can_reach_size );
}

void add_edge( vertex_t *v, vertex_t *c )
{
	v->connections++;
	v->edges = realloc( v->edges, sizeof(vertex_t *) * v->connections );
	// adds an edge to an existing vertex
	v->edges[v->connections-1] = c;
}

int is_an_edge( vertex_t *v, vertex_t *c )
{
	for( int i = 0; i < v->connections; i++ )
	{
		// checks if there is an edge between two vertices
		if( v->edges[i]->name == c->name )
			return 1;
	}
	return 0;
}

void reset_connections( vertex_t *v )
{
	for( int i = 0; i < v->connections; i++ )
	{
		// resets found_pointer for use in later functions
		v->edges[i]->found_pointer = 0;
	}
}

/* dfs-like search through graph */
/* I decided to use DFS because, though not complete, (may infinite loop)
 * it allows an easier/more intuitive method of mapping out the graph
 * and connections between each vertex
 */
void dfs_search( vertex_t *v )
{
	if( v == NULL ) return;

	if( v->found_pointer != 10 )
	{
		v->found_pointer = 10;
		
		for( int i = 0; i < v->connections; i++ )
		{
			// recursive dfs call
			dfs_search( v->edges[i]);

			if( v->name[0] == 'r' )
			{
				// adds all found nodes to current nodes reachable array
				for( int j = 0; j < v->connections; j++ )
					if( v->edges[j]->found_pointer == 10 )
						if( i != j )
							v->edges[i]->can_reach[j] = 1;
				// reset all found nodes for next loop
				reset_connections( v );
			}
		}
	}
}

/* checks if all bulb conditions are true */
int *check_bulbs( vertex_t *v, int *conds, int num )
{
	int n = 1;
	int *unsolved = malloc( sizeof(int) * 2 );
	unsolved[0] = 1;
	unsolved[1] = 0;
	for( int i = 0; i < num; i++ )
	{
		int index1, index2;
		if( conds[i*2] < 0 )
			index1 = -conds[i*2]*2 - 1;
		else
			index1 = conds[i*2]*2 - 2;
		if( conds[i*2+1] < 0 )
			index2 = -conds[i*2+1]*2 - 1;
		else
			index2 = conds[i*2+1]*2 - 2;

		if( v->edges[index1]->status || v->edges[index2]->status );
		else
		{
			// change to unsolved problem
			unsolved[0] = 0;
			// increment number of bulbs unsolved
			unsolved[1]++;
			n++;
			unsolved = realloc( unsolved, sizeof(int) * n+1 );
			// add index of bulb to array
			unsolved[n] = i;
		}
	}
	return unsolved;
}

/* walk through graph to ensure everything looks good */
void check_graph( vertex_t *v )
{
}

/* print function */
void print_graph( vertex_t *v )
{
	// for spacing
	aux_print_graph( v, 0 );
}

void aux_print_graph( vertex_t *v, int n )
{
	if( v == NULL ) return;

	if( v->found_pointer != 5 )
	{
		v->found_pointer = 5;

		if( v->connections == 0 )
		{
			for( int i = 0; i < n; i++ )
				fprintf( stderr, " " );
			fprintf( stderr, "%s\n", v->name );
		}
		for( int i = 0; i < v->connections; i++ )
		{
			for( int i = 0; i < n; i++ )
				fprintf( stderr, " " );
			fprintf( stderr, "%s -> \n", v->name );
			aux_print_graph( v->edges[i], n+5 );

			if( v->name[0] == 'r' )
				reset_connections( v );
		}
	}
	else
	{
		for( int i = 0; i < n; i++ )
			fprintf( stderr, " " );
		fprintf( stderr, "%s\n", v->name );
	}
}
