#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

using namespace::std;

extern HANDLE hConsole;

enum class Color
{
	dBlack, dBlue, dGreen, dAqua, dRed, dPurple, dYellow, dWhite,
	lBlack, lBlue, lGreen, lAqua, lRed, lPurple, lYellow, lWhite
};

class Printer
{
private:
	Color background;
	Color font;
public:
	Printer(Color f = Color::dWhite, Color b = Color::dBlack);

	void print(string toPrint);

	void print(char toPrint);

	void setColors(Color f, Color b);

	Color getBack() const;

	Color getFont() const;
};

extern Printer pStandart;
extern Printer pPurpleBlack;
extern Printer pPureWhite;
extern Printer pPurpleBlue;
extern Printer pWhiteBlueBlue;
extern Printer pGrayBlue;
extern Printer pWhiteBlack;
extern Printer pYellowBlack;