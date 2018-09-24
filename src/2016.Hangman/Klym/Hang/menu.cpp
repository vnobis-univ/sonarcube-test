

#include "Global.h"

#include <iostream>

void writeHangman( consoleColourGroup colour, int x, int y );
bool getKeyPressed( char &k );

int menu()
{
	writeHangman( LIGHT_RED, 0, 1 );

	const int xPos = 14;
	const int yPos = 10;

	char key = ' ';

	con.write( "Press a number to select an option.", xPos, yPos );

	con.write( "1. One Player game.", xPos, yPos + 1 );
	con.write( "2. Two Player game.", xPos, yPos + 2 );
	con.write( "3. Help/Info.", xPos, yPos + 3 );
	con.write( "4. Exit.", xPos, yPos + 4 );

	do
	{
		while( ! getKeyPressed( key ) )
		{ /* */ }

		getKeyPressed( key );

		switch( key )
		{
			case '1':
				return 1;

			case '2':
				return 2;

			case '3':
				return 3;

			case '4':
				return 4;

			default:
				break;
		}

	}while( true );
}