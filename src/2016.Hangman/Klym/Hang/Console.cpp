#include "Console.h"


#include <conio.h>

Console::Console(  unsigned width, unsigned height, HWND hDesktop, LPCSTR cTitle )
		: screenWidth( width ), screenHeight( height ), hDesktop( GetDesktopWindow() ), consoleTitle( cTitle )
{
	hConOut = GetStdHandle( STD_OUTPUT_HANDLE );
	GetConsoleScreenBufferInfo( hConOut, &csbi );

	consoleWindow = GetConsoleWindow();

	SetConsoleTitle( consoleTitle );

	//changeFontSize( 7, 7 );	
	
	c.X = screenWidth;
	c.Y = screenHeight;
	SetConsoleScreenBufferSize( hConOut, c );

	ShowWindow( consoleWindow, SW_MAXIMIZE );

	setConsolePosition();
}

Console::~Console(void)
{
	
	SetConsoleTextAttribute( hConOut, csbi.wAttributes );
	SetConsoleScreenBufferSize( hConOut, csbi.dwSize );
	SetConsoleWindowInfo( hConOut, TRUE, &csbi.srWindow );

	cci.bVisible = true;
	SetConsoleCursorInfo( hConOut, &cci );

	
	changeFontSize( 8, 12 );
}

char Console::wait( const char *message, int x, int y )
{
	gotoXY( x, y );

	std::cout << message;

	while( ! _kbhit() )
	{ /* */}

	return _getch();
}

char Console::wait( const char *message )
{
	std::cout << message;

	while( ! _kbhit() )
	{ /* */ }

	return _getch();
}

void Console::wait()
{
	while( ! _kbhit() )
	{ /**/ }

	_getch();
}

void Console::write( const char *message, int xPos, int yPos )
{
	gotoXY( xPos, yPos );
	std::cout << message;
}

void Console::write( const char character, int xPos, int yPos )
{
	gotoXY( xPos, yPos );
	std::cout << character;
}

void Console::write( const std::string message, int xPos, int yPos )
{
	gotoXY( xPos, yPos );
	std::cout << message;
}

void Console::setColour( int t, int b )
{
	colour = ( t + ( b * 16 ) );
	SetConsoleTextAttribute( hConOut, colour );
}

void Console::resetColour()
{
	SetConsoleTextAttribute( hConOut, 7 );
}

void Console::setConsolePosition()
{
	
	SetWindowPos( consoleWindow, 0, 350, 150, 10, 10, SWP_NOSIZE | SWP_NOZORDER );
}

void Console::GetDesktopResolution( int &h, int &v )
{
	RECT desktop;	

	GetWindowRect( hDesktop, &desktop );

	h = desktop.right;
	v = desktop.bottom;
}

void Console::gotoXY( int x, int y )
{
	

	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition( hConOut, pos );
}

void Console::gotoXY( COORD &p )
{
	SetConsoleCursorPosition( hConOut, p );
}

void Console::cursorVisibility( bool visibility )
{
	cci.bVisible = visibility;
	cci.dwSize = 10;

	SetConsoleCursorInfo( hConOut, &cci );
}

void Console::changeFontSize( int x, int y )
{
	font.cbSize = sizeof( CONSOLE_FONT_INFOEX );

	GetCurrentConsoleFontEx( hConOut, false, &font );

	font.dwFontSize.X = x;
	font.dwFontSize.Y = y;
	
	SetCurrentConsoleFontEx( hConOut, false, &font );
}

void Console::clearScreen()
{
	COORD coordScreen = { 0, 0 };   
	DWORD cCharsWritten;
	DWORD dwConSize;


	if( ! GetConsoleScreenBufferInfo( hConOut, &csbi ) )
		return;

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;


	if( ! FillConsoleOutputCharacter( hConOut, ( TCHAR ) ' ',
		dwConSize, coordScreen, &cCharsWritten ) )
		return;


	if( ! GetConsoleScreenBufferInfo( hConOut, &csbi ) )
		return;


	if( ! FillConsoleOutputAttribute( hConOut, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten ) )
		return;

	SetConsoleCursorPosition( hConOut, coordScreen );
}