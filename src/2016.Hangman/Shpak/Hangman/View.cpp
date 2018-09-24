#include <iostream>
#include <Windows.h>
#include "View.h"
#include "ConsoleManipulators.h"
#include "FilesManipulator.h"
#include "Printer.h"

int View::whereLogoEnds = 11;

Printer View::mainPrinter = Printer(Color::red, Color::black);

void View::drawEmptyLines(int numberLines) const
{
	for (size_t i = 0; i < numberLines; ++i)
		std::cout << std::endl;
}

void View::clean()
{
	setCursoreAtPosition(0, whereLogoEnds);

	std::string replaceText(getConsoleWidth(), ' ');

	for (size_t i = whereLogoEnds; i < getConsoleHeight() - 1; ++i)
	{
		std::cout << replaceText;
	}
}

void View::drawLogo(int coordY) const
{
	std::vector<std::string> vec;


	FilesManipulator().getLogo(vec);

	Printer().makeLeftPadding(vec[0].length());

	COORD current;

	getCursorPosition(current);

	for (size_t i = 0; i < vec.size(); ++i)
	{
		setCursoreAtPosition(current.X, coordY + i);
		mainPrinter << vec[i];
	}

	drawEmptyLines(1);
}



