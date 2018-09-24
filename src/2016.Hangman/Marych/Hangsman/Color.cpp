#include <iostream>
#include <string>
#include "Color.h"

using namespace std;

Color parseStrToColor(const string str)
{
	Color color;
	if (str == "black")
	{
		color = Color::BLACK;
	}
	else if (str == "blue")
	{
		color = Color::BLUE;
	}
	else if (str == "green")
	{
		color = Color::GREEN;
	}
	else if (str == "aqua")
	{
		color = Color::AQUA;
	}
	else if (str == "red")
	{
		color = Color::RED;
	}
	else if (str == "purple")
	{
		color = Color::PURPLE;
	}
	else if (str == "yellow")
	{
		color = Color::YELLOW;
	}
	else if (str == "white")
	{
		color = Color::WHITE;
	}
	else if (str == "gray")
	{
		color = Color::GRAY;
	}
	else if (str == "light_blue")
	{
		color = Color::LIGHT_BLUE;
	}
	else if (str == "light_green")
	{
		color = Color::LIGHT_GREEN;
	}
	else if (str == "light_aqua")
	{
		color = Color::LIGHT_AQUA;
	}
	else if (str == "light_red")
	{
		color = Color::LIGHT_RED;
	}
	else if (str == "light_purple")
	{
		color = Color::LIGHT_PURPLE;
	}
	else if (str == "light_yellow")
	{
		color = Color::LIGHT_YELLOW;
	}
	else if (str == "light_white")
	{
		color = Color::LIGHT_WHITE;
	}
	else
	{
		cout << "Some error occured! Using black color as default value!" << endl;
		color = Color::BLACK;
	}

	return color;
}

int convertColorToInt(const Color color)
{
	int textAttributeValue;
	switch (color)
	{
	case Color::BLACK:
		textAttributeValue = 0;
		break;
	case Color::BLUE:
		textAttributeValue = 1;
		break;
	case Color::GREEN:
		textAttributeValue = 2;
		break;
	case Color::AQUA:
		textAttributeValue = 3;
		break;
	case Color::RED:
		textAttributeValue = 4;
		break;
	case Color::PURPLE:
		textAttributeValue = 5;
		break;
	case Color::YELLOW:
		textAttributeValue = 6;
		break;
	case Color::WHITE:
		textAttributeValue = 7;
		break;
	case Color::GRAY:
		textAttributeValue = 8;
		break;
	case Color::LIGHT_BLUE:
		textAttributeValue = 9;
		break;
	case Color::LIGHT_GREEN:
		textAttributeValue = 10;
		break;
	case Color::LIGHT_AQUA:
		textAttributeValue = 11;
		break;
	case Color::LIGHT_RED:
		textAttributeValue = 12;
		break;
	case Color::LIGHT_PURPLE:
		textAttributeValue = 13;
		break;
	case Color::LIGHT_YELLOW:
		textAttributeValue = 14;
		break;
	case Color::LIGHT_WHITE:
		textAttributeValue = 15;
		break;
	default:
		textAttributeValue = 0;
	}

	if (textAttributeValue < 0 || textAttributeValue > 15)
	{
		cout << "Some error occured! textAttributeValue should be in range [0;15]. Using default 0 value (black color)" << endl;
		textAttributeValue = 0;
	}

	return textAttributeValue;
}

