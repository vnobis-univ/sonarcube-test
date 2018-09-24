#include "Color.h"

int convertColToInt(ConsoleColor col)
{
	int ColorValue;
	switch (col)
	{
	case ConsoleColor::Black:
		ColorValue = 0;
		break;
	case ConsoleColor::Blue:
		ColorValue = 1;
		break;
	case ConsoleColor::Green:
		ColorValue = 2;
		break;
	case ConsoleColor::Cyan:
		ColorValue = 3;
		break;
	case ConsoleColor::Red:
		ColorValue = 4;
		break;
	case ConsoleColor::Magenta:
		ColorValue = 5;
		break;
	case ConsoleColor::Brown:
		ColorValue = 6;
		break;
	case ConsoleColor::LightGray:
		ColorValue = 7;
		break;
	case ConsoleColor::DarkGray:
		ColorValue = 8;
		break;
	case ConsoleColor::LightBlue:
		ColorValue = 9;
		break;
	case ConsoleColor::LightGreen:
		ColorValue = 10;
		break;
	case ConsoleColor::LightCyan:
		ColorValue = 11;
		break;
	case ConsoleColor::LightRed:
		ColorValue = 12;
		break;
	case ConsoleColor::LightMagenta:
		ColorValue = 13;
		break;
	case ConsoleColor::Yellow:
		ColorValue = 14;
		break;
	case ConsoleColor::White:
		ColorValue = 15;
		break;
	default:
		ColorValue = 0;
	}
	if (ColorValue > 15 && ColorValue < 0)
	{
		ColorValue = 0;
	}
	return ColorValue;
}