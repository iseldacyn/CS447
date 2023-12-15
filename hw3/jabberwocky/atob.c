#include <stdio.h>
#include <stdlib.h>

char *convert_to_byte( int );
int power( int, int );

int main( int argc, char **argv )
{
	FILE *input = fopen( argv[1], "rb" );
	FILE *output = fopen( argv[2], "w" );
	
	int c;
	while( (c = fgetc(input)) != EOF )
	{
		char *b = convert_to_byte(c);
		fputs( b, output );
	}

	fclose(input);
	fclose(output);

	return 0;
}

// convert ASCII 8-byte char to 8-character array
char *convert_to_byte( int c )
{
	char *b = malloc( sizeof(unsigned char) * 8 );
	int d = c;
	for ( int i = 8; i > 0; i-- )
	{
		int curr_bit = power(2, i-1);
		if ( d >= curr_bit )
		{
			b[8-i] = '1';
			d -= curr_bit;
		}
		else
			b[8-i] = '0';
	}
	return b;
}

// returns a^b (b >= 0)
int power( int a, int b )
{
	int c = 1;
	for ( int i = 0; i < b; i++ )
		c *= a;
	return c;
}
