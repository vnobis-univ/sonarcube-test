

#include "Global.h"
#include "timer.h"

void writeHangman( consoleColourGroup colour, int x, int y );
bool getKeyPressed();

void exitScreen()
{
	con.clearScreen();

	int hmCount = 0;

	int updateTime = 150;
	
	int incrementBy = 5;
	int y = 1;

	bool skip = false;

	timer hmWrite( GetTickCount() );
	hmWrite.currentTime = GetTickCount() - hmWrite.startTime;

	do
	{
		do
		{
			hmWrite.currentTime = GetTickCount() - hmWrite.startTime;

			if( getKeyPressed() )
				skip = true;

		}while( hmWrite.currentTime < updateTime );

		if( skip )
			break;

		switch( hmCount )
		{
			case 0:
				writeHangman( LIGHT_CYAN, 0, y );
				y += incrementBy;
				break;

			case 1:
				writeHangman( WHITE, 0, y );
				y += incrementBy;
				break;

			case 2:
				writeHangman( LIGHT_MAGENTA, 0, y );
				y += incrementBy;
				break;

			case 3:
				writeHangman( LIGHT_GREEN, 0, y );
				y += incrementBy;
				break;

			case 4:
				writeHangman( LIGHT_BLUE, 0, y );
				y += incrementBy;
				break;

			case 5:
				writeHangman( LIGHT_YELLOW, 0, y );
				y += incrementBy;
				break;

			case 6:
				writeHangman( LIGHT_RED, 0, y );
				y += incrementBy;
				break;
		}

		if( hmWrite.currentTime > updateTime )
		{
			++hmCount;
			hmWrite.startTime = GetTickCount();
		}
	
	}while( hmCount < 8 );

	con.write( "Thanks for playing Hangman!", 14, y + 3 );
	
	con.write( "Press any key to exit...", 14, y + 5 );
	con.wait();


}