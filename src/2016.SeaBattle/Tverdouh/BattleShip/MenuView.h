#pragma once
#include<string>
#include<iostream>
#include <conio.h>
#include "StartGameView.h"

using namespace std;

void printInTheCentre(string str, int numberOfLine, int consoleW);
void SetColor(int text, int background);
void clean();
void drawNet(int x1, int y1);

class Menu
{
	int IsSelected;
public:
	Menu() :IsSelected(0){}

	void drawMenu()
	{


		switch (IsSelected)
		{
		case 0:
		{
			SetColor(15, 0);
			printInTheCentre("* START *", 15, 120);
			SetColor(0, 15);
			printInTheCentre("EXIT", 16, 120);
		}         break;

		case 1:
		{

			printInTheCentre("START", 15, 120);
			SetColor(15, 0);
			printInTheCentre("* EXIT *", 16, 120);
			SetColor(0, 15);
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
			clean();
			StartGameView menu;
			menu.drawMenu();
			menu.draw();


		}
		else if (IsSelected == 1)
		{
			return;

		}
	}
};