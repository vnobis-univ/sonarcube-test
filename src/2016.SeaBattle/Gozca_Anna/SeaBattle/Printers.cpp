#include "ConsoleUtils.h"
#include "Printers.h"

Printer::Printer() : textColor(Color::WHITE), backgroundColor(Color::BLACK), hConsole1(hConsole) {}
Printer::Printer(Color textColor1, Color backgroundColor1) :
	textColor(textColor1), backgroundColor(backgroundColor1), hConsole1(hConsole) {}

Color parseLineToColor(string text)
{
	Color color;
	if (text == "Black")
	{
		color = Color::BLACK;
	}
	else if (text == "blue")
	{
		color = Color::BLUE;
	}
	else if (text == "Green")
	{
		color = Color::GREEN;
	}
	else if (text == "Aqua")
	{
		color = Color::AQUA;
	}
	else if (text == "Red")
	{
		color = Color::RED;
	}
	else if (text == "Purple")
	{
		color = Color::PURPLE;
	}
	else if (text == "Yellow")
	{
		color = Color::YELLOW;
	}
	else if (text == "White")
	{
		color = Color::WHITE;
	}
	else if (text == "Gray")
	{
		color = Color::GRAY;
	}
	else if (text == "Light_blue")
	{
		color = Color::LIGHT_BLUE;
	}
	else if (text == "Light_green")
	{
		color = Color::LIGHT_GREEN;
	}
	else if (text == "Light_aqua")
	{
		color = Color::LIGHT_AQUA;
	}
	else if (text == "Light_red")
	{
		color = Color::LIGHT_RED;
	}
	else if (text == "Light_purple")
	{
		color = Color::LIGHT_PURPLE;
	}
	else if (text == "Light_yellow")
	{
		color = Color::LIGHT_YELLOW;
	}
	else if (text == "Light_white")
	{
		color = Color::LIGHT_WHITE;
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
	return textAttributeValue;
}

const Printer & Printer :: operator << (string textToPrint) const
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hConsole1, &csbiInfo);
	SetConsoleTextAttribute(hConsole1, convertColorToInt(backgroundColor) * 16 + convertColorToInt(textColor));
	cout << textToPrint;
	SetConsoleTextAttribute(hConsole1, csbiInfo.wAttributes);
	return *this;
}

const Printer & Printer :: operator << (char textToPrint) const
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hConsole1, &csbiInfo);
	SetConsoleTextAttribute(hConsole1, convertColorToInt(backgroundColor) * 16 + convertColorToInt(textColor));
	cout << textToPrint;
	SetConsoleTextAttribute(hConsole1, csbiInfo.wAttributes);
	return *this;
}

const Printer & Printer :: operator >> (char name[7]) const
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hConsole1, &csbiInfo);
	SetConsoleTextAttribute(hConsole1, convertColorToInt(backgroundColor) * 16 + convertColorToInt(textColor));
	for (int i = 0; i < 7; i++)
	{
		cin >> name[i];
	}
	SetConsoleTextAttribute(hConsole1, csbiInfo.wAttributes);
	return *this;
}

Printer& Printer::operator = (const Printer& p)
{
	textColor = p.textColor;
	backgroundColor = p.backgroundColor;
	hConsole1 = p.hConsole1;
	return *this;
}

ostream& operator <<(ostream& os, const Printer& printer)
{
	os << "Printer(" << static_cast<underlying_type<Color>::type>(printer.textColor)
		<< "; " << static_cast<underlying_type<Color>::type>(printer.backgroundColor) << ")";
	return os;
}

istream& operator >>(istream& is, Printer& printer)
{
	string fontColorStr, backgroundColorStr;
	if (is >> fontColorStr >> backgroundColorStr)
	{
		printer.textColor = parseLineToColor(fontColorStr);
		printer.backgroundColor = parseLineToColor(backgroundColorStr);
	}
	return is;
}

Printer redTextWhiteBG(Color::LIGHT_WHITE, Color::AQUA);
Printer redTextYellowBG(Color::WHITE, Color::AQUA);

