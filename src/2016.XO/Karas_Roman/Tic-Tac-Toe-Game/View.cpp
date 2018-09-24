#include "View.h"
#include "Printer.h"
#include "ForConsole.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

void View::clean()
{
	system("cls");
}

void View::draw()
{
	setCursorPosition(0, 0);
	drawBackground();
}

void View::drawBackground()
{
	Printer black(Color::BLACK, Color::BLACK);
	Printer frame(Color::LIGHT_GREEN, Color::AQUA);
	Printer background(Color::GREEN, Color::BLUE);

	string bodyLine = string(consoleWidth - 2, ' ');

	setCursorPosition(0, 0);

	black << " ";
	frame << bodyLine;
	black << " ";

	for (int i = 0; i < consoleHeight - 2; i++)
	{
		frame << " ";
		background << bodyLine;
		frame << " ";
	}

	black << " ";
	frame << bodyLine;

	printAtLineCenter(0, "Tic Tac Toe Game", frame);
	printAtLineCenter(14, "Press any key!", background);
	printAtLineCenter(consoleHeight - 1, "Made by Roman Karas, PMi-11", frame);
	showCursor(false);
}