

#include "Global.h"


void drawHangman( int n )
{
	switch( n )
	{
		case 0:
			con.setColour( DARK_BLUE, BLACK );

			con.gotoXY( 28, 28 );
			std::cout << '[';

			con.setColour( LIGHT_GRAY, BLACK );

			for( int i = 0; i < 7; ++i )
				std::cout << ( char ) 205;

			std::cout << ( char ) 202;

			for( int i = 0; i < 7; ++i )
				std::cout << ( char ) 205;

			con.setColour( DARK_BLUE, BLACK );
			std::cout << ']';
			break;

		case 1:
			con.gotoXY( 36, 11 );
			std::cout << ( char ) 201;

			for( int i = 0; i < 16; ++i )
			{
				con.gotoXY( 36, i + 12 );
				std::cout << ( char ) 186;
			}

			break;

		case 2:
			for( int i = 0; i < 10; ++i )
			{
				con.gotoXY( i + 37, 11 );
				std::cout << ( char ) 205;
			}

			std::cout << ( char ) 187;
			break;

		case 3:
			con.setColour( DARK_MAGENTA, BLACK );

			con.write( ( char ) 219, 47, 12 );
			break;

		case 4:
			con.setColour( DARK_RED, BLACK );

			for( int i = 0; i < 3; ++i )
			{
				con.gotoXY( 47, i + 13 );
				std::cout << ( char ) 186;
			}
			break;

		case 5:
			con.setColour( LIGHT_YELLOW, BLACK );
			con.write( "MMM", 46, 16 );

			con.setColour( LIGHT_GRAY, BLACK );
			con.write( "{o_o}", 45, 17 );

			break;

		case 6:
			{
				std::string body[ 3 ] = { " /   \\ ",
										  " |   |",
										  "  \\_/" };

				for( int i = 0; i < 3; ++i )
				{
					con.gotoXY( 44, i + 18 );
					std::cout << body[ i ];
				}
				break;
			}

		case 7:
			con.write( '_', 44, 18 );
			con.write( 'o', 43, 18 );
			break;

		case 8:
			con.write( '_', 50, 18 );
			con.write( 'o', 51, 18 );
			break;

		case 9:
			con.write( '|', 46, 21 );
			con.write( '|', 46, 22 );
			con.write( 'o', 46, 23 );
			break;

		case 10:
			con.write( '|', 48, 21 );
			con.write( '|', 48, 22 );
			con.write( 'o', 48, 23 );

			con.gotoXY( 44, 17 );
			std::cout << " {x_x}";
			break;
	}

	con.resetColour();
}