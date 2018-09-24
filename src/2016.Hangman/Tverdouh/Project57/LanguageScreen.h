#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "EnglishMenu.h"
#include "UkraineMenu.h"
using namespace std;

void printInTheCentre(string str, int numberOfLine, int consoleWidth);
void SetColor(int text, int background);
void clean();
void resetColour();
class LanguageMenu
{
	int IsSelected;
public:
	LanguageMenu() :IsSelected(0){}
	
	void drawMenu()
	{
		

		switch (IsSelected)
		{
		case 0:
		{
				  SetColor(8, 4);
				  printInTheCentre("* ENGLISH *", 12, 80);
				  SetColor(4, 8);
				  printInTheCentre("UKRAINE", 13, 80);
		}         break;

		case 1:
		{

				  printInTheCentre("ENGLISH", 12, 80);
				  SetColor(8, 4);
				  printInTheCentre("* UKRAINE *", 13, 80);
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
			IsSelected = IsSelected % 2;
			if (IsSelected < 0) IsSelected += 1;
			clean();
			drawMenu();
			
		}
		if (IsSelected == 0)
		{
			EnglishMenu menu;
			menu.draw();


		}
		else if (IsSelected == 1)
		{
			UkraineMenu menu;
			menu.draw();

		}
	}
};