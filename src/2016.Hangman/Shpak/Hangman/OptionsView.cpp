#include "OptionsView.h"
#include "MenuView.h"
#include <iostream>
#include <vector>
#include <string>
#include "Navigation.h"
#include "ConsoleManipulators.h"
#include "Printer.h"
#include "LanguageManipulator.h"
#include "GameLogic.h"

int OptionsView::numberOfEmptyLines = 7;

OptionsView::OptionsView():
	highlightedElement(HighlightedELement::language)
{}

void OptionsView::draw()
{
	clean();

	setCursoreAtPosition(0, whereLogoEnds + 3);

	Printer().printAtCenter(LanguageManipulator().getHowToDrawOptionsHeader());

	drawLanguage();

	drawDifficulty();

	drawColor();

	drawBack();
}

void OptionsView::drawLanguage()
{
	setCursoreAtPosition(0, whereLogoEnds + 1.5 * numberOfEmptyLines);

	std::vector<std::string> vec;

	LanguageManipulator().getHowToDrawOptionsLanguage(vec);

	if (highlightedElement == HighlightedELement::language)
		mainPrinter.printAtCenter(vec[0]);
	else
		Printer().printAtCenter(vec[0]);


	drawEmptyLines(1);

	int lengthOfStr = 0;

	for (size_t i = 1; i < 4; ++i)
	{
		lengthOfStr += vec[i].length();
	}

	Printer().makeLeftPadding(lengthOfStr);
	
	for (size_t i = 1; i < 4; ++i)
	{
		if ((int)LanguageManipulator().getGameLanguage() == (i - 1) / 2.0)
			mainPrinter << vec[i];
		else
			Printer() << vec[i];
	}
}

void OptionsView::drawDifficulty()
{
	setCursoreAtPosition(0, whereLogoEnds + 2.5 * numberOfEmptyLines);

	std::vector<std::string> vec;

	LanguageManipulator().getHowToDrawOptionsDifficulty(vec);
	
	if (highlightedElement == HighlightedELement::difficulty)
		mainPrinter.printAtCenter(vec[0]);
	else
		Printer().printAtCenter(vec[0]);

	drawEmptyLines(1);

	int lengthOfStr = 0;

	for (size_t i = 1; i < 6; ++i)
	{
		lengthOfStr += vec[i].length();
	}

	Printer().makeLeftPadding(lengthOfStr);

	for (size_t i = 1; i < 6; ++i)
	{
		if ((int)GameLogic().getGameDifficulty() == (i - 1) / 2.0)
			mainPrinter << vec[i];
		else
			Printer() << vec[i];
	}
}

void OptionsView::drawColor()
{
	setCursoreAtPosition(0, whereLogoEnds + 3.5 * numberOfEmptyLines);

	std::vector<std::string> vec;

	LanguageManipulator().getHowToDrawOptionsColorOption(vec);

	if (highlightedElement == HighlightedELement::color)
		mainPrinter.printAtCenter(vec[0]);
	else
		Printer().printAtCenter(vec[0]);

	drawEmptyLines(1);

	int lengthOfStr = 0;

	for (size_t i = 1; i < 6; ++i)
	{
		lengthOfStr += vec[i].length();
	}

	Printer().makeLeftPadding(lengthOfStr);

	for (size_t i = 1; i <= 5; ++i)
	{
		if (mainPrinter == Printer(Color::red, Color::black) && i == 1)
			mainPrinter << vec[i];

		else if (mainPrinter == Printer(Color::purple, Color::black) && i == 3)
			mainPrinter << vec[i];

		else if (mainPrinter == Printer(Color::aqua, Color::black) && i == 5)
			mainPrinter << vec[i];

		else
			Printer() << vec[i];
	}

}

void OptionsView::drawBack()
{
	setCursoreAtPosition(0, whereLogoEnds + 35);

	if (highlightedElement == HighlightedELement::back)
		mainPrinter.printAtCenter(LanguageManipulator().getHowToDrawBackButton());
	else
		Printer().printAtCenter(LanguageManipulator().getHowToDrawBackButton());
}

