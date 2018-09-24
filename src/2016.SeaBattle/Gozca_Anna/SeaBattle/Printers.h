#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

enum class Color
{
	BLACK,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	LIGHT_WHITE
};

Color parseLineToColor(string text);
int convertColorToInt(const Color color);

class Printer
{
private:
	Color textColor;
	Color backgroundColor;
	HANDLE hConsole1;
public:
	Printer();
	Printer(Color textColor1, Color backgroundColor1);
	const Printer& operator << (string textToPrint) const;
	const Printer& operator << (char textToPrint) const;

	const Printer & Printer :: operator >> (char name[7]) const;
	Printer& operator = (const Printer& p);
	friend ostream& operator <<(ostream& os, const Printer& printer);
	friend istream& operator >>(istream& is, Printer& printer);
};

extern Printer redTextWhiteBG;
extern Printer redTextYellowBG;