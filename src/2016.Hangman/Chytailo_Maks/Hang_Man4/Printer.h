#pragma once
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;
enum Color
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

class Printer
{
	Color frontColor;
	Color backgroundColor;
public:
	Printer();
	Printer(Color f, Color b);
	void print(string text);
};
