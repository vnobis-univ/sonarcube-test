#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include "UkraineMenu.h"
using namespace std;

void printInTheCentre(string str, int numberOfLine, int consoleWidth);
void SetColor(int text, int background);
void clean();

class EnglishOptions
{
	int IsSelected;
	static int level;
public:
	EnglishOptions() :IsSelected(0){}

	int GetSelected()
	{
		return IsSelected;
	}
	int GetLevel()
	{
		return level;
	}

	void drawMenu()
	{
		switch (IsSelected)
		{
		case 0:
		{
				  SetColor(8, 4);
				  printInTheCentre("* EASY *", 8, 80);
				  SetColor(4, 8);
				  printInTheCentre("MEDIUM", 9, 80);
				  printInTheCentre("HARD", 10, 80);
				  printInTheCentre("BACK", 11, 80);
		}         break;

		case 1:
		{

				  printInTheCentre("EASY", 8, 80);
				  SetColor(8, 4);
				  printInTheCentre("* MEDIUM *", 9, 80);
				  SetColor(4, 8);
				  printInTheCentre("HARD", 10, 80);
				  printInTheCentre("BACK", 11, 80);
				  break;
		}
		case 2:
		{
				  printInTheCentre("EASY", 8, 80);
				  printInTheCentre("MEDIUM", 9, 80);
				  SetColor(8, 4);
				  printInTheCentre("* HARD *", 10, 80);
				  SetColor(4, 8);
				  printInTheCentre("BACK", 11, 80);
				  break;
		}
		case 3:
		{
				  printInTheCentre("EASY", 8, 80);
				  printInTheCentre("MEDIUM", 9, 80);
				  printInTheCentre("HARD", 10, 80);
				  SetColor(8, 4);
				  printInTheCentre("* BACK *", 11, 80);
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
			level = 0;
		}
		else if (IsSelected == 1)
		{
			level = 1;
		}
		else if (IsSelected == 2)
		{
			level = 2;
		}
		else if (IsSelected == 3)
		{


		}
	}
};