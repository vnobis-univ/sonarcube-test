#include "MenuView.h"
#include <iostream>
#include "Utils.h"
#include "LanguageSelection.h"
#include "GameView.h"

void MenuView::printMenu()
{
	system("cls");

	// border control
	if (selected == 3)
	{
		selected = 0;
	}

	if (selected == -1)
	{
		selected = 2;
	}

	if (View::lang == Language::ENG)
	{
		blueOnBlack.printOnCenter(3, "  SEA BATTLE  ");

		lightBlueOnBlack.printOnCenter(6, "  MENU  ");

		for (int i = 0; i < 3; ++i)
		{
			selected != i ? greenOnBlack.printOnCenter(3 * i + 10, option[i]) : lightAquaOnBlack.printOnCenter(3 * i + 10, "~ " + option[i] + " ~");
		}
	}
	else
	{
		blueOnBlack.printOnCenter(3, "  ÌÎÐÑÜÊÈÉ Á²É  ");

		lightBlueOnBlack.printOnCenter(6, "  ÌÅÍÞ  ");

		for (int i = 0; i < 3; ++i)
		{
			selected != i ? greenOnBlack.printOnCenter(3 * i + 10, ukr_option[i]) : lightAquaOnBlack.printOnCenter(3 * i + 10, "~ " + ukr_option[i] + " ~");
		}
	}
}

MenuView::MenuView(Language m_lang) :
	View(m_lang),
	selected(0)
{};


void MenuView::draw()
{
	printMenu();
}


View * MenuView::handle()
{
	View* nextView = this;
	bool userChoose = false;

	while (!userChoose)
	{
		switch (_getwch())
		{
		case 72:
			selected--;
			printMenu();
			break;
		case 80:
			selected++;
			printMenu();
			break;
		case 13:
			userChoose = true;
			if (selected == 0)
			{
				nextView = new GameView(lang);
			}
			else if (selected == 1)
			{
				nextView = new LanguageSelection(lang);
			}
			else
			{
				exit(0);
			}
			break;
		}
	}

	return nextView;
};
