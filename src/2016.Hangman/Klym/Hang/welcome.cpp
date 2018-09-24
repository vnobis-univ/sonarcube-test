#include "Global.h"
#include "timer.h"

#include <iostream>
#include <string>
#include <conio.h>

void writeHangman( consoleColourGroup colour, int x, int y );

void welcome()
{
	int yPos = 20;

	writeHangman( LIGHT_RED, 0, yPos );

	con.gotoXY( 13, yPos - 1 );
	std::cout << "Welcome to...";

	timer pressKeyTimer( GetTickCount() );
	bool showText = true;

	std::string pressKey = "PRESS ANY KEY TO START";
	int centerPressKey = ( ( mWidth / 2 ) - ( pressKey.length() / 2 ) );

	while( ! _kbhit() )
	{
		pressKeyTimer.currentTime = GetTickCount() - pressKeyTimer.startTime;

		if( ( pressKeyTimer.currentTime > 200 ) && ( showText ) )
		{
			con.gotoXY( centerPressKey, yPos + 7 );
			std::cout << pressKey;

			pressKeyTimer.startTime = GetTickCount();
			showText = false;
		}

		if( ( pressKeyTimer.currentTime > 600 ) && ( ! showText ) )
		{
			con.gotoXY( centerPressKey, yPos + 7 );
			std::cout << "                      ";

			pressKeyTimer.startTime = GetTickCount();
			showText = true;
		}
	}

	_getch();

	con.clearScreen();
}