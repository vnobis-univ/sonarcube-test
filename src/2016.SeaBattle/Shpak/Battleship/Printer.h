#pragma once
#include <string>

enum class Color
{
	black,
	blue,
	green,
	aqua,
	red,
	purple,
	yellow,
	white,
	gray,
	lightBlue,
	lightGreen,
	lightAqua,
	lightRed,
	lightPurple,
	lightYellow,
	brightWhite
};

class Printer
{
	Color clFont;
	Color clBackground;

public:
	Printer();

	Printer(Color, Color);

	void setClFont(Color);

	void setClBackground(Color);

	Color getClFont() const;

	const Printer& operator<< (std::string textToPrint) const;

	const Printer& operator<< (char charToPrint) const;

	bool operator== (const Printer&);

	void printAtCenter(std::string);

	void makeLeftPadding(int);
};

