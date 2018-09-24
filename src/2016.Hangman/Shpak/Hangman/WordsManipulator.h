#pragma once
#include <list>
#include <string>
#include "View.h"

class WordsManipulator
{
	std::list<std::string> wordsContainer;
	std::string wordToGuess;

	unsigned numberOfGuessedLetters;
	std::string guessedChars;

public:
	WordsManipulator();

	void chooseWord();

	void drawHowMuchGuessed(bool = false);

	bool isWholeWordGuessed() const;

	bool doesHaveWords() const;

	bool tryGuess(char);

	int getNumberOfGuessedLetters() const;
};