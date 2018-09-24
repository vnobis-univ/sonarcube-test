

#include "Global.h"

void writeHangman( consoleColourGroup colour, int x, int y );

void help()
{
	writeHangman( LIGHT_RED, 0, 1 );

	const int xPos = 14;
	const int yPos = 10;

	con.write( "Throughout the game, there is no need to press [ENTER].", xPos - 2, yPos );
	con.write( "To make a selection in a menu, or to guess a letter,", xPos - 2, yPos + 1 );
	con.write( "just simply press the key!", xPos - 2, yPos + 2 );

	con.write( "Hopefully you have acquired this application, along with", xPos - 2, yPos + 4 );
	con.write( "it's source code! I'd like to say sorry for the lack of", xPos - 2, yPos + 5 );
	con.write( "commenting throught the code! I use a forum, cplusplus.com,", xPos - 2, yPos + 6 );
	con.write( "and people always ask for homework help. And I'm not one", xPos - 2, yPos + 7 );
	con.write( "to give someone the answer right away!", xPos - 2, yPos + 8 );

	con.wait( "Press any key to continue", xPos - 2, yPos + 11 );

	con.clearScreen();
}