View* OptionsView::handle()
{
	while (true)
	{
		Button button;

		HighlightedELement oldHighligted = highlightedElement;

		// until one of possible buttons is not presed continue loop
		if (!getWhichButton(button))
			continue;

		switch (button)
		{
		case Button::UP: //key up
			if (highlightedElement == HighlightedELement::language) break;

			highlightedElement = (HighlightedELement)(int(highlightedElement) - 1);

			handleUpDownMove(oldHighligted, highlightedElement);
			break;

		case Button::DOWN: //key down
			if (highlightedElement == HighlightedELement::back) break;

			highlightedElement = (HighlightedELement)(int(highlightedElement) + 1);


			handleUpDownMove(oldHighligted, highlightedElement);
			break;

		case Button::LEFT: //key left
			handleRightLeftMove(highlightedElement, Button::LEFT);
			break;

		case Button::RIGHT: //key right
			handleRightLeftMove(highlightedElement, Button::RIGHT);
			break;

		case Button::ENTER: // key enter
			if (highlightedElement == HighlightedELement::back)
				return new MenuView;

			break;

		default:
			continue;
		}
	}
}


void OptionsView::handleUpDownMove(HighlightedELement oldHighlighted, HighlightedELement newHighlighted)
{
	if (oldHighlighted == HighlightedELement::language || newHighlighted == HighlightedELement::language)
		drawLanguage();

	if (oldHighlighted == HighlightedELement::difficulty || newHighlighted == HighlightedELement::difficulty)
		drawDifficulty();

	if (oldHighlighted == HighlightedELement::color || newHighlighted == HighlightedELement::color)
		drawColor();

	if (oldHighlighted == HighlightedELement::back || newHighlighted == HighlightedELement::back)
		drawBack();
	
}

void OptionsView::handleRightLeftMove(HighlightedELement current, Button button)
{
	// handle language

	if (current == HighlightedELement::language)
	{
		handleLanguage(current, button);

		draw();
	}

	// handle difficulty

	if (current == HighlightedELement::difficulty)
	{
		handleDifficulty(current, button);

		drawDifficulty();
	}

	// handle color

	if (current == HighlightedELement::color)
	{
		handleColor(current, button);

		View::drawLogo(whereLogoEnds - 6);
		draw();
	}
}

void OptionsView::handleDifficulty(HighlightedELement current, Button button)
{
	GameLogic::Difficulty difficulty = GameLogic().getGameDifficulty();

	if (button == Button::LEFT)
	{
		if (difficulty == GameLogic::Difficulty::easy)
			return;
		else
			GameLogic().setGameDifficulty(static_cast<GameLogic::Difficulty> ((int)(difficulty)-1));
	}
	else if (button == Button::RIGHT)
	{
		if (difficulty == GameLogic::Difficulty::hard)
			return;
		else
			GameLogic().setGameDifficulty(static_cast<GameLogic::Difficulty> ((int)(difficulty)+1));
	}
}

void OptionsView::handleLanguage(HighlightedELement current, Button button)
{
	Language language = LanguageManipulator().getGameLanguage();

	if (button == Button::LEFT)
	{
		if (language == Language::English)
			return;
		else
			LanguageManipulator().setGameLanguage(static_cast<Language> ((int)(language)-1));
	}
	else if (button == Button::RIGHT)
	{
		if (language == Language::Ukranian)
			return;
		else
			LanguageManipulator().setGameLanguage(static_cast<Language> ((int)(language)+1));
	}
}

void OptionsView::handleColor(HighlightedELement current, Button button)
{
	GameLogic::Difficulty difficulty = GameLogic().getGameDifficulty();

	if (button == Button::LEFT)
	{
		if (mainPrinter == Printer(Color::red, Color::black))
			return;

		else if (mainPrinter == Printer(Color::purple, Color::black))
			mainPrinter = Printer(Color::red, Color::black);

		else if (mainPrinter == Printer(Color::aqua, Color::black))
			mainPrinter = Printer(Color::purple, Color::black);

		else
			throw std::string("Problem in OptionsView::handleRightLeftMove");

	}
	else if (button == Button::RIGHT)
	{
		if (mainPrinter == Printer(Color::aqua, Color::black))
			return;

		else if (mainPrinter == Printer(Color::purple, Color::black))
			mainPrinter = Printer(Color::aqua, Color::black);

		else if (mainPrinter == Printer(Color::red, Color::black))
			mainPrinter = Printer(Color::purple, Color::black);

		else
			throw std::string("Problem in OptionsView::handleRightLeftMove");
	}
}