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
	windowLanguage = Language::ENGLISH;

	markUpText.push_back("WELCOME TO SEA BATTLE!");
	markUpText.push_back("Hit all enemies and save your country from marine invasion!");
	markUpText.push_back("Change ship direction - Space");
	markUpText.push_back("Quit game - ESC");

	menuItems.push_back(MenuItem("START GAME", CONSOLE_WIDTH / 3, CONSOLE_HEIGHT / 6 + 5));
	menuItems.push_back(MenuItem("OPTIONS", CONSOLE_WIDTH / 3, 2 * (CONSOLE_HEIGHT / 6) + 5));
	menuItems.push_back(MenuItem("HIGH SCORES", CONSOLE_WIDTH / 3, 3 * (CONSOLE_HEIGHT / 6) + 5));
	menuItems.push_back(MenuItem("EXIT", CONSOLE_WIDTH / 3, 4 * (CONSOLE_HEIGHT / 6) + 5));

	menuItems[0].chosen = true;
}


void StartView::drawMenu() 
{
	string bufferLeft;
	string bufferRight;

	for (size_t i = 0; i < 4; ++i)
	{
		// fillers that make all menu strings of the same size
		bufferLeft = string((CONSOLE_WIDTH / 3 - menuItems[i].text.length()) / 2, ' ');
		bufferRight = string(((CONSOLE_WIDTH / 3 - menuItems[i].text.length()) / 2) + menuItems[i].text.length() % 2, ' ');

		setCursorAt(menuItems[i].x, menuItems[i].y);

		if (menuItems[i].chosen == true)
		{
			menuActive.print(bufferLeft + menuItems[i].text + bufferRight);
		}
		else
		{
			menuPassive.print(bufferLeft + menuItems[i].text + bufferRight);
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
					menuItems[menuCurrent].chosen = false;
					--menuCurrent;
					menuItems[menuCurrent].chosen = true;

					drawMenu();
				}
				break;
			case 80: // menu down
				if (menuCurrent < 3)
				{
					menuItems[menuCurrent].chosen = false;
					++menuCurrent;
					menuItems[menuCurrent].chosen = true;

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
	printAtCenter(markUpText[0], headline);

	setCursorAt(3, 3);
	printAtCenter(markUpText[1], stats);

	setCursorAt(0, 5);
	printAtCenter(markUpText[2], techData);

	setCursorAt(0, 6);
	printAtCenter(markUpText[3], techData);

	drawMenu();
}
