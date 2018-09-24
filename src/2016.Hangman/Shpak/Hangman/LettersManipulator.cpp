#include "LettersManipulator.h"
#include "LanguageManipulator.h"
#include "HangmanPicture.h"
#include "Navigation.h"
#include "ConsoleManipulators.h"
#include "Printer.h"
#include "LanguageManipulator.h"
#include <vector>
#include <iostream>

int LettersManipulator::spaceBetweenChars = 3;
int LettersManipulator::spaceBetweenRows = 3;

LettersManipulator::LettersManipulator():
	hoverLetter(0)
{
	LanguageManipulator().getAlphabet(letters);
	numberOfLetters = letters.size();

	for (size_t i = 0; i < numberOfLetters; ++i)
	{
		states.push_back(LetterState::default);
	}
}

char LettersManipulator::getWhichSelected() const
{
	return letters[hoverLetter];
}

bool LettersManipulator::checkIfUsed()
{
	if (states[hoverLetter] != LetterState::default)
		return false;
	else
		return true;
}

void LettersManipulator::setNewState(LetterState newState)
{
	states[hoverLetter] = newState;

	drawOneLetter(hoverLetter);
}

void LettersManipulator::renewStates()
{
	for (size_t i = 0; i < states.size(); ++i)
	{
		states[i] = LetterState::default;
	}

	drawLetters();
}

std::vector<char> LettersManipulator::getLetters() const
{
	return letters;
}

void LettersManipulator::drawLetters()
{	
	*this = LettersManipulator(); // renewing element

	setCursoreAtPosition(0, HangmanPicture().getWhereFrameEnds() + 6);

	Printer().makeLeftPadding(numberOfLetters / 2 + spaceBetweenChars * (numberOfLetters / 2 - 1) - 3);

	getCursorPosition(whereLettersStarts);

	for (size_t i = 0; i < numberOfLetters; ++i)
	{
		drawOneLetter(i);
	}
}

void LettersManipulator::drawOneLetter(size_t index) const
{
	// getting where to draw letter
	COORD whereToDraw;

	whereToDraw.X = whereLettersStarts.X + (index % (numberOfLetters / 2)) * (spaceBetweenChars + 1);
	whereToDraw.Y = whereLettersStarts.Y + (index / (numberOfLetters / 2)) * spaceBetweenRows;
		
	setCursoreAtPosition(whereToDraw);


	// setting background based on whether hover or not
	Color backGround;

	if (hoverLetter == index)
		backGround = Color::purple;
	else
		backGround = Color::black;


	// making background around letter
	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
			if (i != 0 || j != 0)
			{
				setCursoreAtPosition(whereToDraw.X + i, whereToDraw.Y + j);
				Printer(Color::white, backGround) << " ";
			}

	setCursoreAtPosition(whereToDraw);

	// printing letter
	switch (states[index])
	{
	case LetterState::default:
		Printer(Color::white, backGround) << letters[index];
		break;

	case LetterState::wrong:
		Printer(Color::red, backGround) << letters[index];
		break;

	case LetterState::right:
		Printer(Color::green, backGround) << letters[index];
		break;
	}
}

void LettersManipulator::handleMove(Button pressedButton)
{
	int oldHover = hoverLetter;
	
	switch (pressedButton)
	{
	case Button::UP:
		if (hoverLetter / (numberOfLetters / 2) == 0) break; //if top row

		hoverLetter -= numberOfLetters / 2;
		break;

	case Button::DOWN:
		if (hoverLetter / (numberOfLetters / 2) == 1) break; //if bottom row

		hoverLetter += numberOfLetters / 2;
		break;

	case Button::LEFT:
		if (hoverLetter == 0 || hoverLetter == numberOfLetters / 2) break; //if left column

		hoverLetter -= 1;
		break;

	case Button::RIGHT:
		if (hoverLetter == numberOfLetters / 2 - 1 || hoverLetter == numberOfLetters - 1) break; //if right column

		hoverLetter += 1;
		break;
	}

	if (oldHover != hoverLetter)
	{
		drawOneLetter(oldHover);
		drawOneLetter(hoverLetter);
	}
}


