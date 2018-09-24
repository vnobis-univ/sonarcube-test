#include "Printer.h"

#include <iostream>
#include <string>
#include <windows.h> 
#include "Color.h"
#include "ForConsole.h"

using namespace std;

Printer::Printer() :fore(Color::WHITE), back(Color::BLACK), hConsole(Screen){}


Printer::Printer(Color _fore, Color _back) : fore(_fore), back(_back), hConsole(Screen){}

const Printer& Printer::operator<<(string textToPrint) const
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; // stored console info
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);

	SetConsoleTextAttribute(hConsole, getTextColor()); // set our colors
	cout << textToPrint; // print text
	SetConsoleTextAttribute(hConsole, csbiInfo.wAttributes); // set colors as they were before us :)
	return *this;
}

int Printer::getTextColor() const
{
	return convertColorToInt(back) * 16 + convertColorToInt(fore);
}

Printer& Printer::operator = (const Printer& p)
{
	fore = p.fore;
	back = p.back;
	hConsole = p.hConsole;

	return *this;
}

ostream& operator <<(ostream& os, const Printer& printer)
{
	os << "Printer(" << static_cast<underlying_type<Color>::type>(printer.fore)
		<< "; " << static_cast<underlying_type<Color>::type>(printer.back) << ")";
	return os;
}

istream& operator >>(istream& is, Printer& printer)
{
	string foreStr, backStr;
	if (is >> foreStr >> backStr)
	{
		printer.fore = convertStrToColor(foreStr);
		printer.back = convertStrToColor(backStr);
	}

	return is;
}