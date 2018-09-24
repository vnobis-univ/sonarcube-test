#pragma once
#include "LettersManipulator.h"
#include "WordsManipulator.h" 
#include "HangmanPicture.h"

class Game
{
protected:
	static LettersManipulator lettersManipulator;
	static WordsManipulator wordsManipulator;
	static HangmanPicture hangmanPicture;

public:
	Game();
};

