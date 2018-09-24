#pragma once

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

	void print(std::string);
};

