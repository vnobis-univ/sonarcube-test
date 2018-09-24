#include "Levels.h"
#include <iostream>
#include "Utils.h"
#include "MenuView.h"
#include "Field.h"

void Levels::printLevels()
{

	// border control
	if (selected == 3)
	{
		selected = 0;
	}
	if (selected == -1)
	{
		selected = 2;
	}
	system("cls");


	if (View::lang == Language::ENG)
	{
		lightPurpleOnBlack.printOnCenter(6, " * PLEASE, SELECT LEVEL * ");
		for (int i = 0; i < 3; ++i)
		{
			moveCursorTo(15 + i * 20, 10);
			selected != i ?
				greenOnBlack.print(levels[i]) : lightAquaOnBlack.print("> " + levels[i] + " <");

		}

		lightPurpleOnBlack.printOnCenter(20, " * PRESS ESC To Return To MENU * ");
	}
	else 
	{
		lightPurpleOnBlack.printOnCenter(6, " * ÁÓÄÜ ËÀÑÊÀ, ÎÁÅÐ²ÒÜ Ð²ÂÅÍÜ * ");
		for (int i = 0; i < 3; ++i)
		{
			moveCursorTo(15 + i * 20, 10);
			selected != i ?
				greenOnBlack.print(ukr_levels[i]) : lightAquaOnBlack.print("> " +	ukr_levels[i] + " <");

		}

		lightPurpleOnBlack.printOnCenter(20, " * ÍÀÒÈÑÍ²ÒÜ ESC ÄËß ÏÎÂÅÐÍÅÍÍß Â ÌÅÍÞ * ");
	}
	
}

Levels::Levels(Language m_lang ):
	View(m_lang),
	selected(0)
	{}
void Levels::draw()
{
	printLevels();
}
View * Levels::handle()
{
	View* nextView = this;
	bool userChoose = false;

	while (!userChoose)
	{
		switch (_getwch())
		{
		case 75:  // move to the left
			selected--;
			printLevels();
			break;
		case 77:   // move to the right
			selected++;
			printLevels();
			break;
		case 27:   //ESC to return to menu
			userChoose = true;
			nextView = new MenuView(lang);
			break;
		case 13:  // to chose the level
			userChoose = true;
			if (selected == 0)
			{
				
				nextView = new Field((LevelState)selected, lang);
			}
			else if (selected == 1)
			{
				nextView = new Field((LevelState)selected, lang);
			}
			else
			{
				nextView = new Field((LevelState)selected, lang);
			}
			break;
		}
	}

	return nextView;
};
