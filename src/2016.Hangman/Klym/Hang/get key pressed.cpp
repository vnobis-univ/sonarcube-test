

#include <conio.h>

bool getKeyPressed( char &k )
{
	if( _kbhit() )
	{
		k = _getch();
		return true;
	}

	return false;
}

bool getKeyPressed()
{
	if( _kbhit() )
	{
		_getch();
		return true;
	}

	return false;
}