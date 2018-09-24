#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

#include "ConsoleCustomize.h"
#include "SysUtils.h"
#include "Printer.h"

using namespace std;

StartView startView;

void StartView::displayMenu()
{
	cursor.Y = CONSOLE_HEIGHT/3;

	printAtCenter("\tWELCOME TO GAME \"TIC-TAC-TOE\"\n\n", headline);

	Printer checked(Color::YELLOW, Color::RED);
	Printer notChecked(Color::YELLOW, Color::BROWN);

	for (size_t i = 0; i < 3; ++i)
	{
		cursor.Y += 2;

		if (menu[i].chosen == true)
		{
			printAtCenter(menu[i].text, checked);
		}
		else
			printAtCenter(menu[i].text, notChecked);
	}
}

void StartView::draw()
{
	clear();

	// each time startView gets opened defaults to "Start game"
	menu[0].chosen = true;
	menu[1].chosen = false;
	menu[2].chosen = false;

	displayMenu();

	int menu_current = 0;
	int c = 0;
	bool finish = false;

	while (selectedOption != Options::EXIT && !finish) // menu navigation
	{
		c = _getch();
		switch (c)
		{
		case 224:
			switch (_getch())
			{
			case 72: // up
				if (menu_current > 0) 
				{
					menu[menu_current].chosen = false;
					--menu_current;
					menu[menu_current].chosen = true;

					displayMenu();
				}
				break;
			case 80: // down
				if (menu_current < 2)
				{
					menu[menu_current].chosen = false;
					++menu_current;
					menu[menu_current].chosen = true;

					displayMenu();
				}
				break;
			}
			break;

		case VK_RETURN: // Enter

			selectedOption = (Options)menu_current;

			switch (selectedOption)
			{
			case Options::START: // draws field for game
				fieldView.draw();
				finish = true;
				break;
			case Options::HIGH_SCORE: // draws high score 
				scoresView.draw();
				finish = true;
				break;
			case Options::EXIT: // closes game window
				exit(0);
			}
			break;
		}
	}
}