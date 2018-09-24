#include "Colors.h"

int ColToInt(Color col)
{
	int colorInt;
	switch (col)
	{
	case Color::Black:
		colorInt = 0;
		break;
	case Color::Blue:
		colorInt = 1;
		break;
	case Color::Green:
		colorInt = 2;
		break;
	case Color::Cyan:
		colorInt = 3;
		break;
	case Color::Red:
		colorInt = 4;
		break;
	case Color::Brown:
		colorInt = 6;
		break;
	case Color::LightGray:
		colorInt = 7;
		break;
	case Color::White:
		colorInt = 15;
		break;
	default:
		colorInt = 0;
	}

	return colorInt;
}