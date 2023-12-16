#ifndef SYMTAB_H
#define SYMTAB_H

#define HASH_SIZE 211
#define EOS '\0'

typedef struct list_s
{
	char *key;
	int val;
	struct list_s *next;
}

/* constructor/deconstructor */
list_t *make_list( char * );
void free_list( list_t * );

/* insert/search */
list_t *list_insert( list_t *, char *, int );
list_t *list_search( list_t *, char * );

typedef struct hash_s
{
	list_t *table[HASH_SIZE];
} hash_t;

/* constructor/deconstructor */

/* search/insert */
list_t *hash_insert( hash_t **, char *, int );
list_t *hash_search( hash_t **, char * );

int hashpjw( char * );
