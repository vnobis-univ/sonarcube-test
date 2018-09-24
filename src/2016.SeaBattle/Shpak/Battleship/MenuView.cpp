#include "MenuView.h"
#include "OptionsView.h"
#include "ConsoleManipulators.h"
#include "LanguageManipulator.h"
#include "ChooseGameView.h"
#include "HighscoresView.h"
#include "Navigation.h"
#include "GameView.h"
#include "Printer.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

std::string MenuView::howToShowSelected[2] = { "*  ", "  *" };

int MenuView::whereMenuStarts = whereLogoEnds + 7;

int MenuView::numberOfEmptyLines = 4;


MenuView::MenuView():
	menuOptionsSize(4),
	selectedOption(MenuOptions::start)
{}

void MenuView::draw()
{
	system("cls");
	
	drawLogo(whereLogoEnds - 6);

	drawMenu();
}

void MenuView::drawMenu()
{
	LanguageManipulator().getHowToDrawMenuOptions(vecOfOptions, menuOptionsSize);

	setCursoreAtPosition(0, whereMenuStarts);
	
	for (size_t i = 0; i < menuOptionsSize; ++i)
	{
		if (i == 0)
		{
			// making by default first selected. Showing Move is handled in handleMove function

			mainPrinter.printAtCenter(howToShowSelected[0] + vecOfOptions[i] + howToShowSelected[1]);
		}
		else
		{
			Printer().printAtCenter(vecOfOptions[i]);
		}

		drawEmptyLines(numberOfEmptyLines);
	}
}

View* MenuView::handle()
{
	while (true)
	{
		Button button;
		MenuOptions newSelectedOption = selectedOption;

		// until one of possible buttons is not presed continue loop
		if (!getWhichButton(button))
			continue;

		switch (button)
		{
		case Button::UP: //key up
			if (selectedOption == MenuOptions::start) break;

			newSelectedOption = (MenuOptions)(int(selectedOption) - 1);
			break;

		case Button::DOWN: //key down
			if (selectedOption == MenuOptions::exit) break;
			newSelectedOption = (MenuOptions)(int(selectedOption) + 1);
			break;

		case Button::ENTER: // key enter
			return getNextView();
			break;

		default:
			continue;
		}

		if (newSelectedOption != selectedOption)
		{
			handleMove(selectedOption, newSelectedOption);
			selectedOption = newSelectedOption;
		}
	}
}

void MenuView::handleMove(MenuOptions oldOption, MenuOptions newOption)
{
	std::string emptySpace(howToShowSelected[0].length(), ' ');
	
	// rewriting option that isn't now selected

		//setting cursor in needed line
	setCursoreAtPosition(0, whereMenuStarts + (int)oldOption * (numberOfEmptyLines + 1));

		//changing line (removing symbols for selected option)
	Printer().printAtCenter(emptySpace + vecOfOptions[(int)oldOption] + emptySpace);



	// rewriting option that is now selected

		//setting cursor in needed line
	setCursoreAtPosition(0, whereMenuStarts + (int)newOption * (numberOfEmptyLines + 1));

		//changing line (adding symbols for selected option)
	mainPrinter.printAtCenter(howToShowSelected[0] + vecOfOptions[(int)newOption] + howToShowSelected[1]);
}

View* MenuView::getNextView() const
{
	 switch (selectedOption)
	 {
		 case MenuOptions::start:
			 return new ChooseGameView();

		 case MenuOptions::options:
			 return new OptionsView();

		 case MenuOptions::highscores:
			 return new HighscoresView();

		 case MenuOptions::exit:
			  return nullptr;
	 }
}