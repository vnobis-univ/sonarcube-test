#pragma once
#include <string>
#include <Windows.h>
#include <iostream>
#include "Colors.h"

using namespace std;

extern HANDLE hconsole;
extern int consoleWidth;
extern int consoleHeight;

class Printer
{
	Color background;
	Color text;
public:
	Printer(Color, Color);
	int getColor()const;
	const Printer& operator<<(string);
};