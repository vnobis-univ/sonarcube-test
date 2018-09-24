#include <iostream>
#include <string>
#include <windows.h> 
#include "Printer.h"
#include "Color.h"
#include "Console.h"

using namespace std;

Printer::Printer() : text(Color::WHITE), background(Color::BLACK), hConsole(hConOut) {}

Printer::Printer(Color _fontColor, Color _backgroundColor) :
	text(_fontColor), background(_backgroundColor), hConsole(hConOut) {}

const Printer& Printer::operator<<(string textToPrint) const
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; // stored console info
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);

	SetConsoleTextAttribute(hConsole, getTextAttribute()); // set our colors
	cout << textToPrint; // print text
	SetConsoleTextAttribute(hConsole, csbiInfo.wAttributes); // set colors as they were before us
	return *this;
}

void Printer::print(char textToPrint) const
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; // stored console info
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);

	SetConsoleTextAttribute(hConsole, getTextAttribute()); // set our colors
	cout << textToPrint; // print text
	SetConsoleTextAttribute(hConsole, csbiInfo.wAttributes); // set colors as they were before us
}
int Printer::getTextAttribute() const
{
	return convertColorToInt(background) * 16 + convertColorToInt(text);
}

Printer& Printer::operator = (const Printer& p)
{
	text = p.text;
	background = p.background;
	hConsole = p.hConsole;

	return *this;
}

bool Printer::operator== (const Printer& p)
{
	return (background == p.background) && (text == p.text);
}

ostream& operator <<(ostream& os, const Printer& printer)
{
	os << "Printer(" << static_cast<underlying_type<Color>::type>(printer.text)
		<< "; " << static_cast<underlying_type<Color>::type>(printer.background) << ")";
	return os;
}

istream& operator >>(istream& is, Printer& printer)
{
	string fontColorStr, backgroundColorStr;
	if (is >> fontColorStr >> backgroundColorStr)
	{
		printer.text = parseStrToColor(fontColorStr);
		printer.background = parseStrToColor(backgroundColorStr);
	}

	return is;
}

