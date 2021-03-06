#include "Printer.h"
#include <Windows.h>
#include "ConsoleTools.h"
#include <iostream>

Printer pStandart(Color::dWhite);
Printer pPurpleBlack(Color::dPurple);
Printer pPureWhite(Color::dWhite);
Printer pPurpleBlue(Color::dPurple, Color::lBlue);
Printer pWhiteBlueBlue(Color::dWhite, Color::lBlue);
Printer pGrayBlue(Color::lBlack, Color::lBlue);
Printer pYellowBlue(Color::lYellow, Color::lBlue);
Printer pRedBlue(Color::lRed, Color::lBlue);
Printer pRedBlack(Color::lWhite, Color::dBlack);

Printer::Printer(Color f, Color b) : font(f), background(b){}

void Printer::print(string toPrint)
{
	SetConsoleTextAttribute(hConsole, static_cast<int>(this->getFont()) + static_cast<int>(this->getBack()) * 16);
	cout << toPrint;
	SetConsoleTextAttribute(hConsole, 7);
}

void Printer::print(char ch)
{
	SetConsoleTextAttribute(hConsole, static_cast<int>(this->getFont()) + static_cast<int>(this->getBack()) * 16);
	cout << ch;
	SetConsoleTextAttribute(hConsole, 7);
}

Color Printer::getBack() const
{
	return background;
}

Color Printer::getFont() const
{
	return font;
}
