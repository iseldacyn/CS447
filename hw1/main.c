/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "graph.h"

/* main function */
int main(int argc, char **argv)
{
	srand(time(NULL));

	// initialize runtime file
	FILE *input = fopen( argv[1], "r" );

	// read in number of switches and bulbs from file
	int switches, bulbs;
	fscanf( input, "%d", &switches );
	fscanf( input, "%d", &bulbs );

	// initialize graph to have N switches
	vertex_t *graph = make_vertex( "root", bulbs );
	char **vars = malloc( sizeof(char *) * switches * 2  );
	assert( vars != NULL );
	for( int i = 0; i < switches; i++ )
	{
		vars[i*2] = malloc( sizeof(char) * 2 );
		assert( vars[i*2] != NULL );
		vars[i*2+1] = malloc( sizeof(char) * 3 );
		assert( vars[i*2+1] != NULL );

		// index i*2 = xi, i*2+1 = Nxi
		sprintf( vars[i*2], "x%d", i+1 );
		add_new_edge( graph, vars[i*2] );
		sprintf( vars[i*2+1], "Nx%d", i+1 );
		add_new_edge( graph, vars[i*2+1] );
	}

	// read in conditions from file
	int *bulb_conds = malloc( sizeof(int) * bulbs * 2);
	for( int i = 0; i < bulbs; i++ )
	{
		int cond1, cond2;
		fscanf( input, "%d %d", &cond1, &cond2 );
		bulb_conds[i*2] = cond1;
		bulb_conds[i*2+1] = cond2;

 		// weird way to map condition variable itself to index where its stored
		// adds edges ( p|q => !p->q === !q->p ) to graph
		// four conditions for !a|!b , !a|b , a|!b , a|b
		if( cond1 < 0 )
		{
			if( cond2 < 0 )
			{
				// both conditions negative
				add_edge( graph->edges[-cond1*2-2], graph->edges[-cond2*2-1] );
				add_edge( graph->edges[-cond2*2-2], graph->edges[-cond1*2-1] );
			}
			else
			{
				// only first condition negative
				add_edge( graph->edges[-cond1*2-2], graph->edges[cond2*2-2] );
				add_edge( graph->edges[cond2*2-1], graph->edges[-cond1*2-1] );
			}
		}
		else
		{
			if( cond2 < 0 )
			{
				// only second condition negative
				add_edge( graph->edges[cond1*2-1], graph->edges[-cond2*2-1] );
				add_edge( graph->edges[-cond2*2-2], graph->edges[cond1*2-2] );
			}
			else
			{
				// both conditions positive
				add_edge( graph->edges[cond1*2-1], graph->edges[cond2*2-2] );
				add_edge( graph->edges[cond2*2-1], graph->edges[cond1*2-2] );
			}
		}
	}
	// display graph to the terminal [DEBUGGING]
	//print_graph( graph );

	// dfs-like search for all connections
	dfs_search( graph );

	// display which nodes each node could reach [DEBUGGING]
	/*
	for( int i = 0; i < switches*2; i++ )
	{
		fprintf( stderr, "switch %s can reach switches: ", graph->edges[i]->name );
		for( int j = 0; j < switches*2; j++ )
		{
			if( graph->edges[i]->can_reach[j] == 1 )
			{
				fprintf( stderr, "%s ", graph->edges[j]->name );
			}
		}
		fprintf( stderr, "\n" );
	}
	*/

	// check for loops within system
	for( int i = 0; i < switches; i++ )
	{
		if( graph->edges[i*2]->can_reach[i*2+1] && graph->edges[i*2+1]->can_reach[i*2] )
		{
			printf( "NO: Node %s -> %s and %s -> %s\n", graph->edges[i*2]->name, graph->edges[i*2+1]->name, graph->edges[i*2+1]->name, graph->edges[i*2]->name );
			exit(1);
		}
		if( graph->edges[i*2]->can_reach[i*2+1] )
		{
			graph->edges[i*2]->status = 0;
			graph->edges[i*2+1]->status = 1;
			graph->edges[i*2]->can_change = 0;
			graph->edges[i*2+1]->can_change = 0;
		}
		else if( graph->edges[i*2+1]->can_reach[i*2] )
		{
			graph->edges[i*2]->status = 1;
			graph->edges[i*2+1]->status = 0;
			graph->edges[i*2]->can_change = 0;
			graph->edges[i*2+1]->can_change = 0;
		}
		// random walk algorithm
		else{
			graph->edges[i*2]->status = rand() % 2;
			graph->edges[i*2+1]->status = !graph->edges[i*2]->status;
		}
	}

	// random walk on a line
	int *unsolved_bulbs = check_bulbs( graph, bulb_conds, bulbs );
	int solved = unsolved_bulbs[0];
	int hanging = 0;
	while( !solved )
	{
		int n = rand() % unsolved_bulbs[1] + 2;
		int bulb_to_change = unsolved_bulbs[n];
		int index1, index2;
		if( bulb_conds[bulb_to_change*2] < 0 )
			index1 = -bulb_conds[bulb_to_change*2]*2 - 1;
		else
			index1 = bulb_conds[bulb_to_change*2]*2 - 2;
		if( bulb_conds[bulb_to_change*2+1] < 0 )
			index2 = -bulb_conds[bulb_to_change*2+1]*2 - 1;
		else
			index2 = bulb_conds[bulb_to_change*2+1]*2 - 2;

		int switch_to_change = rand() % 2 + 1;

		if( graph->edges[index1]->can_change && switch_to_change == 1 )
		{
			graph->edges[index1]->status = !graph->edges[index1]->status;
			if( index1 % 2 == 0 )
				graph->edges[index1+1]->status = !graph->edges[index1+1]->status;
			else
				graph->edges[index1-1]->status = !graph->edges[index1-1]->status;
		}
		else if( graph->edges[index2]->can_change && switch_to_change == 2 )
		{
			graph->edges[index2]->status = !graph->edges[index2]->status;
			if( index2 % 2 == 0 )
				graph->edges[index2+1]->status = !graph->edges[index2+1]->status;
			else
				graph->edges[index2-1]->status = !graph->edges[index2-1]->status;
		}
		else
		{
			printf( "NO: Bulb %d has two unchangable switches, %d and %d\n", bulb_to_change+1, index1/2, index2/2 );
			exit(1);
		}

		unsolved_bulbs = check_bulbs( graph, bulb_conds, bulbs );
		solved = unsolved_bulbs[0];
		hanging++;
		if( hanging > 10000 )
			srand(time(NULL));
	}

	check_graph( graph );

	printf( "YES:\n[ " );
	for( int i = 0; i < switches; i++ )
	{
		if( graph->edges[i*2]->status )
			printf( "%d ", i+1 );
		else
			printf( "-%d ", i+1 );
		if( i != switches-1 )
			printf( ", " );
	}
	printf( "]\n" );

	// free when done
	free_vertex( graph );
	free( bulb_conds );
	free( vars );
	fclose( input );
}
