#pragma once


#include <Windows.h>
#include <iostream>
#include <string>


enum consoleColourGroup
{
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_CYAN,
	DARK_RED,
	DARK_MAGENTA,
	DARK_YELLOW,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	LIGHT_YELLOW,
	WHITE
};


class Console
{
	public:
		Console( unsigned width, unsigned height, HWND hDesktop, LPCSTR cTitle );
		~Console(void);

		void setConsolePosition();
		void GetDesktopResolution( int &h, int &v );

		void changeFontSize( int x, int y );

		char wait( const char *message, int x, int y );
		char wait( const char *message );
		void wait();

		void write( const char *message, int xPos, int yPos );
		void write( const char character, int xPos, int yPos );
		void write( const std::string message, int xPos, int yPos );

		void cursorVisibility( bool visibility );

		void gotoXY( int x, int y );
		void gotoXY( COORD &p );

		void setColour( int t, int b );
		void resetColour();

		void clearScreen();

	private:
		unsigned screenWidth;
		unsigned screenHeight;
		int colour;
		LPCSTR consoleTitle;

		HANDLE hConOut;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		CONSOLE_CURSOR_INFO cci;

		CONSOLE_FONT_INFOEX font;

		const HWND hDesktop;
		HWND consoleWindow;
		
		LPRECT windowRect;
		COORD c;
		COORD pos;
};


