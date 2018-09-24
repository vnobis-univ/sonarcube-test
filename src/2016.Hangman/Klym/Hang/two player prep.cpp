

#include "Global.h"

void writeHangman( consoleColourGroup colour, int x, int y );

std::string twoPlayerPrep()
{
	con.cursorVisibility( true );

	bool invalid = false;

	int xPos = 14;
	int yPos = 10;

	std::string input;

	do
	{
		con.clearScreen();

		writeHangman( LIGHT_RED, 0, 1 );

		con.write( "Word/Phrase entry. Only letters/spaces are valid entry!", xPos, yPos );

		con.write( "Player two, look away NOW!", xPos, yPos + 2 );
		con.write( "Player one, enter the word/phrase:", xPos, yPos + 3 );

		con.gotoXY( xPos, yPos + 4 );
		std::getline( std::cin, input, '\n' );

		for( unsigned int i = 0; i < input.length(); ++i )
		{
			if( ( tolower( input[ i ] ) < 97 ) || ( tolower( input[ i ] ) > 122 ) )
				invalid = true;
			else
				invalid = false;

			if( tolower( input[ i ] ) == ' ' )
				invalid = false;

			if( invalid )
				break;
		}
	
	}while( invalid );

	con.cursorVisibility( false );
	con.clearScreen();

	return input;
}