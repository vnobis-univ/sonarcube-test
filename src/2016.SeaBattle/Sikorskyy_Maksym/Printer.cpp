#include "Printer.h"


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Printer pStandart(Color::dWhite);
Printer pPurpleBlack(Color::dPurple);
Printer pPureWhite(Color::dWhite);
Printer pPurpleBlue(Color::dPurple, Color::lBlue);
Printer pWhiteBlueBlue(Color::dWhite, Color::lBlue);
Printer pGrayBlue(Color::lBlack, Color::lBlue);
Printer pWhiteBlack(Color::dWhite, Color::dBlack);
Printer pYellowBlack(Color::dYellow, Color::dBlack);

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


