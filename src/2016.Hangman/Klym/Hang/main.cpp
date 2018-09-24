

#include "Global.h"

#include <time.h>

void exitScreen();
void welcome();
int menu();

void twoPlayer( std::string hangmanWord );
std::string twoPlayerPrep();
void onePlayer();
void help();

int main()
{
	con.cursorVisibility( false );

	welcome();

	int choice;

	srand( unsigned( time( NULL ) ) );

	do
	{
		choice = menu();

		switch( choice )
		{
			case 1:
				con.clearScreen();
				onePlayer();
				break;

			case 2:
				{
					con.clearScreen();
					std::string input = twoPlayerPrep();
					twoPlayer( input );
					break;
				}

			case 3:
				con.clearScreen();
				help();
				break;
		}

	}while( choice != 4 );

	exitScreen();

	return 0;
}