#include "WordsManipulator.h"
#include "FilesManipulator.h"
#include "LanguageManipulator.h"
#include "ConsoleManipulators.h"
#include "HangmanPicture.h"
#include "GameLogic.h"
#include "View.h"
#include "Printer.h"
#include <stdlib.h>
#include <time.h>
#include <list>

WordsManipulator::WordsManipulator():
	guessedChars("_"),
	numberOfGuessedLetters(0)
{
	try
	{
		FilesManipulator().getWords(wordsContainer);
	}
	catch (std::string)
	{
		if (wordsContainer.size() == 0) throw;
	}
	LanguageManipulator().varifyLetters(wordsContainer);

	LanguageManipulator().makeAllLettersBig(wordsContainer);
}

bool WordsManipulator::doesHaveWords() const
{
	return !wordsContainer.empty();
}

int WordsManipulator::getNumberOfGuessedLetters() const
{
	return numberOfGuessedLetters;
}

void WordsManipulator::chooseWord()
{
	if (wordsContainer.size() == 0) throw std::string("Empty words container");

	srand(time(NULL));

	size_t index = rand() % wordsContainer.size();

	std::list<std::string>::iterator it = wordsContainer.begin();

	for (size_t i = 0; i != index; ++i)
	{
		++it;
	}

	wordToGuess = *it;

	wordsContainer.erase(it);

	// by default none chars are guessed
	guessedChars = std::string(wordToGuess.length(), '_');

	numberOfGuessedLetters = 0;
}

void WordsManipulator::drawHowMuchGuessed(bool isEnd)
{
	setCursoreAtPosition(0, HangmanPicture().getWhereFrameEnds() + 2);

	std::string strToDraw = "";
	std::string emptySpaces(10, ' ');


	if (!isEnd)
	{
		for (size_t i = 0; i < guessedChars.length(); ++i)
		{
			strToDraw += guessedChars[i];

			if (i != guessedChars.length() - 1)
				strToDraw += " ";
		}

		Printer().printAtCenter(emptySpaces + strToDraw + emptySpaces);
	}
	else
	{
		for (size_t i = 0; i < guessedChars.length(); ++i)
		{
			strToDraw += wordToGuess[i];

			if (i != guessedChars.length() - 1)
				strToDraw += " ";
		}


		Printer(Color::red, Color::black).printAtCenter(emptySpaces + strToDraw + emptySpaces);
	}
}

bool WordsManipulator::tryGuess(char letter)
{
	bool isGuess = false;


	for (size_t i = 0; i < wordToGuess.length(); ++i)
	{
		if (letter == wordToGuess[i])
		{
			isGuess = true;
			guessedChars[i] = letter;
		}
	}

	if (isGuess)
		++numberOfGuessedLetters;



	return isGuess;
}

bool WordsManipulator::isWholeWordGuessed() const
{
	for (size_t i = 0; i < wordToGuess.length(); ++i)
	{
		if (guessedChars[i] != wordToGuess[i])
		{
			return false;
		}
	}

	return true;
}