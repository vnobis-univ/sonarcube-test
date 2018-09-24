#include "MenuView.h"
#include <iostream>
#include "Utils.h"
#include "Levels.h"
#include "HighScore.h"
#include "LangOption.h"

void MenuView::printMenu()
{
	system("cls");

	// border control
	if (selected == 4)
	{
		selected = 0;
	}
	if (selected == -1)
	{
		selected = 3;
	}
	
	if (View::lang == Language::ENG)
	{
		purleOnBlack.printOnCenter(3, "  H A N G M A N  ");

		lightPurpleOnBlack.printOnCenter(6, " * MENU * ");

		for (int i = 0; i < 4; ++i)
		{
			selected != i ? greenOnBlack.printOnCenter(3 * i + 10, option[i]) : lightAquaOnBlack.printOnCenter(3 * i + 10, "> " + option[i] + " <");

		}
	}
	else
	{
		
		purleOnBlack.printOnCenter(3, "  ุ ศ ม ล อ ศ ึ ฿  ");

		lightPurpleOnBlack.printOnCenter(6, " * ฬลอÞ * ");

		for (int i = 0; i < 4; ++i)
		{
			selected != i ? greenOnBlack.printOnCenter(3 * i + 10, ukr_option[i]) : lightAquaOnBlack.printOnCenter(3 * i + 10, "> " + ukr_option[i] + " <");

		}
	}
	
	
}


MenuView::MenuView(Language m_lang):
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
				nextView = new Levels(lang);
			}
			else if (selected == 1)
			{
				nextView = new HighScore(lang);
			}
			else if(selected == 2)
			{
				nextView = new LangOption(lang);
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