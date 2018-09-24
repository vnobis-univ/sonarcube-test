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

	void print(string text) const;
	void setColor() const;
	void midLinePrint(int line, string text) const;
};