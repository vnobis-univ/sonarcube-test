

#include "Global.h"

#include <vector>

bool checkLetter( char &k, std::string &word, std::string &hWord );
void writeHangman( consoleColourGroup colour, int x, int y );
void finish( bool win, bool onePlayer, std::string word );
bool getDictionary( std::vector< std::string > &v );
bool getKeyPressed( char &k );
void drawHangman( int n );
void drawBox();

void onePlayer()
{
	writeHangman( LIGHT_RED, 0, 1 );

	drawBox();
	
	std::vector< std::string > dictionary;
	getDictionary( dictionary );

	int randomWord;

	do
	{
		randomWord = rand() % dictionary.size();
	
	}while( ( dictionary[ randomWord ].length() < 5 ) || ( dictionary[ randomWord ].length() > 9 ) );

	std::string hangmanWord = dictionary[ randomWord ];
	
	std::string hiddenWord( hangmanWord.length(), '-' );
	const int hiddenWordCenter = ( ( mWidth / 2 ) - ( hiddenWord.length() / 2 ) );

	std::string hiddenWordInfo = "Here is your hidden word to guess!";
	const int wordInfoCenter = ( ( mWidth / 2 ) - ( hiddenWordInfo.length() / 2 ) );

	bool gameOver = false;
	bool invalid = false;
	bool alreadyGuessed = false;
	
	int guessCount = 0;
	int wrongCount = 0;
	const int die = 11;

	const int totalGuessedLetters = 20;
	
	char guessedLetters[ totalGuessedLetters ] = { NULL };
	char key = ' ';

	int statusPosX = 40;

	const int xPos = 14;
	const int yPos = 31;

	do
	{
		con.write( hiddenWordInfo, wordInfoCenter, yPos );
		con.write( hiddenWord, hiddenWordCenter, yPos + 2 );


		con.write( "Letters guessed so far:", xPos, yPos + 5 );

		con.gotoXY( xPos, yPos + 6 );
		for( int i = 0; i < totalGuessedLetters; ++i )
		{
			std::cout << guessedLetters[ i ] << ' ';
		}

		while( ! getKeyPressed( key ) )
		{ /* do nothing */ }

		con.write( "                                   ", xPos, statusPosX );

		if( ( tolower( key ) > 96 ) && ( tolower( key ) < 123 ) )
		{
			for( int checkGuessedLetters = 0; checkGuessedLetters < guessCount; ++checkGuessedLetters )
			{
				if( guessedLetters[ checkGuessedLetters ] == tolower( key ) )
				{					
					alreadyGuessed = true;
					break;
				}
				else
					alreadyGuessed = false;
			}
			
			if( alreadyGuessed )
			{
				con.write( "You've already guessed this letter!", xPos, statusPosX );
				alreadyGuessed = false;
			}
			else
			{
				guessedLetters[ guessCount ] = key;
				++guessCount;

				if( ! checkLetter( key, hangmanWord, hiddenWord ) )
				{
					drawHangman( wrongCount );
					++wrongCount;
				}
			}
		
			if( invalid )
				invalid = false;
		}
		else
		{
			con.write( "Invalid input!", xPos, statusPosX );
			invalid = true;
			continue;
		}

		if( hangmanWord == hiddenWord )
		{
			con.clearScreen();
			finish( true, true, hangmanWord );
			gameOver = true;
		}

		if( wrongCount == die )
		{
			con.setColour( LIGHT_RED, BLACK );
			std::string hman = "You're the new hangman!";
			int centerHMan = ( ( mWidth / 2) - ( hman.length() / 2 ) );

			con.write( hman, centerHMan, 29 );
			con.resetColour();

			con.write( "Press a key to continue...", 14, yPos + 8 );

			con.wait();

			con.clearScreen();
			finish( false, true, hangmanWord );
			gameOver = true;
		}
	
	}while( ! gameOver );

	con.clearScreen();
}