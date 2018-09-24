#include "Colors.h"

int intColor(Color col)
{
	int ColorValue;
	switch (col)
	{
	case Color::Black:
		ColorValue = 0;
		break;
	case Color::Blue:
		ColorValue = 1;
		break;
	case Color::Green:
		ColorValue = 2;
		break;
	case Color::Cyan:
		ColorValue = 3;
		break;
	case Color::Red:
		ColorValue = 4;
		break;
	case Color::Magenta:
		ColorValue = 5;
		break;
	case Color::Brown:
		ColorValue = 6;
		break;
	case Color::LightGray:
		ColorValue = 7;
		break;
	case Color::DarkGray:
		ColorValue = 8;
		break;
	case Color::LightBlue:
		ColorValue = 9;
		break;
	case Color::LightGreen:
		ColorValue = 10;
		break;
	case Color::LightCyan:
		ColorValue = 11;
		break;
	case Color::LightRed:
		ColorValue = 12;
		break;
	case Color::LightMagenta:
		ColorValue = 13;
		break;
	case Color::Yellow:
		ColorValue = 14;
		break;
	case Color::White:
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