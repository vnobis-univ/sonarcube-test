#pragma once
#include <iostream>//for standart in/out
#include <fstream>//for working with files
#include <conio.h>//for _getch()
#include <string>//for strings
#include <Windows.h>//for grapjics
#include "Color.h"
#include "SetConsoleSize.h"
#include "LocateYourShips.h"
#include "HumanPlayer.h"
#include "BotPlayer.h"
#include "InternetPlayer.h"
#include "Game.h"
#include "Ship.h"
using namespace std;

class StartMenu{
public:
	int gameOption;//1 - single player, 2 - two players by internet, 3 - two players on one computer
	int selectedOption;
public:
	StartMenu() :
		gameOption(0),
		selectedOption(0)
	{
	}

	void draw()
	{
		drawMainMenu();
		if (selectedOption == 0)
		{
			drawSingleOrMulti();
			if (selectedOption == 0)
			{
				drawByInternet();
				if (selectedOption == 0)
				{
					gameOption = 2;
				}
				else
				{
					gameOption = 3;
				}
			}
			else
			{
				gameOption = 1;
			}
			if (gameOption != 3)
			{
				drawPlaceShips();
				if (selectedOption == 0)
				{
					system("cls");
					field.draw();
					field.drawSettingShips();
				}
			}
			afterChoosing();
		}
	}

	void drawAnyMenuWithTwoOptions(string s1, string s2)
	{
		selectedOption = 0;
		bool pressedEnter = false;

		while (!pressedEnter)
		{
			system("cls");
			SetConsoleTextAttribute(hConsole, Blue);

			for (size_t i = 0; i < 10; ++i)
				cout << endl;

			const string spaces = "                    ";

			switch (selectedOption)
			{

			case 0:
			{
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << s1 << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << s2 << endl;
				break;
			}

			case 1:
			{
				cout << spaces << s1 << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << s2 << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				break;
			}

			}

			char selectOption = ' ';
			selectOption = _getch();

			switch (selectOption)
			{
			case 72:
			{
				--selectedOption;
				break;
			}

			case 75:
			{
				--selectedOption;
				break;
			}

			case 77:
			{
				++selectedOption;
				break;
			}

			case 80:
			{
				++selectedOption;
				break;
			}

			case 13:
			{
				pressedEnter = true;
				break;
			}

			default:
			{
				break;
			}
			}

			if (selectedOption < 0) selectedOption += 2;
			if (selectedOption > 1) selectedOption -= 2;
		}
	}

	void drawMainMenu()
	{
		string correction = "                 ";
		drawAnyMenuWithTwoOptions(correction + "PLAY", correction + "EXIT");
	}

	void drawSingleOrMulti()
	{
		string correction = "             ";
		drawAnyMenuWithTwoOptions(correction + " MULTIPLAYER", correction + "SINGLE PLAYER");
	}

	void drawByInternet()
	{
		string correction = "          ";
		drawAnyMenuWithTwoOptions(correction + "   PLAY BY INTERNET", correction + "PLAY ON THIS COMPUTER");
	}

	void drawPlaceShips()
	{
		string correction = "           ";
		drawAnyMenuWithTwoOptions(correction + " PLACE YOUR SHIPS", correction + "AUTOMATIC LOCATION");
	}

	void afterChoosing(){

		ofstream write("GameOption.txt");
		write << gameOption;
		write.close();

		if (gameOption == 1)
		{
			BotPlayer game;
			game.draw();
		}
		if (gameOption == 2)
		{
			InternetPlayer game;
			game.draw();
		}
		if (gameOption == 3)
		{
			HumanPlayer game;
			game.draw();
		}
	}
};

StartMenu menu;