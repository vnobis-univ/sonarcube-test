#pragma once
#include <string>
using namespace::std;

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

	void setColors(Color f, Color b);

	Color getBack() const;

	Color getFont() const;
};


