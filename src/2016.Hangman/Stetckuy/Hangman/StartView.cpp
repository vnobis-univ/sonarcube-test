#pragma once

#include <conio.h>
#include <string>
#include "StartView.h"
#include "OptionView.h"
#include "FieldView.h"
#include "HighScoreView.h"

using namespace std;

StartView::StartView() // creates menu items
	: menuCurrent(0)
{
	if (options.getLanguage() == Language::ENGLISH)
	{
		menu[0] = MenuItem("START GAME");
		menu[1] = MenuItem("OPTIONS");
		menu[2] = MenuItem("HIGH SCORES");
		menu[3] = MenuItem("EXIT");
	}
	else
	{
		menu[0] = MenuItem("ÏÎ×ÀÒÈ ÃÐÓ");
		menu[1] = MenuItem("ÎÏÖ²¯");
		menu[2] = MenuItem("ÐÅÊÎÐÄÈ");
		menu[3] = MenuItem("ÂÈÕ²Ä");
	}

	menu[0].chosen = true; 

	markUpText.push_back("WELCOME TO HANGMAN");
	markUpText.push_back("Guess all words and save your friend from gallows!");
}


void StartView::drawMenu() 
{
	string bufferLeft;
	string bufferRight;

	for (size_t i = 0; i < 4; ++i)
	{

		// fillers that make all menu strings of the same size
		bufferLeft = string((CONSOLE_WIDTH / 3 - menu[i].text.length()) / 2, ' ');
		bufferRight = string(((CONSOLE_WIDTH / 3 - menu[i].text.length()) / 2) + menu[i].text.length() % 2, ' ');

		setCursorAt(CONSOLE_WIDTH / 3, (CONSOLE_HEIGHT / 6)*(i + 1) + 5);

		if (menu[i].chosen == true)
		{
			menuActive.print(bufferLeft + menu[i].text + bufferRight);
		}
		else
		{
			menuPassive.print(bufferLeft + menu[i].text + bufferRight);
		}
	}
}

View* StartView::handle()
{
	bool finish = false;
	View* current = this;

	while (!finish)
	{
		switch (_getch())
		{
		case 224: // one of the arrows was pressed
			switch (_getch())
			{
			case 72: // menu up
				if (menuCurrent > 0)
				{
					menu[menuCurrent].chosen = false;
					--menuCurrent;
					menu[menuCurrent].chosen = true;

					drawMenu();
				}
				break;
			case 80: // menu down
				if (menuCurrent < 3)
				{
					menu[menuCurrent].chosen = false;
					++menuCurrent;
					menu[menuCurrent].chosen = true;

					drawMenu();
				}
				break;
			}
			break;
		case VK_RETURN: // Enter
			Action currentAct = Action(menuCurrent);

			switch (currentAct)
			{
			case Action::START:
				current = new FieldView();
				finish = true;
				break;
			case Action::OPTIONS:
				current = new OptionView();
				finish = true;
				break;
			case Action::HIGH_SCORES:
				current = new HighScoreView();
				finish = true;
				break;
			case Action::EXIT:
				current = nullptr;
				finish = true;
			}
			break;
		}
	}

	return current;
}

void StartView::draw()
{
	clear();
	configure();

	setCursorAt(CONSOLE_WIDTH / 3, 0);

	headline.print(markUpText[0]);

	setCursorAt(3, 3);

	techData.print(markUpText[1]);

	drawMenu();
}
