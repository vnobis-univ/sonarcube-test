#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "UkraineOptions.h"
#include "Game1.h"
#include "Highscores.h"
using namespace std;

void printInTheCentre(string str, int numberOfLine, int consoleWidth);
void SetColor(int text, int background);
void clean();

class UkraineMenu
{
	int IsSelected;
public:
	UkraineMenu() :IsSelected(0){}
	
	void drawMenu()
	{


		switch (IsSelected)
		{
		case 0:
		{
				  SetColor(8, 4);
				  printInTheCentre("* —“¿–“ *", 8, 80);
				  SetColor(4, 8);
				  printInTheCentre("Œœ÷IØ", 9, 80);
				  printInTheCentre("–≈«”À‹“¿“", 10, 80);
				  printInTheCentre("¬»’Iƒ", 11, 80);
		}         break;

		case 1:
		{

				  printInTheCentre("—“¿–“", 8, 80);
				  SetColor(8, 4);
				  printInTheCentre("* Œœ÷IØ *", 9, 80);
				  SetColor(4, 8);
				  printInTheCentre("–≈«”À‹“¿“", 10, 80);
				  printInTheCentre("¬»’Iƒ", 11, 80);
				  break;
		}
		case 2:
		{
				  printInTheCentre("—“¿–“", 8, 80);
				  printInTheCentre("Œœ÷IØ", 9, 80);
				  SetColor(8, 4);
				  printInTheCentre("* –≈«”À‹“¿“ *", 10, 80);
				  SetColor(4, 8);
				  printInTheCentre("¬»’Iƒ", 11, 80);
				  break;
		}
		case 3:
		{
				  printInTheCentre("—“¿–“", 8, 80);
				  printInTheCentre("Œœ÷IØ", 9, 80);
				  printInTheCentre("–≈«”À‹“¿“", 10, 80);
				  SetColor(8, 4);
				  printInTheCentre("* ¬»’Iƒ *", 11, 80);
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
			Game1 game;
			game.draw();



		}
		else if (IsSelected == 1)
		{
			UkraineOptions menu;
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

			switch (_getch())
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