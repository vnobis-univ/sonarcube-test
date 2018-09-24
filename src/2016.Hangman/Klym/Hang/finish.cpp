

#include "Global.h"

#include <string>

void writeHangman( consoleColourGroup colour, int x, int y );

void finish( bool win, bool onePlayer, std::string word )
{
	writeHangman( LIGHT_RED, 0, 1 );

	const int xPos = 14;
	const int yPos = 10;

	if( onePlayer )
	{
		if( win )
		{
			con.write( "Congratulations! You guessed the word!", xPos, yPos );
		}
		else
		{
			con.write( "Unlucky! You failed to guess the word.", xPos, yPos );
		}

		std::string writeWord = "The word was: " + word;
		
		con.write( writeWord, xPos, yPos + 2 );	
	}
	else
	{
		bool isPhrase = false;

		for( unsigned int i = 0; i < word.length(); ++i )
		{
			if( word[ i ] == ' ' )
			{
				isPhrase = true;
				break;
			}
		}

		if( win )
		{
			if( isPhrase )
			{
				con.write( "Congratulations! You guessed the phrase!", xPos, yPos );
				std::string writeWord = "The phrase was: " + word;

				con.write( writeWord, xPos, yPos + 2 );
			}
			else
			{
				con.write( "Congratulations! You guessed the word!", xPos, yPos );
				std::string writeWord = "The word was: " + word;

				con.write( writeWord, xPos, yPos + 2 );
			}
		}
		else
		{
			if( isPhrase )
			{
				con.write( "Unlucky! You failed to guess the phrase.", xPos, yPos );
				std::string writeWord = "The phrase was: " + word;

				con.write( writeWord, xPos, yPos + 2 );
			}
			else
			{
				con.write( "Unlucky! You failed to guess the word.", xPos, yPos );
				std::string writeWord = "The word was: " + word;

				con.write( writeWord, xPos, yPos + 2 );
			}
		}
	}

	con.write( "Press any key to continue...", xPos, yPos + 4 );
	con.wait();
}