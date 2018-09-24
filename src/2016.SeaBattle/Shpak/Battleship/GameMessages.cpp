#include "GameMessages.h"
#include "ConsoleManipulators.h"
#include "GameLogicComputer.h"
#include "LanguageManipulator.h"
#include <string>
#include <conio.h>
#include <iostream>
#include <vector>
#include "Printer.h"

int GameMessages::frameWidth = 45;
int GameMessages::frameHeight = 8;
COORD GameMessages::whereFrameStarts = { getConsoleWidth() / 2 - GameMessages::frameWidth / 2 - 2, 40 };

Printer GameMessages::hintPrinter = Printer(Color::gray, Color::black);

GameMessages::GameMessages()
{
}

void GameMessages::clearHints()
{
	std::string space(getConsoleWidth() - 2, ' ');

	for (size_t i = 0; i < frameHeight; ++i)
	{
		setCursoreAtPosition(0, whereFrameStarts.Y + i);

		Printer() << space;
	}
}

void GameMessages::drawShipPlacementHint()
{
	std::vector<std::string> vec;

	LanguageManipulator().getHowToDrawShipPlacementHint(vec);

	setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y + 2);

	hintPrinter.printAtCenter(vec[0]);

	setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y + 4);

	hintPrinter.printAtCenter(vec[1]);
}

void GameMessages::drawWin()
{
	std::vector<std::string> vec;

	LanguageManipulator().getHowToDrawWin(vec);

	setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y + 2);

	hintPrinter.printAtCenter(vec[0]);

	setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y + 4);

	hintPrinter.printAtCenter(vec[1]);

	while (!checkIfKeyPressed())
	{/*empty block*/}
}

void GameMessages::drawLose()
{
	std::vector<std::string> vec;

	LanguageManipulator().getHowToDrawLose(vec);

	setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y + 2);

	hintPrinter.printAtCenter(vec[0]);

	setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y + 4);

	hintPrinter.printAtCenter(vec[1]);

	while (!checkIfKeyPressed())
	{/*empty block*/}
}

void GameMessages::drawWaitUntilJoin(int id)
{
	std::vector<std::string> vec;

	LanguageManipulator().getHowToDrawWaitUntilJoin(vec);

	setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y + 2);

	hintPrinter.printAtCenter(vec[0] + std::to_string(id));

	setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y + 4);

	hintPrinter.printAtCenter(vec[1]);
}

void GameMessages::drawWaintUntilMakeMove()
{
	std::vector<std::string> vec;

	LanguageManipulator().getHowToDrawWaintUntilMakeMove(vec);

	setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y + 3);

	hintPrinter.printAtCenter(vec[0]);
}

int GameMessages::getIdForGame()
{
	std::vector<std::string> vec;

	LanguageManipulator().getHowToDrawGetIdForGame(vec);

	setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y + 3);

	std::string str = vec[0];

	hintPrinter.makeLeftPadding(str.length());

	hintPrinter << str;

	COORD current;

	getCursorPosition(current);

	return getId(current);
}

int GameMessages::getId(COORD whereStart)
{
	std::string newId = "";

	size_t counter = 0;
	char ch = 0;

	while (counter < 6 && ch != 13)
	{
		ch = _getch();

		if (ch == 224) 
		{
			_getch();
			continue;
		}

		if (ch == 8 && counter > 0)
		{
			newId.pop_back();
			--counter;

			setCursoreAtPosition(whereStart);
			std::cout << newId << "     ";

			continue;
		}
		else if (ch != 8 && ch != 13 && counter != 5)
		{
			for (char i = '0'; i <= '9'; ++i)
			{
				if (ch == i)
				{
					newId += ch;

					setCursoreAtPosition(whereStart);
					std::cout << newId;

					++counter;
				}

			}
		}
	}

	if (newId == "")
		return -1;
	else
		return stoi(newId);
}