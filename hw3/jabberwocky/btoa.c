#include <stdio.h>
#include <stdlib.h>

int convert_to_ascii( char * );
int power( int, int );

int main( int argc, char **argv )
{
	FILE *input = fopen( argv[1], "rb" );
	FILE *output = fopen( argv[2], "w" );
	
	char *s = malloc( sizeof(unsigned char) * 9 );
	while( fgets( s, 9, input ) != NULL )
	{
		int c = convert_to_ascii( s );
		fputc( c, output );
	}

	fclose(input);
	fclose(output);

	return 0;
}

// convert 8-character array to ASCII int
int convert_to_ascii( char *c )
{
	int d = 0;
	for ( int i = 0; i < 8; i++ )
	{
		int curr_bit = power(2, 7-i);
		d += curr_bit * (c[i] - '0');
	}
	return d;
}

// returns a^b (b >= 0)
int power( int a, int b )
{
	int c = 1;
	for ( int i = 0; i < b; i++ )
		c *= a;
	return c;
}
