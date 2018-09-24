

#include "Global.h"

void drawBox()
{
	char horizontal = ( char )205;
	char vertical = ( char ) 186;
	char topLeft = ( char ) 201;
	char bottomLeft = ( char ) 200;

	char topRight = ( char ) 187;
	char bottomRight = ( char ) 188;


	for( int i = 0; i < 20; ++i )
	{
		con.gotoXY( 14, i + 10 );
		std::cout << vertical;

		con.gotoXY( 65, i + 10 );
		std::cout << vertical;
	}

	for( int i = 0; i < 50; ++i )
	{
		con.gotoXY( i + 15, 9 );
		std::cout << horizontal;

		con.gotoXY( i + 15, 30 );
		std::cout << horizontal;
	}

	con.write( topLeft, 14, 9 );
	con.write( topRight, 65, 9 );
	con.write( bottomLeft, 14, 30 );
	con.write( bottomRight, 65, 30 );
}