#include <iostream>
#include <string>
#include "HighscoresView.h"
#include "ConsoleManipulators.h"
#include "FilesManipulator.h"
#include "LanguageManipulator.h"
#include "MenuView.h"
#include "Navigation.h"
#include "Printer.h"

HighscoresView::HighscoresView():
	choosenLanguage(LanguageManipulator().getGameLanguage())
{}

void HighscoresView::draw()
{
	clean();

	setCursoreAtPosition(0, whereLogoEnds + 3);

	Printer().printAtCenter(LanguageManipulator().getHowToDrawHighscoresHeader());

	drawMainRow();

	drawLines();

	drawDifficultyNames();

	drawResults();

	drawHighscoresFooter();
}

void HighscoresView::drawMainRow(Language languageToDraw)
{
	setCursoreAtPosition(0, whereLogoEnds + 6);

	std::vector<std::string> vec;

	std::string space(20, ' ');

	LanguageManipulator().getHowToDrawTableMainRow(vec);

	mainPrinter.makeLeftPadding(vec[0].length() + vec[1].length() + space.length());

	for (size_t i = 0; i < 2; ++i) // 2 is number of languages
	{
		if (i == int(languageToDraw))
		{
			mainPrinter << " " << vec[i] << space;
		}
		else
		{
			Printer() << " " << vec[i] << space;
		}
	}
}

void HighscoresView::drawDifficultyNames()
{
	std::vector<std::string > vec;

	LanguageManipulator().getLevelsNames(vec);

	COORD current = { 0, whereLogoEnds + 11 };

	setCursoreAtPosition(current);

	for (size_t i = 0; i < 3; ++i)
	{
		setCursoreAtPosition(getConsoleWidth() / 3 * i + 11, current.Y);

		std::cout << vec[i];
	}
}

void HighscoresView::drawLines()
{
	COORD current = { 0, whereLogoEnds + 9 };

	setCursoreAtPosition(current);

	std::string horizontalLine(70, '.');

	Printer().printAtCenter(horizontalLine);

	for (size_t k = 1; k <= 2; ++k)
		for (size_t i = 0; i < 20; i++)
		{
			setCursoreAtPosition(getConsoleWidth() / 3 * k, current.Y + i);

			Printer() << '.';
		}
}

void HighscoresView::drawHighscoresFooter()
{
	setCursoreAtPosition(0, whereLogoEnds + 35);

	mainPrinter.printAtCenter(LanguageManipulator().getHowToDrawBackButton());
}

void HighscoresView::clearTable()
{
	COORD current = { 0, (short)whereLogoEnds + 14 };

	setCursoreAtPosition(current);

	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 10; ++j)
		{
			std::string spaces(3 + getConsoleWidth() / 3 * (i + 1) - (3 + getConsoleWidth() / 3 * i) - 5, ' ');

			setCursoreAtPosition(3 + getConsoleWidth() / 3 * i, current.Y + (j * 2));

			std::cout << spaces;
		}
	}
}

void HighscoresView::drawResults(Language languageToDraw)
{

	clearTable();
	
	Language currentLanguage = LanguageManipulator().getGameLanguage();
	LanguageManipulator().setGameLanguage(languageToDraw);

	COORD current = { 0, (short)whereLogoEnds + 14};

	setCursoreAtPosition(current);

	for (size_t i = 0; i < 3; ++i)
	{
		std::vector<std::string> names;
		std::vector<std::pair<int, int>> scores;

		FilesManipulator().getHighscores(names, scores, static_cast<GameLogic::Difficulty>(i));

		for (size_t j = 0; j < names.size(); ++j)
		{
			setCursoreAtPosition(3 + getConsoleWidth() / 3 * i, current.Y + (j * 2));

			Printer() << names[j] << " ";

			std::string strToPrint = std::to_string(scores[j].first) + "  " + std::to_string(scores[j].second);

			setCursoreAtPosition(getConsoleWidth() / 3 * (i + 1) - 2 - strToPrint.length(), current.Y + (j * 2));
			std::cout << strToPrint;
		}
	}

	LanguageManipulator().setGameLanguage(currentLanguage);
}

View* HighscoresView::handle()
{
	while (true)
	{
		Button button;

		if (!getWhichButton(button))
			continue;

		
		switch (button)
		{
		case Button::LEFT: //key left
			handleRightLeftMove(Button::LEFT);
			break;

		case Button::RIGHT: //key right
			handleRightLeftMove(Button::RIGHT);
			break;

		case Button::ENTER: //key right
			return new MenuView();
			break;

		default:
			continue;
		}
	}
}

void HighscoresView::handleRightLeftMove(Button button)
{
	if (button == Button::LEFT)
	{
		if (choosenLanguage == Language::English) return;

		choosenLanguage = static_cast<Language> (int(choosenLanguage) - 1);

		drawMainRow(choosenLanguage);
		drawResults(choosenLanguage);
	}

	else if (button == Button::RIGHT)
	{
		if (choosenLanguage == Language::Ukranian) return;

		choosenLanguage = static_cast<Language> (int(choosenLanguage) + 1);
		
		drawMainRow(choosenLanguage);
		drawResults(choosenLanguage);
	}
}
