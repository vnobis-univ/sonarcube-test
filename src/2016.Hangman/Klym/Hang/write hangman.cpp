

#include "Global.h"

#include <fstream>
#include <vector>
#include <string>

void writeHangman( consoleColourGroup colour, int x, int y )
{
	std::ifstream inFile;
	std::vector< std::string >sVec;

	inFile.open( "hangmanWelcome.txt", std::ios::in );
	
	if( inFile.is_open() )
	{
		std::string input;

		while( inFile.good() )
		{
			std::getline( inFile, input, '\n' );

			sVec.push_back( input );
		}

		inFile.close();
	}
	else
		con.wait( "Unable to open hangmanWelcome.txt." );

	if( x == 0 )
		x = ( ( mWidth / 2 ) - ( sVec[ 0 ].length() / 2 ) );

	con.setColour( colour, BLACK );

	for( int index = 0; index < 6; ++index )
	{
		con.gotoXY( x, index + y );

		std::cout << sVec[ index ];
	}

	con.resetColour();

	std::string coded = "Special for V.Nobis!";
	int codedXPos = ( mWidth - coded.length() );

	con.gotoXY( codedXPos, mHeight - 2 );
	std::cout << coded;
}