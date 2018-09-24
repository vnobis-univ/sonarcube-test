#include "Game.h"


LettersManipulator Game::lettersManipulator = LettersManipulator();
HangmanPicture Game::hangmanPicture = HangmanPicture();
WordsManipulator Game::wordsManipulator = WordsManipulator();

Game::Game()
{
	// constructor renew static elements
	lettersManipulator = LettersManipulator();
	hangmanPicture = HangmanPicture();
	wordsManipulator = WordsManipulator();
}
