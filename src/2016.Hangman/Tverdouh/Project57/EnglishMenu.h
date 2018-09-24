#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "EnglishOptions.h"
#include "Game.h"
#include "Highscores.h"
using namespace std;

void printInTheCentre(string str, int numberOfLine, int consoleWidth);
void SetColor(int text, int background);
void clean();

class EnglishMenu
{
int IsSelected;
public:
	EnglishMenu() :IsSelected(0){}

	void drawMenu()
	{


		switch (IsSelected)
		{
		case 0:
		{
				  SetColor(8, 4);
				  printInTheCentre("* START *", 8, 80);
				  SetColor(4, 8);
				  printInTheCentre("OPTIONS", 9, 80);
				  printInTheCentre("HIGHSCORES", 10, 80);
				  printInTheCentre("EXIT", 11, 80);
		}         break;

		case 1:
		{

				  printInTheCentre("START", 8, 80);
				  SetColor(8, 4);
				  printInTheCentre("* OPTIONS *", 9, 80);
				  SetColor(4, 8);
				  printInTheCentre("HIGHSCORES", 10, 80);
				  printInTheCentre("EXIT", 11, 80);
				  break;
		}
		case 2:
		{
			printInTheCentre("START", 8, 80);
			printInTheCentre("OPTIONS", 9, 80);
			SetColor(8, 4);
			printInTheCentre("* HIGHSCORES *", 10, 80);
			SetColor(4, 8);
			printInTheCentre("EXIT", 11, 80);
			break;
		}
		case 3:
		{
				  printInTheCentre("START", 8, 80);
				  printInTheCentre("OPTIONS", 9, 80);
				  printInTheCentre("HIGHSCORES", 10, 80);
				  SetColor(8, 4);
				  printInTheCentre("* EXIT *", 11, 80);
				  SetColor(4, 8);
				  break;
		}
		}
	}

	void draw()
	{
		clean();
		drawMenu();
		char input = ' ';
		while (input != 13)
		{
			if (input == 13) break;
			input = _getch();
			switch (input)
			{
			case 72: IsSelected -= 1; break;
			case 80: IsSelected += 1; break;
			}
			IsSelected = IsSelected % 4;
			if (IsSelected < 0) IsSelected += 4;
			clean();
			drawMenu();

		}
		if (IsSelected == 0)
		{
			clean();
			Game game;
			game.draw();


		}
		else if (IsSelected == 1)
		{
			EnglishOptions menu;
			menu.draw();
			if ((menu.GetSelected() == 0) || (menu.GetSelected() == 1) || (menu.GetSelected() == 2) || (menu.GetSelected() == 3))
			{
				draw();
			}

		}
		else if (IsSelected == 2)
		{
			clean();
			HighscoreView menu;
			menu.draw();
			
			switch(_getch())
			{
			case 13:
				clean();
				draw();
			}

		}
		else if (IsSelected == 3)
		{
			return;
		}
	}
};