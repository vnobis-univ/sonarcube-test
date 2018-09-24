#pragma once
#include <string>
#include <Windows.h>
#include <iostream>
#include "Color.h"

using namespace std;

extern HANDLE hconsole;
extern int consoleWidth;
extern int consoleHeight;

class Printer
{
	ConsoleColor background;
	ConsoleColor text;
public:
	Printer(ConsoleColor, ConsoleColor);
	int getTextColor()const;
	const Printer& operator<<(string);
	const Printer& operator<<(int);
};