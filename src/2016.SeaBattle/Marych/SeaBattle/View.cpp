#include "View.h"
#include "Printer.h"
#include "Console.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

Printer View::defaultPrinter = Printer(Color::LIGHT_GREEN, Color::BLACK);
Printer View::defaultPrinterBg = Printer(Color::BLACK, Color::LIGHT_GREEN);

void View::draw()
{
	setCursoreAtPosition(0, 0);

	drawBackground();
}

void View::clean()
{
	system("cls");
}
void View::drawBackground()
{
	Printer black(Color::BLACK, Color::BLACK);
	Printer gameName(Color::BLACK, Color::LIGHT_BLUE);

	string bodyLine = string(consoleWidth - 2, ' ');

	black << " ";
	defaultPrinterBg << bodyLine;
	black << " ";

	for (int i = 0; i < consoleHeight - 2; i++)
	{
		defaultPrinterBg << " ";
		black << bodyLine;
		defaultPrinterBg << " ";
	}

	black << " ";
	defaultPrinterBg << bodyLine;

	printAtCenterOfLine(0, "-->  Sea Battle  <--", defaultPrinterBg);

	showConsoleCursor(false);
}