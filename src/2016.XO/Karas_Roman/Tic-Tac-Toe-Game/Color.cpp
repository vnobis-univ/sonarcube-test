#include "Color.h"


Color convertStrToColor(string text)
{
	Color color = Color::BLACK; //by default is black
	if (text == "black" || text == "BLACK") color = Color::BLACK;
	else if (text == "blue" || text == "BLUE") color = Color::BLUE;
	else if (text == "green" || text == "GREEN") color = Color::GREEN;
	else if (text == "aqua" || text == "AQUA") color = Color::AQUA;
	else if (text == "red" || text == "RED") color = Color::RED;
	else if (text == "purple" || text == "PURPLE") color = Color::PURPLE;
	else if (text == "yellow" || text == "YELLOW") color = Color::YELLOW;
	else if (text == "white" || text == "WHITE") color = Color::WHITE;
	else if (text == "gray" || text == "GRAY") color = Color::GRAY;
	else if (text == "light_blue" || text == "LIGHT_BLUE") color = Color::LIGHT_BLUE;
	else if (text == "light_green" || text == "LIGHT_GREEN") color = Color::LIGHT_GREEN;
	else if (text == "light_aqua" || text == "LIGHT_AQUA") color = Color::LIGHT_AQUA;
	else if (text == "light_red" || text == "LIGHT_RED") color = Color::LIGHT_RED;
	else if (text == "light_purple" || text == "LIGHT_PURPLE") color = Color::LIGHT_PURPLE;
	else if (text == "light_yellow" || text == "LIGHT_YELLOW") color = Color::LIGHT_YELLOW;
	else if (text == "light_white" || text == "LIGHT_WHITE") color = Color::LIGHT_WHITE;
	else color = Color::BLACK; //default case
	return color;
}

int convertColorToInt(Color color)
{
	int number = 0; //by default is black
	switch (color)
	{
	case Color::BLACK: number = 0; break;
	case Color::BLUE: number = 1; break;
	case Color::GREEN: number = 2; break;
	case Color::AQUA: number = 3; break;
	case Color::RED: number = 4; break;
	case Color::PURPLE: number = 5; break;
	case Color::YELLOW: number = 6; break;
	case Color::WHITE: number = 7; break;
	case Color::GRAY: number = 8; break;
	case Color::LIGHT_BLUE: number = 9; break;
	case Color::LIGHT_GREEN: number = 10; break;
	case Color::LIGHT_AQUA: number = 11; break;
	case Color::LIGHT_RED: number = 12; break;
	case Color::LIGHT_PURPLE: number = 13; break;
	case Color::LIGHT_YELLOW: number = 14; break;
	case Color::LIGHT_WHITE: number = 15; break;
	default: number = 0;
	}
	return number;
}
