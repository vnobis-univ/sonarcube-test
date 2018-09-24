#include <windows.h>
#include <iostream>
#include <string>
#include "ConsoleManipulators.h"
#include "Printer.h"

Printer::Printer(): clFont(Color::white), clBackground(Color::black) {}

Printer::Printer(Color clFont, Color clBackground) :clFont(clFont), clBackground(clBackground) {}

void Printer::setClFont(Color newCl)
{
	clFont = newCl;
}

void Printer::setClBackground(Color newCl)
{
	clBackground = newCl;
}

const Printer& Printer::operator<< (std::string stringToPrint) const
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int color = (int)clFont + 16 * (int)clBackground;
	SetConsoleTextAttribute(hConsole, color);

	std::cout << stringToPrint;

	//setting default
	SetConsoleTextAttribute(hConsole, 15);

	return *this;
}

const Printer& Printer::operator<< (char charToPrint) const
{
	std::string str(1, charToPrint);

	*this << str;

	return *this;
}

bool Printer::operator== (const Printer& rP)
{
	return clBackground == rP.clBackground && clFont == rP.clFont;
}

void Printer::printAtCenter(std::string stringToPrint) 
{
	makeLeftPadding(stringToPrint.length());

	*this << stringToPrint;

	std::cout << std::endl;
}

void Printer::makeLeftPadding(int length)
{
	int leftPadding = (getConsoleWidth() - length) / 2 - 1;

	COORD current;

	getCursorPosition(current);

	setCursoreAtPosition(0 + leftPadding, current.Y);
}