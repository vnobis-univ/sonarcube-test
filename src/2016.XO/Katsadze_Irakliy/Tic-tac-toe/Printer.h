#pragma once
#include <string>
#include <iostream>
#include "Colors.h"
#include <Windows.h>

using namespace std;

class Printer
{
private:
	Color background;
	Color font;
public:
	Printer();
	Printer(Color,Color);
	int ConvertColorsToInt()const;
	const Printer& operator<<(string);
};