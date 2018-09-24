#pragma once
#include "Color.h"
#include <iostream>
#include <string>
#include <windows.h> 

using std::istream;
using std::string;

class Printer
{
	Color text;
	Color backgroung;

	int convertTextCol() const;
	int convertBgrndCol() const;
public:
	Printer(Color txt = Color::white, Color bg = Color::black);

	void Print(string) const;
	void Print(int) const;
	void SetConsoleAttribute() const;
	void MidLinePrint(int, string, unsigned i = -1) const;
};