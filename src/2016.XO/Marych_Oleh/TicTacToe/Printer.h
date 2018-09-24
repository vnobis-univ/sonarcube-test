#pragma once
#include <string>
#include <iostream>
#include "Color.h"
#include <Windows.h>

using namespace std;

class Printer
{
	ConsoleColor background;
	ConsoleColor text;
public:
	Printer();
	Printer(ConsoleColor, ConsoleColor);
	int getTextColors()const;
	void print(char) const;
	const Printer& operator<<(string);
};
