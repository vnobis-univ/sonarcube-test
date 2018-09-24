#include "ResultView.h"
#include "MenuView.h"
#include "Navigation.h"
#include "FilesManipulator.h"
#include "ConsoleManipulators.h"
#include "LanguageManipulator.h"
#include <vector>
#include <string>
#include <conio.h>


ResultView::ResultView(int score, int letters, std::vector<char> vec):
	newScore(score),
	newNumberLetters(letters),
	possibleLetters(vec)
{}

void ResultView::draw()
{
	clean();

	std::vector<std::string> names;
	std::vector<std::pair<int, int>> scores;

	FilesManipulator().getHighscores(names, scores);

	int indexInVec = newHighscoreHandler(scores);

	if (indexInVec == -1)
	{
		drawNotNewHighscoresCase();
	}
	else
	{
		drawNewHighscoresCase();

		names[indexInVec] = getName();

		FilesManipulator().writeHighscores(names, scores);
	}

	setCursoreAtPosition(0, whereLogoEnds + 30);

	mainPrinter.printAtCenter(LanguageManipulator().getHowToDrawBackButton());
}

void ResultView::drawNotNewHighscoresCase()
{
	setCursoreAtPosition(0, whereLogoEnds + 5);

	std::vector<std::string> vec;

	LanguageManipulator().getStandartResultMessage(vec);

	mainPrinter.printAtCenter(vec[0]);

	drawEmptyLines(1);
}

void ResultView::drawNewHighscoresCase()
{
	setCursoreAtPosition(0, whereLogoEnds + 5);

	std::vector<std::string> vec;

	LanguageManipulator().getNewResultMessage(vec);

	Printer().printAtCenter(vec[0]);

	setCursoreAtPosition(0, whereLogoEnds + 10);

	mainPrinter.printAtCenter(vec[1]);

	setCursoreAtPosition(0, whereLogoEnds + 18);

	Printer().printAtCenter(LanguageManipulator().getHowToDrawHint());

	setCursoreAtPosition(0, whereLogoEnds + 11);
}

int ResultView::newHighscoreHandler(std::vector<std::pair<int, int>>& scores)
{
	for (int i = scores.size() - 1; i >= 0; --i)
	{
		if (newScore > scores[i].first || (newScore == scores[i].first && newNumberLetters >= scores[i].second))
		{
			scores[i] = std::pair<int, int>(newScore, newNumberLetters);

			return i; // return index in vector in order to save name later
		}
	}

	return -1; // if highscore didn't achieved
}

std::string ResultView::getName()
{
	std::string newName = "";

	size_t counter = 0;
	char ch = 0;

	while (counter < 13 && ch != 13)
	{
		ch = _getch();
	
		if (checkIfArrowPressed()) //working with console methods so execute long(realisation in consoleManipulators.cpp)
		{
			// if arrowKey is pressed than need to continue
			// need to make this check because arrow has 2 codes (224 and other) and it make some bugs
			_getch();
			continue;
		}

		if (ch == 8 && counter > 0)
		{
			newName.pop_back();
			--counter;

			drawEnteringName(newName);

			continue;
		}
		else if (ch != 8 && ch != 13 && counter != 12)
		{
			char pressedLetter = LanguageManipulator().getWhichLetterIsPressed(ch);

			for (size_t i = 0; i < possibleLetters.size(); ++i)
			{
				if (possibleLetters[i] == pressedLetter || possibleLetters[i] == pressedLetter - 32)
				{
					newName += pressedLetter;
					drawEnteringName(newName);
					++counter;
				}

			}
		}
	}

	if (newName == "")
		return "no_name";
	else
		return newName;
}

void ResultView::drawEnteringName(std::string str)
{
	COORD current;

	getCursorPosition(current);

	std::string space(10, ' ');

	Printer().printAtCenter(space + str + space);

	setCursoreAtPosition(current);
}

bool ResultView::varifyButtonCodeInput(char letter)
{
	if (letter == 224 || letter == 0)
	{
		 _getch(); 
		return false;
	}

	if (letter == '\b') // if backspace
		return true;

	for (size_t i = 0; i < possibleLetters.size(); ++i)
	{
		if (letter == possibleLetters[i] || letter == possibleLetters[i] + 32)
		{
			// if one of possible letters(both small or big) is pressed
			return true;
		}
	}

	return false;
}

View* ResultView::handle()
{
	while (true)
	{
		Button button;

		// until one of possible buttons is not presed continue loop
		if (!getWhichButton(button))
			continue;

		switch (button)
		{
		case Button::ENTER: // key enter
			return new MenuView();
			break;

		default:
			continue;
		}

	}
}

