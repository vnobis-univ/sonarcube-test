#pragma once
#include <string>

#include "Color.h"

using std::string;

class Printer
{
	Color text;
	Color backgroung;

	int convertTextCol() const;
	int convertBgrndCol() const;
public:
	Printer(Color txt = Color::white, Color bg = Color::black);

	void Print(string text) const;
	void setColor() const;
	void MidLinePrint(int line, string text) const;
};