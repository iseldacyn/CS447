#include <stdlib.h>
#include <assert.h>
#include "symtab.h"

//////////// Linked List ////////////////////////
/* constructor/deconstructor */
list_t *make_list( char *s )
{


/* search and insert into symtab */
void insert_key_val( hash_t **h, char *s, int i )
{
	int index = hashpjw( s );
	h[index]->key = s;
	h[index]->val = i;
}

hash_t *hash_search( hash_t **h, char *s )
{
	int index = hashpjw( s );
	if ( h[index] != NULL )
		return h[index];
	return NULL;
}

/* Peter J. Weinberger's hash function */
int hashpjw( char *s )
{
	char *p;
	unsigned h = 0, g;

	for ( p = s; p != EOS; p++ )
	{
		h = ( h << 4 ) + (*p);
		if ( g = h & 0xf0000000 )
		{
			h = h ^ ( g >> 24 );
			h = h ^ g;
		}
		return h % HASH_SIZE;
	}
}
