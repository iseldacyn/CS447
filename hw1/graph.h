#ifndef GRAPH_H
#define GRAPH_H

typedef struct vertex_s
{
	// name attribute (of node)
	char *name;

	// value of node ( ON or OFF )
	int status;

	// array of indices node can reach + its size
	int *can_reach;
	int can_reach_size;

	// in case node N can reach !N
	// or, dispute in random walk around graph
	int can_change;

	// 1 for free, 5 for print, 10 for search
	int found_pointer;

	// number of edges on node
	int connections;

	// edges for graph search
	struct vertex_s **edges;
}vertex_t;

vertex_t *make_vertex( char *, int );
void free_vertex( vertex_t * );
void add_new_edge( vertex_t *, char * );
void add_edge( vertex_t *, vertex_t * );
int is_an_edge( vertex_t *, vertex_t * );
void dfs_search( vertex_t * );
int *check_bulbs( vertex_t *, int *, int );
void check_graph( vertex_t * );
void print_graph( vertex_t * );

#endif
