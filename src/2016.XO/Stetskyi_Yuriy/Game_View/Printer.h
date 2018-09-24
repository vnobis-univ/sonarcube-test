#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>

using namespace std;

enum class Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
};

class Printer
{
	Color font;
	Color background;

public:
	Printer(Color f = Color::WHITE, Color back = Color::BLACK) 
		: font(f), 
		background(back)
	{
	}

	template <class T>
	void print(T text) const
	{

		int _font = static_cast<int>(font);
		int _back = static_cast<int>(background);

		SetConsoleTextAttribute(hConsole, _font + 16 * _back);

		ostringstream out;
		out << text;
		cout << out.str() << endl;

		SetConsoleTextAttribute(hConsole, 15);  // return to normal state
	}
};
