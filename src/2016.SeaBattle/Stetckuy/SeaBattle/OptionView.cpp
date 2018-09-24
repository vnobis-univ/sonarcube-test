#pragma once

#include <conio.h>

#include "OptionView.h"
#include "FieldView.h"
#include "StartView.h"

using namespace std;

OptionView::OptionView()
	:menuCurrent(0)
{
	windowLanguage = Language::ENGLISH;

	markUpText.push_back("Language:");
	markUpText.push_back("Game mode:");

	menuItems.push_back(MenuItem("English", CONSOLE_WIDTH / 5, CONSOLE_HEIGHT / 4));
	menuItems.push_back(MenuItem("Ukrainian", CONSOLE_WIDTH / 5 + CONSOLE_WIDTH / 2, CONSOLE_HEIGHT / 4));
	menuItems.push_back(MenuItem("Computer", CONSOLE_WIDTH / 5, 2 * CONSOLE_HEIGHT / 4));
	menuItems.push_back(MenuItem("Multiplayer", CONSOLE_WIDTH / 5 + CONSOLE_WIDTH / 2, 2 * CONSOLE_HEIGHT / 4));
	menuItems.push_back(MenuItem("Back to menu", CONSOLE_WIDTH / 6, CONSOLE_HEIGHT - 2));
	menuItems.push_back(MenuItem("Start game", 4 * CONSOLE_WIDTH / 6, CONSOLE_HEIGHT - 2));

	menuItems[0].chosen = true;
}

View* OptionView::handle() 
{ 
	bool finish = false;
	View* current = this;

	while (!finish)
	{
		switch (_getch())
		{
		case 224: // one of the arrows
			switch (_getch())
			{
			case 75: // left
				menuItems[menuCurrent].chosen = false;
				--menuCurrent;

				if (menuCurrent == -1) // allows to pass from top-left item to the bottom-right one
				{
					menuCurrent = 5;
				}

				menuItems[menuCurrent].chosen = true;

				drawMenu();
				break;
			case 77: //right
				menuItems[menuCurrent].chosen = false;

				++menuCurrent;

				if (menuCurrent == 6) // allows to pass from bottom-right item to the top-left one
				{
					menuCurrent = 0;
				}

				menuItems[menuCurrent].chosen = true;

				drawMenu();

				break;
			}
			break;
		case VK_RETURN: // Enter
			switch (menuCurrent)
			{
			case 0: // English
				options.language = Language::ENGLISH;
				draw();
				break;
			case 1: // Ukrainian
				options.language = Language::UKRAINIAN;
				draw();
				break;
			case 2: // Computer
				options.gameMode = Mode::COMPUTER;
				break;
			case 3: // Multiplayer
				options.gameMode = Mode::MULTIPLAYER;
				break;
			case 4: // Back to menu
				current = new StartView();
				finish = true;
				break;
			case 5: // Start game
				current = new FieldView();
				finish = true;
			}
			break;
		}
	}

	return current;
}

void OptionView::draw()
{
	clear();
	configure();

	drawBackground(0, 0, CONSOLE_WIDTH*FONT_WIDTH, CONSOLE_HEIGHT*FONT_HEIGHT, RGB(0, 100, 200));

	setCursorAt(CONSOLE_WIDTH / 2, CONSOLE_HEIGHT / 4 - 2);
	printAtCenter(markUpText[0], headline);

	setCursorAt(CONSOLE_WIDTH / 2, 2 * CONSOLE_HEIGHT / 4 - 2);
	printAtCenter(markUpText[1], headline);

	drawMenu();
}

void OptionView::drawMenu()
{
	for (size_t i = 0; i < menuItems.size(); ++i)
	{
		setCursorAt(menuItems[i].x, menuItems[i].y);

		if (menuItems[i].chosen)
		{
			menuActive.print(menuItems[i].text);
		}
		else
		{
			menuPassive.print(menuItems[i].text);
		}
	}
}