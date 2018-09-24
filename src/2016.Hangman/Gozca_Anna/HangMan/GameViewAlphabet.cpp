#include "GameView.h"

bool GameView::isSelected(int i)
{
	return i == numOfSelectedLetter;
}

LetterStates GameView::getState(int i)
{
	return letters[i];
}

void GameView::drawSelectedLetter(int i, bool isSelect, LetterStates state)
{
	Printer printer;
	Printer defaultLetter(Color::BLUE, isSelect ? Color::LIGHT_WHITE : Color::LIGHT_YELLOW);
	Printer inWordLetter(Color::LIGHT_AQUA, isSelect ? Color::LIGHT_WHITE : Color::LIGHT_YELLOW);
	Printer notInWordLetter(Color::LIGHT_GREEN, isSelect ? Color::LIGHT_WHITE : Color::LIGHT_YELLOW);

	switch (state)
	{
	case LetterStates::DEFAULT:
	{
		printer = defaultLetter;
	}
	break;
	case LetterStates::INWORD:
	{
		printer = inWordLetter;
	}
	break;
	case LetterStates::NOTINWORD:
	{
		printer = notInWordLetter;
	}
	}
	if (i < 13)
	{
		moveCursorTo(2 + 3 * i, 22);
	}
	else
	{
		moveCursorTo((3 * i) - 37, 23);
	}
	printer << " " << allLetters[i] << " ";
}

void GameView::printAllLetters()
{
	for (size_t i = 0; i < 26; i++)
	{
		LetterStates _state = getState(i);
		bool isSelect = isSelected(i);
		drawSelectedLetter(i, isSelect, _state);
	}
}
